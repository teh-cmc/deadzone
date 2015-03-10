/**
 * entity module unit tests
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

#include <entity.h>
#include <tests_entity.h>

/* ----------------------------------- */

typedef struct __s_entity__family {
    ENTITYEnt*    parent;
    GList*        children;
} __ENTITYFamily;

/* ----------------------------------- */

void
TESTS_ENTITY_build(void) {
    ENTITYEnt* ent1 = ENTITY_build(5, 10, -10, NULL);
    g_assert(ent1 != NULL);

    g_assert(ent1->__family != NULL);
    g_assert(ent1->__family->parent == NULL);
    g_assert(ent1->__family->children == NULL);

    g_assert(ent1->pos != NULL);
    g_assert(ent1->pos->abs.x ==  5);
    g_assert(ent1->pos->abs.y ==  10);
    g_assert(ent1->pos->abs.z == -10);
    g_assert(ent1->pos->rel.x ==  5);
    g_assert(ent1->pos->rel.y ==  10);
    g_assert(ent1->pos->rel.z == -10);

    ENTITYEnt* ent2 = ENTITY_build(-5, -10, 10, ent1);
    g_assert(ent2 != NULL);

    g_assert(ent2->__family != NULL);
    g_assert(ent2->__family->parent == ent1);
    g_assert(ent2->__family->children == NULL);

    g_assert(ent2->pos != NULL);
    g_assert(ent2->pos->abs.x == 0);
    g_assert(ent2->pos->abs.y == 0);
    g_assert(ent2->pos->abs.z == 0);
    g_assert(ent2->pos->rel.x == -5);
    g_assert(ent2->pos->rel.y == -10);
    g_assert(ent2->pos->rel.z ==  10);

    ent1 = ENTITY_destroy(ent1);
    g_assert(ent1 == NULL);
    ent2 = ENTITY_destroy(ent2);
    g_assert(ent2 == NULL);
}