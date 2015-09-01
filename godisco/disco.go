// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package godisco

import (
	"fmt"
	"log"
	"time"
)

// ----------------------------------------------------------------------------

// Option is used as a functor to set Disco options.
//
// If you've never met this pattern yet, you can take a look at the readme
// usage/examples section; or at Dave Cheney's blog [1] for further reading.
//
// [1] http://dave.cheney.net/2014/10/17/functional-options-for-friendly-apis
type Option func(d *Disco) error

// Disco exposes a public API for decentralized service discovery.
type Disco struct {
	services []Service

	// broadcasting

	broadcastSubnet   string
	broadcastPort     int
	broadcastInterval time.Duration

	stopListening chan<- struct{}
	stopBeaconing chan<- struct{}

	// gossiping

	gossiper   Gossiper
	gossipAddr string

	stopGossiping chan<- struct{}
}

// ----------------------------------------------------------------------------

// NewDisco returns a new Disco with the given options.
func NewDisco(options ...Option) (*Disco, error) {
	d := &Disco{
		// broadcasting

		broadcastSubnet:   "127.0.0.1/24",
		broadcastPort:     55666,
		broadcastInterval: time.Second * 5,

		// gossiping

		gossipAddr: ":55777",
	}

	return d, d.SetOptions(options...)
}

// SetOptions sets the passed options.
func (d *Disco) SetOptions(options ...Option) error {
	for _, option := range options {
		if err := option(d); err != nil {
			return err
		}
	}

	return nil
}

// SetBroadcastSubnet sets the subnet IPv4 address in CIDR notation.
//
// Disco.broadcastSubnet defaults to "127.0.0.1/24".
func SetBroadcastSubnet(subnet string) Option {
	return func(d *Disco) error {
		_, err := cidrToBroadcast(subnet)
		if err != nil {
			return err
		}

		d.broadcastSubnet = subnet

		return nil
	}
}

// BroadcastSubnet returns a copy of d.broadcastSubnet.
//
// Disco.broadcastSubnet defaults to "127.0.0.1/24".
func (d Disco) BroadcastSubnet() string {
	return d.broadcastSubnet
}

// SetBroadcastPort sets the broadcast port.
//
// Disco.broadcastPort defaults to 55666.
func SetBroadcastPort(port int) Option {
	return func(d *Disco) error {
		if port < 0 || port > 2^16-1 {
			return fmt.Errorf("invalid port: %d", port)
		}

		d.broadcastPort = port

		return nil
	}
}

// BroadcastPort returns a copy of d.broadcastPort.
//
// Disco.broadcastPort defaults to 55666.
func (d Disco) BroadcastPort() int {
	return d.broadcastPort
}

// SetBroadcastInterval sets the broadcast port.
//
// Disco.broadcastInterval defaults to 5sec.
func SetBroadcastInterval(interval time.Duration) Option {
	return func(d *Disco) error {
		d.broadcastInterval = interval

		return nil
	}
}

// BroadcastInterval returns a copy of d.broadcastInterval.
//
// Disco.broadcastInterval defaults to 5sec.
func (d Disco) BroadcastInterval() time.Duration {
	return d.broadcastInterval
}

// SetGossipAddr sets the gossip port.
//
// Disco.gossipAddr defaults to 55777.
func SetGossipAddr(addr string) Option {
	return func(d *Disco) error {
		d.gossipAddr = addr

		return nil
	}
}

// GossipAddr returns a copy of d.gossipAddr.
//
// Disco.gossipAddr defaults to ":55777".
func (d Disco) GossipAddr() string {
	return d.gossipAddr
}

// ----------------------------------------------------------------------------

// StartDiscovery starts the whole discovery process.
//
// This runs asynchronously, to stop the discovery process, use StopDiscovery()
func (d *Disco) StartDiscovery() error {
	addrs, lerrs, lstop, lerr := broadcastListen(d.broadcastPort)
	if lerr != nil {
		return lerr
	}

	d.stopListening = lstop

	go func() {
		for {
			select {
			case addr := <-addrs:
				log.Printf("(%p) discovered: %v", d, addr)
			case lerr := <-lerrs:
				log.Println("error:", lerr)
			}
		}
	}()

	berrs, bstop, berr := broadcastBeacon(d.broadcastSubnet, d.broadcastPort, d.broadcastInterval)
	if berr != nil {
		return berr
	}

	d.stopBeaconing = bstop

	go func() {
		for {
			select {
			case berr := <-berrs:
				log.Println("error:", berr)
			}
		}
	}()

	gerrs, gstop, gerr := d.gossiper.rpcListen(d.gossipAddr)
	if gerr != nil {
		return gerr
	}

	d.stopGossiping = gstop

	go func() {
		for {
			select {
			case gerr := <-gerrs:
				log.Println("error:", gerr)
			}
		}
	}()

	return nil
}

// ----------------------------------------------------------------------------
