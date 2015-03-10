/**
 * User class
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

// GS modules
GS_SETTINGS = require("../settings/__settings__.js");

var User = function (ldb) {
  var that = {};

  // PRIVATE //

  var __client_settings = GS_SETTINGS.Client();

  // PUBLIC //

  that.addUser = function (username, password, cb) {
    if (!__client_settings.getUsernameSyntax().test(username)) {
      return cb("invalidUsername");
    } else if (!__client_settings.getPasswordSyntax().test(password)) {
      return cb("invalidPassword");
    }
    that.getUser(username, function (s, u) {
      if (s === "success") {
        return cb("alreadyExist");
      } else if (s === "failure") {
        return cb("failure");
      }
      ldb.put(username, {
        password: password,
        rights: {
          admin: false,
          user: true,
          anon: false
        }
      }, function (e) {
        cb(e ? "failure" : "success");
      });
    })
  };

  that.getUser = function (username, cb) {
    ldb.get(username, function (e, v) {
      if (e) {
        if (e.notFound) {
          return cb("doesNotExist", null);
        } else {
          return cb("failure", null);
        }
      }
      v.username = username;
      cb("success", v);
    });
  };

  that.delUser = function (username, cb) {
    that.getUser(username, function (s, u) {
      if (s === "doesNotExist") {
        return cb("doesNotExist");
      } else if (s === "failure") {
        return cb("failure");
      }
      ldb.del(username, function (e) {
        cb(e ? "failure" : "success");
      })
    });
  };

  // INIT //

  return that;
};

module.exports = User;