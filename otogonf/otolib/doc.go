// Copyright 2014 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
// Use of this source code is governed by a MIT
// license that can be found in the ../COPYING file.

/*
Package otolib provides a Go library allowing you to load your config files and to automatically generate REST APIs to handle them remotely

Note: for every example below, the gFlagged variable is:

	gFlagged = {
		"OTO-RDONLY": {
			"OTO-BASICAUTH": {
				"elasticsearch": {
					"ip": "127.0.0.1",
					"user": "mark",
					"password": "knopfler"
				}
			}
		},
		"OTO-BASICAUTH": {
			"couchbase": {
				"default": {
					"ip": "172.17.0.1",
					"port": "8091",
					"OTO-RDONLY": {
						"user": "dennis"
					},
					"OTO-WRONLY": {
						"password": "ritchie"
					}
				}
			}
		},
		"OTO-WRONLY": {
			"pgsql": {
				"username": "gregory",
				"OTO-PRIVATE": {
					"password": "house"
				}
			}
		}
	}

*/
package otolib
