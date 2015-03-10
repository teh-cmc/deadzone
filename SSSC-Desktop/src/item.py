#!/usr/bin/env python

##
# Item
# A pygame Surface with physics that inherits from a pygame Sprite
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

from pygame.sprite import Sprite as PygSprite

class Item(PygSprite):
  """
  a pygame Surface with physics that inherits from a pygame Sprite
  """

##
# BUILDING STUFF
##

  def __init__(self, t):
    """
    constructor
    `t` being the toolbox main instance
    """
    PygSprite.__init__(self)
# members
    self.__toolbox = t
# stuff used by pygame's drawing functions
    self.image = None
    self.rect = None
    self.__image_bu = None
# physics stuff
    self.__body = None

  def init_as_rectangle(self, s, c, p = (0, 0)):
    """
    rectangle shape initializer
    `s` = (w, h)
    `c` = (r, g, b)
    `p` = (x, y)
    """
    from pygame import Surface as PygSurface

# stuff used by pygame's drawing functions
    self.image = PygSurface(s).convert()
    self.image.fill(c)
    self.__image_bu = self.image.copy()
    self.rect = self.image.get_rect().move(p[0], p[1])

  def init_as_image(self, path, p = (0, 0)):
    """
    image initializer
    `p` = (x, y)
    """
# stuff used by pygame's drawing functions
    self.image, self.rect = self.__toolbox.load_image(path)
    self.__image_bu = self.image.copy()
    self.rect = self.image.get_rect().move(p[0], p[1])

  def init_physics(self, space, mass = None, moment = None,
                   friction = 1.0, ctype = 0, cgroup = 0):
    """
    enables physics for this item
    `space` = ref to corresponding virtual physics environment
    `mass` = None if static
    `moment` = None if static
    0.0 <= `friction` <= 1.05
    `ctype` = collision type
    `cgroup` = collision group
    """
    from pymunk import Body as PymBody
    from pygame import display as pyg_display

    if not space:
      self.__toolbox.talk("invalid space specified", "mad")
    self.__body = PymBody(mass, moment)
    self.__body.friction = friction
    self.__body.collision_type = ctype
    self.__body.group = cgroup
    self.__body.position = (self.rect[0], pyg_display.get_surface().get_height() - self.rect[1])
    if mass and moment:
      space.add(self.__body)

##
# PUBLIC STUFF
##

  def add_rectangle(self, space, vertices = None, offset = (0, 0), elasticity = 0.4):
    """
    adds a rectangle to Item's body
    `space` = ref to corresponding virtual physics environment
    `vertices` = PygRect-like (x, y, w, h)
    `offset` = offset from the body's center
    """
    from pymunk import Poly as PymPoly
    from misc.toolbox import Toolbox

    if not space:
      self.__toolbox.talk("invalid space specified", "mad")
    if not self.__body:
      self.__toolbox.talk("physics not enabled for this item", "mad")
    if not vertices:
      vertices = Toolbox.pygrect_to_vertices_ry(self.rect)
    else:
      vertices = Toolbox.pygrect_to_vertices_ry(vertices)
    offset += -self.__body.position
    poly = PymPoly(self.__body, vertices, offset)
    poly.elasticity = elasticity
    space.add(poly)

  def update(self):
    """
    called by pygame sprite groups at each frame
    """
    from pygame import display as pyg_display
    from pygame import transform as pyg_transform
    import math

    try:
      x, y = self.__body.position
      r = self.__body.angle
      self.rect[0] = x
      self.rect[1] = pyg_display.get_surface().get_height() - y
      self.image = pyg_transform.rotate(self.__image_bu, math.degrees(r))
      self.rect = self.image.get_rect(center = self.rect.center)
    except Exception as e:
# TBD
      print e
