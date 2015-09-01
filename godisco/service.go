// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package godisco

import (
	"net"

	"github.com/blang/semver"
)

// ----------------------------------------------------------------------------

// Service represents a service on the network.
type Service struct {
	ip net.IP

	name    string
	version semver.Version
}

// ----------------------------------------------------------------------------

// IP returns the net.IP associated with the service.
func (s Service) IP() net.IP {
	return s.ip
}

// Name returns the name associated with the service.
func (s Service) Name() string {
	return s.name
}

// Version returns the version of the service.
func (s Service) Version() semver.Version {
	return s.version
}
