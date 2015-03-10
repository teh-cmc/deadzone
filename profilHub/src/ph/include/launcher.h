/**
 * Launcher API
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

#ifndef __LAUNCHER__
#define __LAUNCHER__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <linked_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * PARAMETERS DATAS
**/

struct	launcher_vgd_p
{
	bool	track_fds;
	bool	timestamps;
};

struct	launcher_vgd_memcheck_p
{
	struct launcher_vgd_p	vgd_p;
	bool			still_reachable;
	bool			gcc296;
};

union	launcher_task_params
{
	struct launcher_vgd_memcheck_p	vgd_memcheck;
};

#define M_LAUNCHER_DEFAULT_MEMCHECK_P(__params)\
	do {\
		__params.vgd_memcheck.vgd_p.track_fds = true;\
		__params.vgd_memcheck.vgd_p.timestamps = false;\
		__params.vgd_memcheck.still_reachable = true;\
		__params.vgd_memcheck.gcc296 = false;\
	} while (0)

/**
 * TASKS DATAS
**/

enum	launcher_task_type
{
	E_VALGRIND_MEMCHECK
};

struct	launcher_task
{
	enum launcher_task_type		type;
	union launcher_task_params	params;
	D_LL_MAGIC_NODE_DECLARATION;
};

/**
 * LAUNCHER
**/

/* should be way enough to store a path */
#define D_TASK_EXECUTABLE_PATH_LEN	512

struct	launcher
{
	char			executable[D_TASK_EXECUTABLE_PATH_LEN];
	struct launcher_task*	tasks;
};

#ifndef __cplusplus
#define M_LAUNCHER(__launcher_name, __executable)\
	struct launcher	__launcher_name = { .tasks = NULL };\
	do {\
		__launcher_name.executable[0] = 0;\
		if (!__executable) break;\
		strncpy(__launcher_name.executable, __executable, D_TASK_EXECUTABLE_PATH_LEN);\
	} while (0)
#else
#define M_LAUNCHER(__launcher_name, __executable)\
	struct launcher	__launcher_name;\
	do {\
		__launcher_name.tasks = NULL;\
		__launcher_name.executable[0] = 0;\
		if (!__executable) break;\
		strncpy(__launcher_name.executable, __executable, D_TASK_EXECUTABLE_PATH_LEN);\
	} while (0)
#endif

#define M_LAUNCHER_DESTROY(__launcher)\
	M_LL_ERASE(__launcher.tasks);\

bool	launcher_add_task(struct launcher* launcher, enum launcher_task_type, void* parameters);
bool	launcher_launch(struct launcher* launcher);

#ifdef __cplusplus
}
#endif

#endif
