/**
 * entities tree
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

#ifndef ENTITY_H
#define ENTITY_H

/* ----------------------------------- */

#include <SDL.h>
#include <glib.h>

#include <pos.h>

/* ----------------------------------- */

struct __s_entity__family;

typedef struct s_entity__ent {
    POSPos*                       pos;

    struct __s_entity__family*    __family;
} ENTITYEnt;

/* ----------------------------------- */

ENTITYEnt*
ENTITY_build(gint x, gint y, gint z, ENTITYEnt* parent);

ENTITYEnt*
ENTITY_destroy(ENTITYEnt* ent);

#endif
