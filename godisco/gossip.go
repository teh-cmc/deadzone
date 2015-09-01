// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package godisco

import (
	"net"
	"net/rpc"
	"sync/atomic"
)

// ----------------------------------------------------------------------------

// Gossiper exports methods for the gossiping RPC server.
type Gossiper struct{}

// ----------------------------------------------------------------------------

// rpcListen listens for RPC events on the given address.
//
// Close the returned struct{} channel to stop the listening goroutine.
func (g *Gossiper) rpcListen(addr string) (<-chan error, chan<- struct{}, error) {
	rpcServer := rpc.NewServer()
	if err := rpcServer.Register(g); err != nil {
		return nil, nil, err
	}
	l, err := net.Listen("tcp", addr)
	if err != nil {
		return nil, nil, err
	}

	errs := make(chan error)
	stop := make(chan struct{})

	go func() {
		defer close(errs)
		defer l.Close()

		closed := int32(0)

		go func() {
			for {
				c, err := l.Accept()
				if err != nil {
					if atomic.LoadInt32(&closed) == 0 {
						errs <- err
					}
					return
				}

				// NOTE: defer in forever loop
				// will defer once the stop channel has been closed
				defer c.Close()

				go rpcServer.ServeConn(c)
			}
		}()

		select {
		case <-stop:
			atomic.StoreInt32(&closed, 1)
			return
		}
	}()

	return errs, stop, nil
}

// ----------------------------------------------------------------------------

// Ping is a RPC method to check if a GoDisco instance is running on a given
// address.
func (g *Gossiper) Ping(_ struct{}, _ *struct{}) error {
	return nil
}
