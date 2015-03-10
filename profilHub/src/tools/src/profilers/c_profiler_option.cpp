/**
 * Copyright (C) 2013  Hugo Nedelec <hugo.nedelec@gmail.com>
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

#include <c_profiler_option.h>

using namespace	pH::ph_tools;

c_profiler_option::c_profiler_option(launcher_task_type task, const char* string): __v_option(task),
										   __v_string(string),
										   __v_activated(false)
{
}

c_profiler_option::~c_profiler_option(void)
{
}

/*
 * C_PROFILER_OPTION PUBLIC METHODS
 */

launcher_task_type	c_profiler_option::f_option(void)
{
	return this->__v_option;
}

const char*	c_profiler_option::f_string(void)
{
	return this->__v_string;
}

bool	c_profiler_option::f_activated(void)
{
	return this->__v_activated;
}

void	c_profiler_option::f_activated(bool activated)
{
	this->__v_activated = activated;
}

/*
 * C_PROFILER_OPTION PROTECTED METHODS
 */

/*
 * C_PROFILER_OPTION PRIVATE METHODS
 */
