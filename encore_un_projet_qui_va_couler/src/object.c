/**
 * abstract object
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

#include <object.h>
#include <object_rect.h>
#include <log.h>

/* ----------------------------------- */

OBJECTObj*
OBJECT_build(OBJECTTYPE type) {
    OBJECTObj* obj = NULL;

    if (!(obj = (OBJECTObj*)g_malloc0(sizeof(*obj)))) {
        M_LOG__ERROR("Could not build OBJECTObj", 0);
        return NULL;
    }

    obj->type = type;

    if (type == OBJECTTYPE_ABSTRACT) obj->__vtable.destroy = OBJECT_destroy;

    return obj;
}

gpointer
OBJECT_destroy(gpointer gp) {
    OBJECTObj*  obj = (OBJECTObj*)gp;

    g_free(obj);

    return NULL;
}