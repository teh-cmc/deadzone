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

#ifndef TESTS_POS_H
#define TESTS_POS_H

/* ----------------------------------- */

void
TESTS_POS_build_absolute(void);

void
TESTS_POS_build_relative(void);

void
TESTS_POS_set_absolute(void);

void
TESTS_POS_set_relative(void);

void
TESTS_POS_move(void);

#endif