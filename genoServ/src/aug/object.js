/**
 * augmenting Object
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

// From "JS: The good parts"
Object.prototype.inherit = function (o) {
  var F = function () {};

  F.prototype = o;
  return new F();
};

Object.prototype.isEmpty = function() {
  for (var prop in this) {
    if (this.hasOwnProperty(prop)) {
      return false;
    }
  }
  return true;
};

Object.prototype.forDict = function (c) {
  for (var k in this) {
    if (this.hasOwnProperty(k)) {
      c(k, this[k]);
    }
  }
};