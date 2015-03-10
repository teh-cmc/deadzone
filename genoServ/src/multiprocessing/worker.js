/**
 * Worker class
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

var Worker = function (id, slb) {
  // `inherit` screws IPC for some obscure reason
  // beware not to overload child_process stuff
  // var that = Object.inherit(require("child_process")
  //                  .fork(GS_SETTINGS.Worker().getScript()));
  var that = require("child_process").fork(GS_SETTINGS.Worker().getScript());

  // PRIVATE //

  var __log = "GS WORKER " + "#" + (id + 1) + ": ";
  var __running = false;
  var __nb_clients = 0;

  var __onMessage = function (m, o) {
    if (m.IPC === "running") {
      __running = true;
      console.log(__log + "initialized");
    } else if (m.IPC === "clientDisconnected") {
      __nb_clients -= 1;
      slb.socketDisconnected(id);
    } else if (m.IPC === "globalPostUp") {
      slb.globalPost(m.data, id);
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

  that.getId = function () {
    return id;
  };

  that.getRunning = function () {
    return __running;
  };

  that.getNbClients = function () {
    return __nb_clients;
  };

  that.handleSocket = function (d, s) {
    that.send({
      IPC: "client",
      data: d,
    }, s);
    __nb_clients += 1;
  };

  that.globalPostDown = function (data) {
    that.send({
      IPC:  "globalPostDown",
      data: data
    });
  };

  // INIT //

  that.on("message", __onMessage);
  that.send({
    IPC:  "id",
    data: id
  })

  return that;
};

module.exports = Worker;