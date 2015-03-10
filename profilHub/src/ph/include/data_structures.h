/**
 * Main data structures
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

#ifndef __DATA_STRUCTURES__
#define __DATA_STRUCTURES__

#include <linked_list.h>

#ifdef __cplusplus
extern "C" {
#endif

struct	ph_func
{
	char*		name;
	char*		path;
	uint32_t	line;
	char*		obj_path;
	D_LL_MAGIC_NODE_DECLARATION;
};

struct	ph_error
{
	void*		error;
	struct ph_func	from;
	D_LL_MAGIC_NODE_DECLARATION;
};

struct	ph_data
{
	struct ph_func	function;
	struct ph_func	parents;
	struct ph_func	children;
	D_LL_MAGIC_NODE_DECLARATION;
};

#ifdef __cplusplus
}
#endif

#endif
