#!/usr/bin/env python

##
# Main class
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

class Main:
  """
  initializes
  loops
  clears
  """

##
# BUILDING STUFF
##

  def __init__(self, argv):
    """
    constructor
    takes `argv[1: ]`
    """
    import argparse
    from misc.toolbox import Toolbox

# versioning
    self.__current = "0.1 alpha"
    self.__description = """
                         -- SSSC-Desktop --
                         """
# argparsing
    p = argparse.ArgumentParser(add_help = False, formatter_class = argparse.RawDescriptionHelpFormatter,
                                description = self.__description)
    p.add_argument("-h", "--help", action = "help", help = "shows this help then exits")
    p.add_argument("--version", action = "version", version = "v{version}".format(version = self.__current),
                   help = "shows current version then exits")
    p.add_argument("-d", "--debug", action = "store_true", help = "enables debug mode")
    p.add_argument("-v", "--verbose", action = "store_true", help = "enables verbosity")
# members
    self.__args = p.parse_args(args = argv)
    self.__toolbox = Toolbox(self.__args.verbose)
# pygame and related homemade stuff , will be initialized in init()
    self.__screen = None
    self.__clock = None
    self.__store = None
    self.__event_machine = None

##
# PUBLIC STUFF
##

  def init(self):
    """
    initializes pygame related stuff
    """
    from item_store import ItemStore
    from event_machine import EventMachine
    from pygame import init as pyg_init
    from pygame import display as pyg_display
    from pygame import time as pyg_time
    import pygame.locals as pyg_constants

# inits pure pygame objects
    succeed, failed = pyg_init()
    if succeed:
      self.__toolbox.talk("pygame: {0} modules succesfully loaded".format(str(succeed)), "happy")
    if failed:
      self.__toolbox.talk("pygame: {0} modules could not be loaded".format(str(failed)), "sad")
    self.__screen = pyg_display.set_mode((960, 540), pyg_constants.DOUBLEBUF | pyg_constants.HWSURFACE)
    self.__clock = pyg_time.Clock()
    pyg_display.set_caption("SSSC-Desktop v{0}".format(self.__current), "SSSC-Desktop")
# inits homemade
    self.__store = ItemStore(self.__toolbox)
    self.__store.init()
    self.__event_machine = EventMachine(self.__toolbox,
                                        pyg_constants.MOUSEMOTION,
                                        pyg_constants.MOUSEBUTTONUP,
                                        pyg_constants.MOUSEBUTTONDOWN)

  def run(self):
    """
    starts looping
    """
    from pygame import display as pyg_display

    while self.__event_machine.compute():
      self.__store.update(self.__clock.get_fps())
      self.__store.draw()
      pyg_display.flip()
      self.__clock.tick(120)

  def clear(self):
    """
    clears stuff
    """
    from pygame import quit as pyg_quit

    pyg_quit()

if __name__ == "__main__":
  """
  ./sssc_desktop -h
  """
  import sys

  m = Main(sys.argv[1: ])
  m.init()
  m.run()
  m.clear()
