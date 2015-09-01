// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package godisco

import (
	"net"
	"net/rpc"
	"syscall"
	"testing"
)

// ----------------------------------------------------------------------------

func TestGossiper_rpcListen_Ping(t *testing.T) {
	errs, stop, err := (&Gossiper{}).rpcListen(":55778")
	if err != nil {
		t.Error(err)
	}

	client, err := rpc.Dial("tcp", "localhost:55778")
	if err != nil {
		t.Error(err)
	}
	if err := client.Call("Gossiper.Ping", struct{}{}, nil); err != nil {
		t.Error(err)
	}

	close(stop)

	for e := range errs {
		t.Error(e)
	}

	if err := client.Call("Gossiper.Ping", struct{}{}, nil); err != nil {
		if e, ok := err.(*net.OpError); ok && e.Err == syscall.ECONNRESET {
		} else {
			t.Error(err)
		}
	}
}
