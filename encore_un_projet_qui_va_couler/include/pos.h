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

#ifndef POS_H
#define POS_H

/* ----------------------------------- */

#include <SDL.h>
#include <glib.h>

/* ----------------------------------- */

typedef struct s_pos__coords {
    gint    x;
    gint    y;
    gint    z;
} POSCoords;

typedef struct s_pos__pos {
    POSCoords   abs;
    POSCoords   rel;
} POSPos;

/* ----------------------------------- */

void
POS_print(POSPos* pos);

POSPos*
POS_build_absolute(gint x, gint y, gint z);

POSPos*
POS_build_relative(gint off_x, gint off_y, gint off_z, POSPos* parent);

POSPos*
POS_set_absolute(POSPos* pos, gint x, gint y, gint z);

POSPos*
POS_set_relative(POSPos* pos, gint x, gint y, gint z);

POSPos*
POS_move(POSPos* pos, gint x, gint y, gint z);

POSPos*
POS_destroy(POSPos* pos);

#endif
