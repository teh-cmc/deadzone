/**
 * Client class
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
require("buffer");

// GS modules
GS_MISC = require("../misc/__misc__.js");
GS_SETTINGS = require("../settings/__settings__.js");
GS_PROTOCOL = require("../protocol/__protocol__.js");

var Client = function (s, ui, sw, ldb, serv) {
  var that = Object.inherit(s);

  // DEFAULT PARAMETERS //

  sw = typeof(sw) !== "undefined" ? sw : null;
  ldb = typeof(ldb) !== "undefined" ? ldb : null;
  serv = typeof(serv) !== "undefined" ? serv : null;

  // PRIVATE //

  var __protocol_settings = {
    buffer_encoding:  GS_SETTINGS.Protocol().getBufferEncoding(),
    buffer_max_size:  GS_SETTINGS.Protocol().getBufferMaxSize(),
    buffer_stop:      GS_SETTINGS.Protocol().getBufferStop(),
    ditching_throws:  GS_SETTINGS.Protocol().getRequestDitchingThrows()
  };
  var __net_infos = {
    host: that.remoteAddress,
    port: that.remotePort
  };
  var __buffer = new Buffer(__protocol_settings.buffer_max_size);
  var __buffer_size = 0;
  var __request_handler = GS_PROTOCOL.RequestHandler(ldb);
  var __answer_handler = GS_PROTOCOL.AnswerHandler();
  var __authed = Boolean(!serv);
  var __kicked = false;
  var __disconnected = false;

  var __onData = function (data) {
    var d = new Buffer(data, __protocol_settings.buffer_encoding);
    var stop = 0;

    try {
      if (d.length + __buffer_size > __protocol_settings.buffer_max_size) {
        throw GS_MISC.Exception("bufferOOMException", "buffer out of memory");
      }
      d.copy(__buffer, __buffer_size);
      __buffer_size += d.length;
      while (true) {
        stop = __buffer.toString().indexOf(__protocol_settings.buffer_stop);
        if (stop >= 0) {
          __treatRequest(stop);
        } else {
          break;
        }
      }
    } catch(e) {
      __leave(e.message, true);
    }
  };

  var __onClose = function (err) {
    __disconnected = true;
    if (!__kicked) {
      __leave(err ? err : "disconnected by user");
    }
    if (__authed) {
      sw.clientDisconnected(that, err);
    } else {
      serv.anonDisconnected(ui.id);
    }
  };

  var __treatRequest = function (stop) {
    var r = null;
    var rstop = stop + 2;

    try {
      r = JSON.parse(__buffer.toString(__protocol_settings.buffer_encoding, 0, stop));
    } catch(e) {
      if (e.name === "SyntaxError") {
        console.log(that.netInfos() + ": request ditched, not JSON");
        if (__protocol_settings.ditching_throws) {
          e.message = "non-JSON buffer-stopped request";
          throw e;
        }
      }
    }
    __buffer_size -= rstop;
    __buffer.copy(__buffer, 0, rstop, __buffer._length - rstop);
    __request_handler.buildHandler(r, ui.rights)(r, that);
  };

  var __leave = function (reason, kicked) {
    kicked = typeof(kicked) !== "undefined" ? kicked : false;
    var request = {
      request:  kicked ? "kick" : "disconnect",
      username: ui.username,
      reason:   reason
    };
    var rights = {
      server: true,
      admin:  false,
      user:   false,
      anon:   false
    };

    __kicked = kicked;
    __request_handler.buildHandler(request, rights)(request, that);
  };

  // PUBLIC //

  that.getAuthed = function () {
    return __authed;
  };

  that.getKicked = function () {
    return __kicked;
  };

  that.getDisconnected = function () {
    return __disconnected;
  };

  that.netInfos = function () {
    return __net_infos.host + ":" + __net_infos.port;
  };

  that.getNetInfos = function () {
    return __net_infos;
  };

  that.userInfos = function () {
    var r = "#" + ui.id + " " + ui.username + " - ";

    ui.rights.forDict(function (k, v) {
      r += k + ":" + v + " ";
    });
    if (__authed) {
      r += "<AUTH'D>"
    }
    r += " -";
    return r;
  };

  that.getUserInfos = function () {
    return ui;
  };

  that.setUserInfos = function (infos) {
    ui.username = infos.username ? infos.username : ui.username;
    ui.rights = infos.rights ? infos.rights : ui.rights;
  };

  that.post = function (data, global, kick) {
    global = typeof(global) !== "undefined" ? global : false;
    kick = typeof(kick) !== "undefined" ? kick : false;
    var b = new Buffer(data, __protocol_settings.buffer_encoding);

    if (global && __authed) {
      sw.globalPostUp(data, ui.id);
    }
    if (kick) {
      that.end(b);
    } else if (!__disconnected) {
      that.write(b);
    }
    console.log(that.bytesWritten + " bytes written to " + that.netInfos());
  };

   that.moveToAuthLand = function () {
    that.pause();
    serv.moveToAuthLand(ui.id);
  };

  // INIT //

  that.on("data", __onData);
  that.on("close", __onClose);
  that.setNoDelay(true);
  that.setKeepAlive(false);
  that.setEncoding(__protocol_settings.buffer_encoding);
  that.resume();

  return that;
};

module.exports = Client;