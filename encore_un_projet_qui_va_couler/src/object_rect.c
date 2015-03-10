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

#include <object_rect.h>
#include <log.h>

/* ----------------------------------- */

OBJECTObj*
OBJECT_RECT_build(guint w, guint h) {
    OBJECT_RECTObj* rect = NULL;

    if (!(rect = (OBJECT_RECTObj*)g_malloc0(sizeof(*rect)))) {
        M_LOG__ERROR("Could not build OBJECT_RECTObj", 0);
        return OBJECT_destroy(&rect->__obj);
    }

    rect->__obj.type = OBJECTTYPE_RECT;
    rect->__obj.__vtable.destroy = OBJECT_RECT_destroy;

    rect->w = w;
    rect->h = h;

    return &rect->__obj;
}

gpointer
OBJECT_RECT_destroy(gpointer gp) {
    OBJECT_RECTObj*  rect = M_OBJECT__VCAST(gp, OBJECT_RECTObj);

    g_free(rect);

    return NULL;
}