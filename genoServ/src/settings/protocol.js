/**
 * protocol settings
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

var Protocol = function () {
  var that = {};

  // PRIVATE //

  var __buffer_stop = "\r\n";
  var __buffer_encoding = "utf8";
  var __buffer_max_size = 4096;

  var __request_checking = true;
  var __request_ditching_throws = true;

  // PUBLIC //

  that.getBufferStop = function () {
    return __buffer_stop;
  };

  that.getBufferEncoding = function () {
    return __buffer_encoding;
  };

  that.getBufferMaxSize = function () {
    return __buffer_max_size;
  };

  that.getRequestChecking = function () {
    return __request_checking;
  };

  that.getRequestDitchingThrows = function () {
    return __request_ditching_throws;
  };

  return that;
};

module.exports = Protocol;