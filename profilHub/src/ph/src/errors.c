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

#include <errors.h>
#include <stdio.h>

static inline
void
__print(const char* file, int line, const char* func, const char* format, va_list args)
{
	fprintf(stderr, "\033[0;37m%s, line \033[0;33m%i: \033[1;37m%s()\n\t\033[1;31m",
		file, line, func);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\033[0;37m\n");
}

inline
void
error_void(const char* file, int line, const char* func, const char* format, ...)
{
	va_list	ap;

	va_start(ap, format);
	__print(file, line, func, format, ap);
	va_end(ap);
}

inline
int
error_int(const char* file, int line, const char* func, int ret, const char* format, ...)
{
	va_list	ap;

	va_start(ap, format);
	__print(file, line, func, format, ap);
	va_end(ap);
	return ret;
}

inline
bool
error_bool(const char* file, int line, const char* func, bool ret, const char* format, ...)
{
	va_list	ap;

	va_start(ap, format);
	__print(file, line, func, format, ap);
	va_end(ap);
	return ret;
}
