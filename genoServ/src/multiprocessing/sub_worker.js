/**
 * SubWorker class
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

// GS modules
GS_CLIENT = require("../client/__client__.js");

var SubWorker = function (p) {
  var that = {};

  // PRIVATE //

  var __log = "";
  var __running = false;
  var __clients = new Array();

  var __onMessage = function (m, s) {
    if (m.IPC === "id") {
      __log = "WORKER #" + (m.data + 1) + " (PID #" + p.pid + "): ";
      console.log(__log + "running!");
    } else if (m.IPC === "client") {
      var c = GS_CLIENT.Client(s, m.data, that);

      console.log(__log + "handling new client from " + c.netInfos());
      __clients.push(c);
    } else if (m.IPC === "globalPostDown") {
      for (var i = 0; i < __clients.length; i += 1) {
        __clients[i].post(m.data);
      }
    }
  };

  var __onDisconnect = function () {
    for (var i = 0; i < __clients.length; i += 1) {
      __clients[i].close();
    }
    __running = false;
    console.log(__log + "IPC closed, killing my clients and myself");
    p.exit();
  };

  // PUBLIC //

  that.getRunning = function () {
    return __running;
  };

  that.clientDisconnected = function (c, e) {
    p.send({
      IPC: "clientDisconnected",
      data: c.getUserInfos()
    });
    console.log(__log + "discarding client [" + c.userInfos() + "(" +
                c.netInfos() + ")] <disconnected>");
  };

  that.globalPostUp = function (data, id) {
    p.send({
      IPC:  "globalPostUp",
      data: data,
    });
    for (var i = 0; i < __clients.length; i += 1) {
      if (__clients[i].getUserInfos().id !== id) {
        __clients[i].post(data);
      }
    }
  };

  // INIT //

  p.on("message", __onMessage);
  p.on("disconnect", __onDisconnect);
  p.send({
    IPC: "running"
  });
  __running = true;

  return that;
};

module.exports = SubWorker;