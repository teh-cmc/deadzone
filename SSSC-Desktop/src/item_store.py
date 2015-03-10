#!/usr/bin/env python

##
# Item store
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

class ItemStore:
  """
  holds the different pygame's sprites groups
  dispatches physics, updates, drawings
  """

##
# BUILDING STUFF
##

  def __init__(self, t):
    """
    constructor
    `t` being the toolbox main instance
    """
    from pygame import display as pyg_display
    from pymunk import Space as PymSpace
    import pygame.sprite as pyg_sprite

# members
    self.__toolbox = t
# pygame sprites groups
    self.__background = pyg_sprite.Group()
    self.__statics = pyg_sprite.Group()
    self.__characters = pyg_sprite.LayeredUpdates()
    self.__screen_ref = pyg_display.get_surface()
# stuff for pymunk and physics
    self.__space = PymSpace()
    self.__space.gravity = 0, -1000

##
# PRIVATE STUFF
##

  def __load_background(self):
    """
    loads default background components
    """
    from item import Item

    bg = Item(self.__toolbox)
    bg.init_as_rectangle(self.__screen_ref.get_size(), (150, 150, 150))
    return [bg]

  def __load_statics(self):
    """
    loads default static components
    """
    from item import Item

    c = Item(self.__toolbox)
    c.init_as_rectangle((self.__screen_ref.get_width(), 10), (0, 150, 0),
                        (0, self.__screen_ref.get_height() - 100))
    c.init_physics(self.__space)
    c.add_rectangle(self.__space)
    c.add_rectangle(self.__space, (10, 10, 10, self.__screen_ref.get_height() - 20))
    return [c]

  def __load_characters_fg(self):
    """
    loads default foreground characters
    """
    from item import Item

    mc = Item(self.__toolbox)
    #mc.init((90, 60), (150, 0, 0), (100, 0))
    mc.init_as_image("test.png", (100, 0))
    mc.init_physics(self.__space, 50.0, 500.0)
    mc.add_rectangle(self.__space)
    return [mc]

##
# PUBLIC STUFF
##

  def init(self):
    """
    loads groups content
    """
    self.__background.add(self.__load_background())
    self.__statics.add(self.__load_statics())
    self.__characters.add(self.__load_characters_fg(), layer="fg")

  def update(self, fps):
    """
    updates all groups
    """
    try:
      self.__space.step(1.0 / fps)
    except ZeroDivisionError:
      self.__space.step(1.0 / 120.0)
    self.__characters.update()

  def draw(self):
    """
    draws all groups
    """
    from pymunk.pygame_util import draw_space as pym_draw_space

    self.__background.draw(self.__screen_ref)
    self.__statics.draw(self.__screen_ref)
    self.__characters.draw(self.__screen_ref)
    pym_draw_space(self.__screen_ref, self.__space)
