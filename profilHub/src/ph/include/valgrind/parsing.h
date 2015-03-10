/**
 * API to handle the use of valgrind and its various tools
 * - parsing stuff -
 * Copyright (C) 2013  Clement Rey <cr.rey.clement@gmail.com>
 *
 * This file is part of profilHub.
 *
 * profilHub is free software: you can redistribute it and/or modify
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

#ifndef __VALGRIND_PARSING__
#define __VALGRIND_PARSING__

#include <stdlib.h>
#include <string.h>
#include <errors.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool	valgrind_parse_memcheck(int fd);

#ifdef __cplusplus
}
#endif

#endif
