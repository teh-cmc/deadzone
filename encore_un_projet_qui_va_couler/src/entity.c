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

#include <entity.h>
#include <log.h>

/* ----------------------------------- */

typedef struct __s_entity__family {
    ENTITYEnt*    parent;
    GList*        children;
} __ENTITYFamily;

/* ----------------------------------- */

static
__ENTITYFamily*
__build_family(ENTITYEnt* parent) {
    __ENTITYFamily* family = NULL;

    if (!(family = (__ENTITYFamily*)g_malloc0(sizeof(*family)))) {
        M_LOG__ERROR("Could not build __ENTITYFamily", 0);
        return NULL;
    }

    family->parent = parent;

    return family;
}

/* ----------------------------------- */

ENTITYEnt*
ENTITY_build(gint x, gint y, gint z, ENTITYEnt* parent) {
    ENTITYEnt* ent = NULL;

    if (!(ent = (ENTITYEnt*)g_malloc0(sizeof(*ent)))) {
        M_LOG__ERROR("Could not build ENTITYEnt", 0);
        return NULL;
    }
    if (!(ent->pos = POS_build_relative(x, y, z, (parent ? parent->pos : NULL)))) {
        M_LOG__ERROR("Could not build POSPos", 0);
        return ENTITY_destroy(ent);
    }
    if (!(ent->__family = __build_family(parent))) {
        return ENTITY_destroy(ent);
    }

    return ent;
}

ENTITYEnt*
ENTITY_destroy(ENTITYEnt* ent) {
    ent->pos = POS_destroy(ent->pos);

    g_free(ent);

    return NULL;
}