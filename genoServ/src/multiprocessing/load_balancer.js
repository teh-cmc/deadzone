/**
 * LoadBalancer class
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
GS_SETTINGS = require("../settings/__settings__.js");
GS_MISC = require("../misc/__misc__.js");

var LoadBalancer = function () {
  // `inherit` screws IPC for some obscure reason
  // beware not to overload child_process stuff
  // var that = Object.inherit(require("child_process")
  //                  .fork(GS_SETTINGS.LoadBalancer().getScript()));
  var that = require("child_process").fork(GS_SETTINGS.LoadBalancer().getScript());

  // PRIVATE //

  var __log = "GS LOADBALANCER: ";
  var __running = false;

  var __onMessage = function (m, o) {
    if (m.IPC === "running") {
      __running = true;
      console.log(__log + "initialized");
    }
  };

  var __onDisconnect = function () {
    if (!__running) {
      throw GS_MISC.Exception("alreadyKilledException", "you dun goofed!");
    }
    __running = false;
    console.log(__log + "killed");
  };

  // PUBLIC //

  that.getRunning = function () {
    return __running;
  };

  that.dispatchSocket = function (c) {
    that.send({
      IPC:    "socket",
      data:   c.getUserInfos()
    }, c)
  };

  // INIT //

  that.on("message", __onMessage);
  that.on("disconnect", __onDisconnect);

  return that;
};

module.exports = LoadBalancer;