/**
 * client settings
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

var Client = function () {
  var that = {};

  // PRIVATE //

  var __username_syntax = /^\w{3,20}$/;
  var __password_syntax = /^[\w$-/:-?{-~!"^_`\[\]]{3,30}$/;

  // PUBLIC //

  that.getUsernameSyntax = function () {
    return __username_syntax;
  };

  that.getPasswordSyntax = function () {
    return __password_syntax;
  };

  return that;
};

module.exports = Client;