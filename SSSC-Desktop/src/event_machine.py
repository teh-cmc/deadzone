#!/usr/bin/env python

##
# Event machine
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

class EventMachine:
  """
  handles event related stuff
  """

###
# BUILDING STUFF
###

  def __init__(self, t, *ignored):
    """
    constructor
    `t` being the toolbox main instance
    `ignored` = names of ignored events
    """
    from pygame import event as pyg_event

    self.__toolbox = t
    pyg_event.set_blocked(ignored)

###
# PUBLIC STUFF
###

  def compute(self):
    """
    gets and treats current events in the queue
    returns False upon system exit event
    """
    from pygame import event as pyg_event
    import pygame.locals as pyg_constants

    for e in pyg_event.get():
      if e.type == pyg_constants.QUIT:
        return False
    return True
