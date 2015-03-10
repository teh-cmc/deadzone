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

#include <strstuff.h>
#include <stdio.h>
#include <stddef.h>
#include <errors.h>
#include <stdlib.h>

uintmax_t
word_count_dumb(const char* str, const char* delimiters)
{
	uintmax_t	i = 0;
	const char*	tmp = delimiters;

	while (*str)
	{
		tmp = delimiters;
		while (*tmp)
			if (*str == *tmp++)
			{
				++i;
				break;
			}
		++str;
	}
	return i;
}

bool
string_cut_dumb(const char* str, const char* delimiters, char* ret[])
{
	uintmax_t	i = 0;
	char*		__str = strdup(str);

	if (!__str)
		return M_ERROR_BOOL(false, "strdup() failed\n", 0);
	while (__str)
		ret[i++] = strsep(&__str, delimiters);
	ret[i] = NULL;
	return true;
}

void
string_array_print(char* const* array)
{
	printf("string array begin\n");
	while (*array)
		printf("\t'%s'\n", *array++);
	printf("string array end\n");
}

uintmax_t
string_array_size(char* const* array)
{
	uintmax_t	i = 0;

	while (array[i++])
		;
	return i;
}
