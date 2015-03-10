#!/usr/bin/env python

##
# Toolbox
# Copyright (C) 2013  Clement 'cmc' Rey <cr.rey.clement@gmail.com>
#
# This file is part of SSSC-Desktop.
#
# SSSC-Desktop is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

class Toolbox:
  """
  Simple toolbox, might come in handy
  """

###
# BUILDING STUFF
###

  def __init__(self, v):
    """
    constructor
    `v` as in verbosity
    """
    self.__colors = { "grey":    "\033[00;30m",
                      "red":     "\033[00;31m",
                      "green":   "\033[00;32m",
                      "yellow":  "\033[00;33m",
                      "blue":    "\033[00;34m",
                      "pink":    "\033[00;35m",
                      "cyan":    "\033[00;36m",
                      "white":   "\033[00;37m",
                      "bgrey":    "\033[01;30m",
                      "bred":     "\033[01;31m",
                      "bgreen":   "\033[01;32m",
                      "byellow":  "\033[01;33m",
                      "bblue":    "\033[01;34m",
                      "bpink":    "\033[01;35m",
                      "bcyan":    "\033[01;36m",
                      "bwhite":   "\033[01;37m" }
    self.__verbosity = v

###
# PUBLIC STUFF
###

  @staticmethod
  def pygrect_to_vertices(rect):
    """
    PygRect to [(x, y), (x, y), (x, y), (x, y)]
    """
    return [ (rect[0], rect[1]),
             (rect[0] + rect[2], rect[1]),
             (rect[0] + rect[2], rect[1] + rect[3]),
             (rect[0], rect[1] + rect[3]) ]

  @staticmethod
  def pygrect_to_vertices_ry(rect):
    """
    PygRect to [(x, y), (x, y), (x, y), (x, y)]
    reversed y-axis
    """
    from pygame import display as pyg_display

    h = pyg_display.get_surface().get_height()
    return [ (rect[0], h - rect[1]),
             (rect[0] + rect[2], h - rect[1]),
             (rect[0] + rect[2], h - rect[1] - rect[3]),
             (rect[0], h - rect[1] - rect[3]) ]

  @staticmethod
  def usleep(usec):
    """
    sleeps for `usec` microseconds
    """
    from time import sleep as time_sleep

    time_sleep(usec / 1000000.0)

  def load_image(self, name):
    """
    loads image `name` and handles convertion
    """
    import os
    from pygame import error as pyg_error
    from pygame import image as pyg_image

    path = os.path.join("resources", name)
    try:
            image = pyg_image.load(path)
            image = image.convert() if image.get_alpha() == None else image.convert_alpha()
    except pyg_error, err:
      self.talk("could not load image `{0}`: {1}".format(path, err))
      raise Exception
    return image, image.get_rect()

  def talk(self, msg, mood):
    """
    prints in corresponding `mood` color if verbosity enabled
    """
    if not self.__verbosity:
      return
    if mood == "happy":
      print(self.__colors["bgreen"] + msg + self.__colors["white"])
    elif mood == "neutral":
      print(self.__colors["byellow"] + msg + self.__colors["white"])
    elif mood == "sad":
      print(self.__colors["bred"] + msg + self.__colors["white"])
    elif mood == "mad":
      print(self.__colors["bred"] + msg + self.__colors["white"])
      raise Exception
    else:
      print(msg)
