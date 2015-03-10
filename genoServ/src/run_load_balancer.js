/**
 * load balancer' main()
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

// preloads types augmentations
require("./aug/__aug__.js");

// GS modules
GS_SETTINGS = require("./settings/__settings__.js");
GS_MULTIPROCESSING = require("./multiprocessing/__multiprocessing__.js");

if (!GS_SETTINGS.Server().getVerbose()) {
  console.log = function () {};
}

process.on("uncaughtException", function (e) {
  console.log("\n<< UNCAUGHT EXCEPTION @ LOAD BALANCER THREAD >>");
  console.log(e.name);
  console.log(e.message);
  console.log(e.stack);
  console.log("\n");
});

(function run_worker () {
  var lb = GS_MULTIPROCESSING.SubLoadBalancer(process);

  /* that's it! */
})();

