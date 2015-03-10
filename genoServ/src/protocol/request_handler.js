/**
 * RequestHandler class
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
GS_MISC = require("../misc/__misc__.js");
GS_SETTINGS = require("../settings/__settings__.js");
GS_LEVELDB = require("../leveldb/__leveldb__.js");
GS_PROTOCOL = require("../protocol/__protocol__.js");

var RequestHandler = function (ldb) {
  var that = {};

  // DEFAULT PARAMETERS //

  ldb = typeof(ldb) !== "undefined" ? ldb : null;

  // PRIVATE //

  var __protocol_settings = GS_SETTINGS.Protocol();
  var __user_ldb = ldb ? GS_LEVELDB.User(ldb) : null;
  var __answer_handler = GS_PROTOCOL.AnswerHandler();
  var __requests = {
    /* kick: kick user */
    kick: {
      rights: {
        server: true,
        admin:  true,
        user:   false,
        anon:   false
      },
      params: [
                "username",
                "reason"
              ],
      handler: function (r, c) {
        c.post(__answer_handler.buildAnswer(r), true, true);
      }
    },
    /* disconnect: gently disconnect user */
    disconnect: {
      rights: {
        server: true,
        admin:  false,
        user:   false,
        anon:   false
      },
      params: [
                "username",
                "reason"
              ],
      handler: function (r, c) {
        c.post(__answer_handler.buildAnswer(r), true);
      }
    },
    /* signUp: user asking to sign up */
    signUp: {
      rights: {
        server: true,
        admin:  true,
        user:   true,
        anon:   true
      },
      params: [
                "username",
                "password"
              ],
      handler: function (r, c) {
        __user_ldb.addUser(r.username, r.password, function (s) {
          c.post(__answer_handler.buildAnswer(r, s));
        })
      }
    },
    /* signIn: user asking to sign in */
    signIn: {
      rights: {
        server: true,
        admin:  false,
        user:   false,
        anon:   true
      },
      params: [
                "username",
                "password"
              ],
      handler: function (r, c) {
        __user_ldb.getUser(r.username, function (s, u) {
          if (s === "success") {
            if (u.password !== r.password) {
              c.post(__answer_handler.buildAnswer(r, "wrongPassword"));
            } else {
              c.post(__answer_handler.buildAnswer(r, s), true);
              c.setUserInfos(u);
              c.moveToAuthLand();
            }
          } else {
            c.post(__answer_handler.buildAnswer(r, s));
          }
        })
      }
    },
    /* signDown: delete user */
    signDown: {
      rights: {
        server: true,
        admin:  true,
        user:   false,
        anon:   false
      },
      params: [
                "username"
              ],
      handler: function (r, c) {
        __user_ldb.delUser(r.username, function (s) {
          c.post(__answer_handler.buildAnswer(r, s));
        })
      }
    }
  };

  var __requestCheck = function (r) {
    var params = null;

    if (!r || typeof r.request === "undefined") {
      throw GS_MISC.Exception("anonymousRequestException",
                                "invalid request (name not specified)");
    }
    params = __requests[r.request].params;
    if (typeof params === "undefined") {
      throw GS_MISC.Exception("invalidRequestException",
                                "invalid request (parameters not specified)");
    }
    for (var i = 0; i < params.length; i += 1) {
      if (typeof r[params[i]] === "undefined") {
        throw GS_MISC.Exception("missingRequestParamsException",
                                  "invalid request (missing required parameters)");
      }
    }
  };

  var __rightsCheck = function (r, rights) {
    var required = __requests[r.request].rights;

    for (var k in required) {
      if (required.hasOwnProperty(k)) {
        if (required[k] && rights[k]) {
          return true;
        }
      }
    }
    return false;
  };

  // PUBLIC //

  that.buildHandler = function (r, rights) {
    if (__protocol_settings.getRequestChecking()) {
      __requestCheck(r);
    }
    if (!__rightsCheck(r, rights)) {
      return function (r, c) {
        c.post(__answer_handler.buildAnswer(r, "insufficientRights"));
      };
    }
    return __requests[r.request].handler;
  };

  // INIT //

  return that;
};

module.exports = RequestHandler;