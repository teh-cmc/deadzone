/**
 * settings module
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

var GS_SETTINGS = {
  Server:          require("./server.js"),
  Client:          require("./client.js"),
  Protocol:        require("./protocol.js"),
  LoadBalancer:    require("./load_balancer.js"),
  Worker:          require("./worker.js"),
  LevelDb:         require("./leveldb.js")
};

module.exports = GS_SETTINGS;