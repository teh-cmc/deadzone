/**
 * server settings
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

var Server = function () {
  var that = {};

  // PRIVATE //

  var __verbose = true;

  var __host = "0.0.0.0";
  var __port = 1337;
  var __backlog = 511;
  var __name = "genoServ I";

  var __users_limit = 1;

  var __init_retry_delay = 750;
  var __listen_retry_delay = 750;
  var __kill_retry_delay = 750;

  // PUBLIC //

  that.getVerbose = function () {
    return __verbose;
  };

  that.getHost = function () {
    return __host;
  };

  that.getPort = function () {
    return __port;
  };

  that.getBacklog = function () {
    return __backlog;
  };

  that.getName = function () {
    return that.__name;
  };

  that.getUsersLimit = function () {
    return __users_limit;
  };

  that.getInitRetryDelay = function () {
    return __init_retry_delay;
  };

  that.getListenRetryDelay = function () {
    return __listen_retry_delay;
  };

  that.getKillRetryDelay = function () {
    return __kill_retry_delay;
  };

  return that;
};

module.exports = Server;