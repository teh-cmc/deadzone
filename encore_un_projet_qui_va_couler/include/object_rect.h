/**
 * simple rectangle object
 * Copyright (C) 2014  Clement 'cmc' Rey <cr.rey.clement@gmail.com>
 *
 * This file is part of EUPQVC.
 *
 * EUPQVC is free software: you can redistribute it and/or modify
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

#ifndef OBJECT_RECT_H
#define OBJECT_RECT_H

/* ----------------------------------- */

#include <SDL.h>
#include <glib.h>

#include <object.h>

/* ----------------------------------- */

typedef struct s_object_rect__obj {
    guint           w;
    guint           h;

    OBJECTObj       __obj; /* vparent */
} OBJECT_RECTObj;

/* ----------------------------------- */

OBJECTObj*
OBJECT_RECT_build(guint w, guint h);

/* should be call via M_OBJECT__DESTROY */
gpointer
OBJECT_RECT_destroy(gpointer gp);

#endif
