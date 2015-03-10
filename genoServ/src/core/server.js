/**
 * Server class
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
require("buffer");

// GS modules
GS_CLIENT = require("../client/__client__.js");
GS_SETTINGS = require("../settings/__settings__.js");
GS_MISC = require("../misc/__misc__.js");

var Server = function (lb, ldb) {
  var that = Object.inherit(new require("net").Server());

  // PRIVATE //

  var __log = "GS SERVER: "
  var __settings = GS_SETTINGS.Server();
  var __running = false;
  var __current_id = 0;
  var __anons = new Array();

  var __kill = function () {
    if (!lb.getRunning() && !ldb.getRunning()) {
      that.close();
      __running = false;
      console.log(__log + "killed");
    } else {
      setTimeout(__kill, __settings.getKillRetryDelay());
    }
  };

  var __onError = function (e) {
    var td = __settings.getListenRetryDelay();

    if (e.code == "EADDRINUSE") {
      console.log(__log + __settings.getHost() + ":" + __settings.getPort() +
                  " is already in use, retrying in " + td + "ms...");
      setTimeout(that.init, td);
    }
  };

  var __onClose = function () {
    console.log(__log + "terminating");
    process.exit();
  };

  var __onListening = function () {
    console.log(__log + "initialized");
    console.log(__log + "now listening on " + __settings.getHost() +
                ":" + __settings.getPort());
    __running = true;
  };

  var __onConnection = function (s) {
    var ui = {
      id:        __current_id++,
      username: "anonymous",
      rights: {
        server: false,
        admin:  false,
        user:   false,
        anon:   true
      }
    }
    var c = GS_CLIENT.Client(s, ui, null, ldb, that);

    __anons.push(c);
    console.log(__log + "new connection from " + c.netInfos() +
                " [" + c.userInfos() + " ] (" + __anons.length + " anons total)");
  };

  var __getAnonIndex = function (id) {
    for (var i = 0; i < __anons.length; i += 1) {
      if (__anons[i].getUserInfos().id === id) {
        return i;
      }
    }
    return -1;
  };

  var __popAnon = function (id) {
    var i = __getAnonIndex(id);

    return __anons.splice(i, 1)[0];
  };

  // PUBLIC //

  that.getRunning = function () {
    return __running;
  };

  that.init = function () {
    rd = __settings.getInitRetryDelay();

    if (lb.getRunning() && ldb.getRunning()) {
      that.listen(__settings.getPort(),
                  __settings.getHost(),
                  __settings.getBacklog());
    } else {
      console.log(__log + "LB and/or LDB modules are not ready, retrying in " +
                  rd + "ms...");
      setTimeout(that.init, rd);
    }
  };

  that.kill = function () {
    if (!__running) {
      throw GS_MISC.Exception("alreadyKilledException", "you dun goofed!");
    }
    lb.disconnect();
    ldb.kill();
    __kill();
  };

  that.moveToAuthLand = function (id) {
    var anon = __popAnon(id);

    lb.dispatchSocket(anon);
    console.log(__log + "moving [" + anon.userInfos() + " (" +
                anon.netInfos() + ")] to authland (" +
                __anons.length + " anons total)");
  };

  that.anonDisconnected = function (id) {
    var anon = __popAnon(id);

    console.log(__log + "Anon disconnected [" + anon.userInfos() + " (" +
                anon.netInfos() + ")] - " + __anons.length + " anons total");
  };

  // INIT //

  that.on("error", __onError);
  that.on("listening", __onListening);
  that.on("connection", __onConnection);

  that.init();

  return that;
};

module.exports = Server;