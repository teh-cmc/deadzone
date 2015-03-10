/**
 * pos module unit tests
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

#include <pos.h>
#include <tests_pos.h>

/* ----------------------------------- */

void
TESTS_POS_build_absolute(void) {
    POSPos* pos = POS_build_absolute(1, 2, 3);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 1);
    g_assert(pos->abs.y == 2);
    g_assert(pos->abs.z == 3);
    g_assert(pos->rel.x == 0);
    g_assert(pos->rel.y == 0);
    g_assert(pos->rel.z == 0);

    pos = POS_destroy(pos);
    g_assert(pos == NULL);
}

void
TESTS_POS_build_relative(void) {
    POSPos  parent = { .abs = { .x = 1, .y = 2, .z = 3},
                       .rel = { .x = 4, .y = 5, .z = 6}};

    POSPos* pos = POS_build_relative(1, 2, 3, NULL);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 1);
    g_assert(pos->abs.y == 2);
    g_assert(pos->abs.z == 3);
    g_assert(pos->rel.x == 1);
    g_assert(pos->rel.y == 2);
    g_assert(pos->rel.z == 3);

    pos = POS_destroy(pos);
    g_assert(pos == NULL);

    pos = POS_build_relative(1, 2, 3, &parent);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 2);
    g_assert(pos->abs.y == 4);
    g_assert(pos->abs.z == 6);
    g_assert(pos->rel.x == 1);
    g_assert(pos->rel.y == 2);
    g_assert(pos->rel.z == 3);

    pos = POS_destroy(pos);
    g_assert(pos == NULL);
}

void
TESTS_POS_set_absolute(void) {
    POSPos* pos = POS_build_absolute(1, 2, 3);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 1);
    g_assert(pos->abs.y == 2);
    g_assert(pos->abs.z == 3);
    g_assert(pos->rel.x == 0);
    g_assert(pos->rel.y == 0);
    g_assert(pos->rel.z == 0);

    pos = POS_set_absolute(pos, -1, -1, -1);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == -1);
    g_assert(pos->abs.y == -1);
    g_assert(pos->abs.z == -1);
    g_assert(pos->rel.x == -2);
    g_assert(pos->rel.y == -3);
    g_assert(pos->rel.z == -4);

    pos = POS_destroy(pos);
    g_assert(pos == NULL);
}

void
TESTS_POS_set_relative(void) {
    POSPos* pos = POS_build_absolute(1, 2, 3);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 1);
    g_assert(pos->abs.y == 2);
    g_assert(pos->abs.z == 3);
    g_assert(pos->rel.x == 0);
    g_assert(pos->rel.y == 0);
    g_assert(pos->rel.z == 0);

    pos = POS_set_relative(pos, -1, -2, -3);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 0);
    g_assert(pos->abs.y == 0);
    g_assert(pos->abs.z == 0);
    g_assert(pos->rel.x == -1);
    g_assert(pos->rel.y == -2);
    g_assert(pos->rel.z == -3);

    pos = POS_destroy(pos);
    g_assert(pos == NULL);
}

void
TESTS_POS_move(void) {
    POSPos* pos = POS_build_absolute(1, 2, 3);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == 1);
    g_assert(pos->abs.y == 2);
    g_assert(pos->abs.z == 3);
    g_assert(pos->rel.x == 0);
    g_assert(pos->rel.y == 0);
    g_assert(pos->rel.z == 0);

    pos = POS_move(pos, -10, -10, 5);
    g_assert(pos != NULL);
    g_assert(pos->abs.x == -9);
    g_assert(pos->abs.y == -8);
    g_assert(pos->abs.z ==  8);
    g_assert(pos->rel.x == -10);
    g_assert(pos->rel.y == -10);
    g_assert(pos->rel.z ==  5);

    pos = POS_destroy(pos);
    g_assert(pos == NULL);
}