// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package godisco

import (
	"fmt"
	"log"
	"net"
	"os"
	"strconv"
	"syscall"
	"time"
)

// ----------------------------------------------------------------------------

// BroadcastError indicates an error within the broadcasting module.
//
// It implements the error interface.
type BroadcastError struct {
	errorType BroadcastErrorType
	value     interface{}
}

// BroadcastErrorType represents a type-enum for possible broadcast errors.
type BroadcastErrorType int

const (
	// ErrIPv6NotSupported indicates the lack of support for IPv6.
	ErrIPv6NotSupported BroadcastErrorType = 0x01
)

// NewBroadcastError returns a new BroadcastError.
func NewBroadcastError(errorType BroadcastErrorType, value interface{}) BroadcastError {
	return BroadcastError{errorType: errorType, value: value}
}

// Type returns the type of a BroadcastError.
func (e BroadcastError) Type() BroadcastErrorType {
	return e.errorType
}

// Error returns the BroadcastError as a string.
func (e BroadcastError) Error() string {
	switch e.Type() {
	case ErrIPv6NotSupported:
		return fmt.Sprintf("IPv6 addresses are not supported ('%s')", e.value.(string))
	default:
		return "unknown error"
	}
}

// -----------------------------------------------------------------------------

// cidrToBroadcast takes a subnet IPv4 address in CIDR notation
// and returns the associated broadcast address.
func cidrToBroadcast(cidr string) (net.IP, error) {
	ip, subnet, err := net.ParseCIDR(cidr)
	if err != nil {
		return nil, err
	}

	if ip4 := ip.To4(); ip4 == nil {
		return nil, NewBroadcastError(ErrIPv6NotSupported, ip.String())
	}

	var bip [4]byte
	for i := range bip {
		bip[i] = subnet.IP[i] | (subnet.Mask[i] ^ 0xff)
	}
	return net.IPv4(bip[0], bip[1], bip[2], bip[3]), nil
}

// broadcastListen listens to broadcast events on the given `port`.
//
// Close the returned struct{} channel to stop the listening goroutine.
func broadcastListen(port int) (<-chan net.Addr, <-chan error, chan<- struct{}, error) {
	conn, err := net.ListenUDP("udp4", &net.UDPAddr{
		IP:   net.IPv4(0, 0, 0, 0),
		Port: port,
	})
	if err != nil {
		if e, ok := err.(*net.OpError); ok {
			if se, ok := e.Err.(*os.SyscallError); ok && se.Err == syscall.EADDRINUSE {
				// something is already bound to this local port
				// ask it via RPC if it's one of us
				log.Printf("%#v\n", e.Err)
			}
		}
		return nil, nil, nil, err
	}

	addrs := make(chan net.Addr)
	errs := make(chan error)
	stop := make(chan struct{})

	go func() {
		defer conn.Close()
		defer close(addrs)
		defer close(errs)

		var b [4096]byte
		for {
			select {
			case <-stop:
				return
			default:
				_, addr, err := conn.ReadFrom(b[:])
				if err != nil {
					errs <- err
					return
				}
				addrs <- addr
			}
		}
	}()

	return addrs, errs, stop, nil
}

// broadcastBeacon takes an IPv4 subnet address in CIDR notation and sends
// UDP beacons at the assciated broadcast address on the specified `port`.
//
// Close the returned struct{} channel to stop the beaconing goroutine.
func broadcastBeacon(
	cidr string, port int,
	interval time.Duration,
) (<-chan error, chan<- struct{}, error) {
	bip, err := cidrToBroadcast(cidr)
	if err != nil {
		return nil, nil, err
	}

	baddr := net.JoinHostPort(bip.String(), strconv.Itoa(port))

	conn, err := net.Dial("udp4", baddr)
	if err != nil {
		return nil, nil, err
	}

	errs := make(chan error)
	stop := make(chan struct{})

	go func() {
		defer conn.Close()
		defer close(errs)

		// first, send a beacon asap..
		_, err := conn.Write([]byte{'\xff'})
		if err != nil {
			errs <- err
			return
		}

		// ..then start the beacon loop
		for {
			select {
			case <-stop:
				return
			case <-time.After(interval):
				// this currently sends '\xff', but anything would do the trick:
				// GoDisco doesn't care
				_, err := conn.Write([]byte{'\xff'})
				if err != nil {
					errs <- err
					return
				}
			}
		}
	}()

	return errs, stop, nil
}
