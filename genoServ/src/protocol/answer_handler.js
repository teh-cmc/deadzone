/**
 * AnswerHandler class
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
GS_PROTOCOL = require("../protocol/__protocol__.js");

var AnswerHandler = function () {
  var that = {};

  // PRIVATE //

  var __stop = GS_SETTINGS.Protocol().getBufferStop();
  var __answers = {
    /* kick */
    kick: function (r, s) {
      return {
        username: r.username,
        reason:   r.reason
      }
    },
    /* disconnect */
    disconnect: function (r, s) {
      return {
        username: r.username,
        reason:   r.reason
      }
    },
    /* signUp */
    signUp: function (r, s) {
      var ret = {
        status: s
      };

      if (s === "success") {
        ret.username =  r.username;
      }
      return ret;
    },
    /* signUp */
    signIn: function (r, s) {
      var ret = {
        status: s
      };

      if (s === "success") {
        ret.username =  r.username;
      }
      return ret;
    },
    /* signDown */
    signDown: function (r, s) {
      var ret = {
        status: s
      };

      if (s === "success") {
        ret.username =  r.username;
      }
      return ret;
    }
  };

  // PUBLIC //

  that.buildAnswer = function (r, s) {
    var a = __answers[r.request](r, s);

    a.request = r.request;
    return JSON.stringify(a) + __stop;
  };

  // INIT //

  return that;
};

module.exports = AnswerHandler;