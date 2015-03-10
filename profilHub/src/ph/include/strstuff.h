/**
 * String stuff
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

#ifndef __STRSTUFF__
#define __STRSTUFF__

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

uintmax_t	word_count_dumb(const char* str, const char* delimiters);
/* `*ret` has to be freed later */
/* it's probably smarter to use M_STRSTUFF_STRING_CUT tbh */
bool		string_cut_dumb(const char* str, const char* delimiters, char* ret[]);
/* `array` gotta be NULL terminated */
void		string_array_print(char* const* array);
uintmax_t	string_array_size(char* const* array);

/* `*__ret` has to be freed later */
#define M_STRSTUFF_STRING_CUT(__ret, __str, __delim)\
	char*	__ret[word_count_dumb(__str, __delim) + 1];\
	if (!string_cut_dumb(__str, __delim, __ret))\
		__ret[0] = NULL;\

#ifdef __cplusplus
}
#endif

#endif
