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

#include <launcher.h>
#include <errors.h>
#include <valgrind/parameters.h>
#include <valgrind/exec.h>

static inline
bool
__build_task(struct launcher_task* task, void* parameters)
{
	if (!task)
		return M_ERROR_BOOL(false, "no task given\n", 0);
	switch (task->type)
	{
		case E_VALGRIND_MEMCHECK:
			if (parameters)
				task->params.vgd_memcheck =
					*(struct launcher_vgd_memcheck_p*)parameters;
			else
				M_LAUNCHER_DEFAULT_MEMCHECK_P(task->params);
			break;
		default:
			return M_ERROR_BOOL(false, "no such task type\n", 0);
	}
	return true;
}

static inline
bool
__launch_valgrind_memcheck_task(struct launcher_task* task, const char* executable)
{
	M_VALGRIND_MEMCHECK_DEFAULT_PARAMETERS(p, executable);

	if (!p)
		return M_ERROR_BOOL(false, "could not allocate memcheck parameters\n", 0);
	if (!valgrind_change_general_parameter(p, D_VALGRIND_P_TRACK_FDS,
					       task->params.vgd_memcheck.vgd_p.track_fds) ||
	    !valgrind_change_general_parameter(p, D_VALGRIND_P_TIME_STAMP,
					       task->params.vgd_memcheck.vgd_p.timestamps) ||
	    !valgrind_change_tool_parameter(p, D_VALGRIND_P_SHOW_REACHABLE,
					    task->params.vgd_memcheck.still_reachable) ||
	    !valgrind_change_tool_parameter(p, D_VALGRIND_P_WORKAROUND_GCC296_BUGS,
					    task->params.vgd_memcheck.gcc296))
	{
		M_VALGRIND_ANNIHILATE_PARAMETERS(p);
		return M_ERROR_BOOL(false, "could not customize memcheck parameters\n", 0);
	}
	if (!valgrind_valid_parameters(p))
	{
		M_VALGRIND_ANNIHILATE_PARAMETERS(p);
		return M_ERROR_BOOL(false, "invalid memcheck parameters\n", 0);
	}
	/**/
	if (!valgrind_execute(p))
	{
		M_VALGRIND_ANNIHILATE_PARAMETERS(p);
		return M_ERROR_BOOL(false, "could not execute memcheck task\n", 0);
	}
	M_VALGRIND_ANNIHILATE_PARAMETERS(p);
	return true;
}

static inline
bool
__launch_task(struct launcher_task* task, const char* executable)
{
	if (!task)
		return M_ERROR_BOOL(false, "no task given\n", 0);
	switch (task->type)
	{
		case E_VALGRIND_MEMCHECK:
			return __launch_valgrind_memcheck_task(task, executable);
		default:
			return M_ERROR_BOOL(false, "no such task type\n", 0);
	}
	return true;
}

bool
launcher_add_task(struct launcher* launcher, enum launcher_task_type type, void* parameters)
{
	bool			ret = false;
	struct launcher_task	task = { .type = type };

	if (!launcher)
		return M_ERROR_BOOL(false, "no launcher passed\n", 0);
	if (!__build_task(&task, parameters))
		return M_ERROR_BOOL(false, "could not build task\n", 0);
	M_LL_PUSH_BACK(launcher->tasks, task, ret);
	if (!ret)
		return M_ERROR_BOOL(false, "could not allocate task\n", 0);
	return true;
}

bool
launcher_launch(struct launcher* launcher)
{
	struct launcher_task*	current = NULL;

	M_LL_FOR_EACH(launcher->tasks, current)
		if (!__launch_task(current, launcher->executable))
			return false;
	M_LL_EACH_FOR;
	return true;
}
