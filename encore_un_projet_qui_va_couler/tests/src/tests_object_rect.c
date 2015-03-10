/**
 * object_rect module unit tests
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

#include <glib.h>

#include <object_rect.h>
#include <tests_object_rect.h>

/* ----------------------------------- */

void
TESTS_OBJECT_RECT_build(void) {
    OBJECTObj*      obj = OBJECT_RECT_build(42, 66);
    OBJECT_RECTObj* rect = M_OBJECT__VCAST(obj, OBJECT_RECTObj);
    g_assert(obj != NULL);
    g_assert(rect != NULL);

    g_assert(obj->type == OBJECTTYPE_RECT);
    g_assert(rect->w == 42);
    g_assert(rect->h == 66);

    obj = M_OBJECT__DESTROY(obj);
    g_assert(obj == NULL);
}