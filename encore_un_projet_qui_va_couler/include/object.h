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

#ifndef OBJECT_H
#define OBJECT_H

/**
 * This module acts as a base class for all objects OBJECTXXXObj.
 * It emulates virtual functions so the end-user only has to work
 * with objects of type OBJECTObj.
 *
 * To create a new type of OBJECTXXXObj, this new object has to
 * have a member `__obj` of type OBJECTObj in its structure,
 * and must set its type to anything but ABSTRACT then return
 * a pointer to it in its constructor.
 *
 * Have a look at OBJECT_RECT module for a simple example.
**/

/* ----------------------------------- */

#include <SDL.h>
#include <glib.h>

/* ----------------------------------- */

typedef enum e_object__type {
    OBJECTTYPE_ABSTRACT,
    OBJECTTYPE_RECT
} OBJECTTYPE;

typedef struct s_object__vtable {
    gpointer    (*destroy)(gpointer);
} OBJECTVtable;

typedef struct s_object__obj {
    OBJECTTYPE      type;

    OBJECTVtable    __vtable;
} OBJECTObj;

/* ----------------------------------- */

#define M_OBJECT__VCAST(__ptr, __type) \
    ((__type*)((gint8*)__ptr - G_STRUCT_OFFSET(__type, __obj)))

#define M_OBJECT__VCHILD(__obj) \
    (__obj->type == OBJECTTYPE_RECT ? __M_VCAST(__obj, OBJECT_RECTObj) : NULL)

#define M_OBJECT__DESTROY(Obj) (Obj->__vtable.destroy((gpointer)Obj))

/* ----------------------------------- */

/* should never be used except for testing */
OBJECTObj*
OBJECT_build(OBJECTTYPE type);

/* should be call via M_OBJECT__DESTROY */
gpointer
OBJECT_destroy(gpointer gp);

#endif
