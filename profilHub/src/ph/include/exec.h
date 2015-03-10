/**
 * Facilitate the execution of a program with the given arguments
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

#ifndef __EXEC__
#define __EXEC__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* `total` is the number of arguments, not including the program itself */
bool	execute(const char** env, const char* program, uintmax_t total, ...);
/* `program_args[0]` must be the program name */
/* `program_args[n - 1]` must point to NULL */
bool	execute_a(const char** env, const char* program_args[]);
/* `programs[n - 1]` must point to NULL */
/* `args[n][0]` and `args[n][i - 1]` must point to NULL */
/* `args[n][i]` is the i-th argument of the n-th program */
bool	execute_m(const char** env, const char* programs[], const char** args[]);
/* same as execute_m(), except programs are piped into each other here */
int	execute_mp(const char** env, const char* programs[], const char** args[]);
/* `path_size` is the size of `path[]`, not the size - 1 */
bool	get_program_path(const char* program, char path[], uintmax_t path_size);
bool	program_available(const char* program);
bool	debug_symbols_available(const char* executable);

#ifdef __cplusplus
}
#endif

#endif
