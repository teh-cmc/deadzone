/**
 * leveldb settings
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

var LevelDb = function () {
  var that = {};

  // PRIVATE //

  var __path = "resources/leveldb";
  var __autocreate = true;
  var __exists_error = false;
  var __cache_size = 8 * 1024 * 1024;
  var __key_encoding = "utf8";
  var __value_encoding = "json";
  var __init_retry_delay = 250;
  var __kill_retry_delay = 250;

  // PUBLIC //

  that.getPath = function () {
    return __path;
  };

  that.getAutocreate = function () {
    return __autocreate;
  };

  that.getExistsError = function () {
    return __exists_error;
  };

  that.getCacheSize = function () {
    return __cache_size;
  };

  that.getKeyEncoding = function () {
    return __key_encoding;
  };

  that.getValueEncoding = function () {
    return __value_encoding;
  };

  that.getInitRetryDelay = function () {
    return __init_retry_delay;
  };

  that.getKillRetryDelay = function () {
    return __kill_retry_delay;
  };

  return that;
};

module.exports = LevelDb;