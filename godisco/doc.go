// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

/*
Package godisco provides an easy-to-use and fully-tested library for
decentralized service discovery.

GoDisco starts by using IPv4 broadcasting to find one or more nodes in the
given subnet, then switches to gossiping once it has found any.
IPv4 and IPv6 multicasting support might be added later if requested.
*/
package godisco
