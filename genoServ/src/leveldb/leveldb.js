/**
 * LevelDb class
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
levelup = require("levelup");

// GS modules
GS_SETTINGS = require("../settings/__settings__.js");
GS_MISC = require("../misc/__misc__.js");

var LevelDb = function () {
  var that = {};

  // PRIVATE //

  var __log = "GS LEVELDB: ";
  var __settings = GS_SETTINGS.LevelDb();
  var __ldb = null;
  var __running = false;

  var __init = function (e, ldb) {
    var rd = __settings.getInitRetryDelay();

    if (e) {
      console.log(__log + "error while initializing LevelDB, retrying in " +
        rd + "ms... (" + e + ")");
      setTimeout(that.init, rd);
    } else {
      __ldb = ldb;
      __running = true;
      console.log(__log + "initialized");
    }
  };

  var __kill = function (e) {
    var kd = __settings.getKillRetryDelay();

    if (e) {
      console.log("error while killing LevelDB, retrying in " +
                  kd + "ms...");
      setTimeout(that.kill, kd);
    } else {
      __running = false;
      delete __ldb;
      __ldb = null;
      console.log(__log + "killed");
    }
  };

  // PUBLIC //

  that.getRunning = function () {
    return __running;
  };

  that.init = function () {
    var settings = {
      createIfMissing: __settings.getAutocreate(),
      errorIfExists: __settings.getExistsError(),
      cacheSize: __settings.getCacheSize(),
      keyEncoding: __settings.getKeyEncoding(),
      valueEncoding: __settings.getValueEncoding()
    };

    if (__running) {
      throw GS_MISC.Exception("alreadyInitException", "you dun goofed!");
    }
    levelup(__settings.getPath(), settings, __init);
  };

  that.kill = function () {
    if (!__running) {
      throw GS_MISC.Exception("alreadyKilledException", "you dun goofed!");
    }
    __ldb.close(__kill);
  };

  that.put = function (k, v, c) {
    __ldb.put(k, v, c);
  };

  that.get = function (k, c) {
    __ldb.get(k, c);
  };

  that.del = function (k, c) {
    __ldb.del(k, c);
  };

  // INIT //

  that.init();

  return that;
};

module.exports = LevelDb;