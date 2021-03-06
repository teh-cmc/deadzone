/**
 * load_balancer settings
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

var LoadBalancer = function () {
  var that = {};

  // PRIVATE //

  var __script = "src/run_load_balancer.js";

  /* 0 = number of CPU cores */
  var __nb_workers = 0;
  var __init_retry_delay = 500;

  // PUBLIC //

  that.getScript = function () {
    return __script;
  };

  that.getNbWorkers = function () {
    return __nb_workers;
  };

  that.getInitRetryDelay = function () {
    return __init_retry_delay;
  };

  return that;
};

module.exports = LoadBalancer;