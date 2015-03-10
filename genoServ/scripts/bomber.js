/**
 * simple bomber script
 * spams server with clients connections
 * Copyright (C) 2013  Clement 'cmc' Rey <cr.rey.clement@gmail.com>
 *
 * This file is part of genoServ.
 *
 * genoServ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

// nodejs modules
require("console");
Socket = require("net").Socket;

var run = function () {
  var params = {
    host:     "localhost",
    port:     1337,
    clients:  66666,
    dc:       false
  };
  var s = null;

  process.argv.forEach(function(v, i, a) {
    var r = [];

    if (i >= 2) {
      r = v.split("=");
      if (r[0] in params) {
        params[r[0]] = r[1];
      }
    }
  });
  params.host = params.host.toString();
  params.port = parseInt(params.port);
  params.clients = parseInt(params.clients);
  params.dc = (params.dc.toString().toLowerCase() === "true");
  console.log("Bombing " + params.host + ":" + params.port + " with "+
              params.clients + " clients (auto-disconnect = " + params.dc + ")");
  for (var i = 0; i < params.clients; i += 1) {
    s = new Socket();
    s.on("connect", function () {
      if (params.dc) {
        this.end("sup?", "utf8");
      } else {
        this.write("sup?", "utf8");
      }
    })
    s.connect(params.port, params.host);
  }
}();