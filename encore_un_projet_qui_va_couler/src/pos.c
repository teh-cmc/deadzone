/**
 * position handling
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

#include <pos.h>
#include <log.h>

/* ----------------------------------- */

void
POS_print(POSPos* pos) {
    printf("ABS (%d, %d, %d)\nREL (%d, %d, %d)\n", pos->abs.x, pos->abs.y, pos->abs.z,
                                                   pos->rel.x, pos->rel.y, pos->rel.z);
}

POSPos*
POS_build_absolute(gint x, gint y, gint z) {
    POSPos* pos = NULL;

    if (!(pos = (POSPos*)g_malloc0(sizeof(*pos)))) {
        M_LOG__ERROR("Could not build POSPos", 0);
        return NULL;
    }

    /* absolute coordinates are (x,y,z) */
    /* relative coordinates are (0,0,0) */
    pos->abs.x = x;
    pos->abs.y = y;
    pos->abs.z = z;

    return pos;
}

POSPos*
POS_build_relative(gint x, gint y, gint z, POSPos* parent) {
    POSPos* pos = NULL;

    if (!(pos = (POSPos*)g_malloc0(sizeof(*pos)))) {
        M_LOG__ERROR("Could not build POSPos", 0);
        return NULL;
    }

    /* absolute coordinates are (x,y,z) added to `parent`'s coordinates or 0 */
    pos->abs.x = x + (parent ? parent->abs.x : 0);
    pos->abs.y = y + (parent ? parent->abs.y : 0);
    pos->abs.z = z + (parent ? parent->abs.z : 0);

    /* relative coordinates are (x,y,z) */
    pos->rel.x = x;
    pos->rel.y = y;
    pos->rel.z = z;

    return pos;
}

POSPos*
POS_set_absolute(POSPos* pos, gint x, gint y, gint z) {
    /* relative coordinates are the current ones added to
       the difference between new and old absolute coordinates */
    pos->rel.x += (x - pos->abs.x);
    pos->rel.y += (y - pos->abs.y);
    pos->rel.z += (z - pos->abs.z);

    /* absolute coordinates are (x,y,z) */
    pos->abs.x = x;
    pos->abs.y = y;
    pos->abs.z = z;

    return pos;
}

POSPos*
POS_set_relative(POSPos* pos, gint x, gint y, gint z) {
    /* absolute coordinates are the current ones added to (x,y,z) */
    pos->abs.x += x;
    pos->abs.y += y;
    pos->abs.z += z;

    /* relative coordinates are (x,y,z) */
    pos->rel.x = x;
    pos->rel.y = y;
    pos->rel.z = z;

    return pos;
}

POSPos*
POS_move(POSPos* pos, gint x, gint y, gint z) {
    pos->abs.x += x;
    pos->abs.y += y;
    pos->abs.z += z;

    pos->rel.x += x;
    pos->rel.y += y;
    pos->rel.z += z;

    return pos;
}

POSPos*
POS_destroy(POSPos* pos) {
    g_free(pos);

    return NULL;
}