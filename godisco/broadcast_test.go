// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package godisco

import (
	"net"
	"sync"
	"testing"
	"time"
)

// ----------------------------------------------------------------------------

func TestBroadcast_cidrToBroadcast(t *testing.T) {
	var bip net.IP
	var err error

	checkResult := func(cidr, expectedBIP string) {
		bip, err = cidrToBroadcast(cidr)
		if err != nil {
			t.Error(err)
		}
		if bip.String() != expectedBIP {
			t.Errorf("%s should be %s", bip, expectedBIP)
		}
	}

	checkResult("192.168.5.0/26", "192.168.5.63")
	checkResult("192.168.5.64/26", "192.168.5.127")
	checkResult("192.168.5.128/26", "192.168.5.191")
	checkResult("192.168.5.192/26", "192.168.5.255")

	_, err = cidrToBroadcast("192.168.0.0")
	if err == nil || err.(*net.ParseError).Type != "CIDR address" {
		t.Error(err)
	}

	_, err = cidrToBroadcast("2001:0db8:0000:0000:0000:ff00:0042:8329/64")
	if err == nil || err.(BroadcastError).Type() != ErrIPv6NotSupported {
		t.Error(err)
	}
}

func TestBroadcast_broadcastXXX(t *testing.T) {
	subnetCIDR := "127.0.0.1/24"
	port := 55666

	laddrs, lerrs, lstop, lerr := broadcastListen(port)
	if lerr != nil {
		t.Error(lerr)
	}

	var lwg sync.WaitGroup
	lwg.Add(1)
	go func() {
		defer lwg.Done()
		for i := 0; i < 10; i++ {
			select {
			case addr := <-laddrs:
				t.Log(addr)
			case lerr := <-lerrs:
				t.Error(lerr)
			}
		}
		close(lstop)
		for range laddrs {
		}
		for lerr := range lerrs {
			t.Error(lerr)
		}
	}()

	berrs, bstop, berr := broadcastBeacon(subnetCIDR, port, time.Millisecond*250)
	if berr != nil {
		t.Error(berr)
	}

	lwg.Wait()

	close(bstop)
	for berr := range berrs {
		t.Error(berr)
	}
}
