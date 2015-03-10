/**
 * Useful functions and macros to handle errors
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

#ifndef __ERRORS__
#define __ERRORS__

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void	error_void(const char* file, int line, const char* func,
		   const char* format, ...);
int	error_int(const char* file, int line, const char* func,
		  int ret, const char* format, ...);
bool	error_bool(const char* file, int line, const char* func,
		   bool ret, const char* format, ...);

#ifdef __cplusplus
}
#endif

#define M_ERROR(__error, __args...)\
	(error_void(__FILE__, __LINE__, __func__, __error, __args))

#define M_ERROR_INT(__ret, __error, __args...)\
	(error_int(__FILE__, __LINE__, __func__, __ret, __error, __args))

#define M_ERROR_BOOL(__ret, __error, __args...)\
	(error_bool(__FILE__, __LINE__, __func__, __ret, __error, __args))

#define M_PSTR(__str)\
	(printf("str: '%s'\n", __str ? __str : "NULL"))

#define M_PPTR(__ptr)\
	(printf("ptr: '%p'\n", __ptr))

#define M_PINT(__int)\
	(printf("int: '%i'\n", __int))

#endif
