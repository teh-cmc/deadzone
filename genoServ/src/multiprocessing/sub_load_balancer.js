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
os = require("os");

// GS modules
GS_SETTINGS = require("../settings/__settings__.js");
GS_MISC = require("../misc/__misc__.js");
Worker = require("./worker.js");

var SubLoadBalancer = function (p) {
  var that = {};

  // PRIVATE //

  var __log = "GS SUBLOADBALANCER: ";
  var __settings = GS_SETTINGS.LoadBalancer();
  var __running = false;
  var __workers = new Array();
  var __workers_ordered = new Array();
  var __nb_workers = 0;

  var __init = function () {
    var rd = __settings.getInitRetryDelay();

    if (__running) {
      throw GS_MISC.Exception("alreadyInitException", "you dun goofed!");
    }
    if (__buildWorkers() === __nb_workers) {
      console.log(__log + "initialized");
      __running = true;
      p.send({
        IPC: "running"
      });
    } else {
      console.log(__log + "some workers could not be built or were not ready yet," +
                  " retrying in " + rd + "ms...");
      setTimeout(__init, rd);
    }
  };

  var __onDisconnect = function () {
    if (!__running) {
      throw GS_MISC.Exception("alreadyKilledException", "you dun goofed!");
    }
    for (var i = 0; i < __nb_workers; i += 1) {
        __workers_ordered[i].worker.disconnect();
        delete __workers_ordered[i];
        __workers = new Array();
        __workers_ordered = new Array();
    }
    __running = false;
    console.log(__log + "IPC closed, killing my workers and myself");
    p.exit();
  };

  var __onMessage = function (m, o) {
    if (m.IPC === "socket") {
      var w = __workers[0].worker;

      console.log(__log + "dispatching " + o.remoteAddress +
                  " to worker #" + (w.getId() + 1));
      w.handleSocket(m.data, o);
      __incWorker(0);
      that.workersState();
    }
  };

  var __buildWorkers = function () {
    var r = 0;

    for (var i = 0; i < __nb_workers; i += 1) {
      if (typeof __workers[i] === "undefined") {
        console.log(__log + "building worker #" + (i + 1));
        __workers[i] = {
          worker:     Worker(i, that),
          nb_clients: 0,
          pos:        i
        };
      } else if (!__workers[i].worker.getRunning()) {
        console.log(__log + "rebuilding worker #" + (i + 1));
        try {
          __workers[i].worker.disconnect();
        } catch(e) {
          /* disconnection failed, NGAF */
        }
        delete __workers[i];
        __workers[i] = {
          worker:     Worker(i, that),
          nb_clients: 0,
          pos:        i
        };
      } else {
        r += 1;
        __workers_ordered[i] = __workers[i];
      }
    }
    return r;
  };

  var __incWorker = function (pos) {
    var w_tmp = __workers[pos];
    var npos = w_tmp.pos + 1;

    w_tmp.nb_clients += 1;
    while (npos < __nb_workers &&
           w_tmp.nb_clients > __workers[npos].nb_clients) {
      __workers[w_tmp.pos] = __workers[npos];
      __workers[npos] = w_tmp;
      __workers[w_tmp.pos].pos -= 1;
      w_tmp.pos += 1;
      npos += 1;
    }
  };

  var __decWorker = function (pos) {
    var w_tmp = __workers[pos];
    var ppos = w_tmp.pos - 1;

    w_tmp.nb_clients -= 1;
    while (w_tmp.pos > 0 && w_tmp.nb_clients < __workers[ppos].nb_clients) {
      __workers[w_tmp.pos] = __workers[ppos];
      __workers[ppos] = w_tmp;
      __workers[w_tmp.pos].pos += 1;
      w_tmp.pos -= 1;
      ppos -= 1;
    }
  };

  // PUBLIC //

  that.workersState = function () {
    var slot = 0;

    console.log("\n-------------");
    console.log("WORKERS STATE");
    console.log("-------------\n");
    for (var i = 0; i < __nb_workers; i += 1) {
      slot = i < 10 ? "0" + i : i.toString();
      console.log("SLOT #" + slot + ": Worker #" + (__workers[i].worker.getId() + 1) +
                  " handling " + __workers[i].nb_clients + " (" +
                  __workers[i].worker.getNbClients() + ") --- " + __workers[i].pos);
    }
    console.log("\n");
  }

  that.getRunning = function () {
    return __running;
  };

  that.socketDisconnected = function (id) {
    __decWorker(__workers_ordered[id].pos);
    that.workersState();
  };

  that.globalPost = function (data, id) {
    var nop = __workers_ordered[id].pos;

    for (var i = 0; i < __nb_workers; i += 1) {
      if (i !== nop) {
        __workers[i].worker.globalPostDown(data);
      }
    }
  };

  // INIT //

  __nb_workers = function () {
    var nb_workers = __settings.getNbWorkers();

    if (typeof nb_workers !== "number" || nb_workers === 0) {
      return os.cpus().length;
    } else {
      return nb_workers;
    }
  }();

  p.on("disconnect", __onDisconnect);
  p.on("message", __onMessage);
  __init();

  return that;
};

module.exports = SubLoadBalancer;