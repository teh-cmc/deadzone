/**
 * This class is the valgrind abstract tool class
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
#include <c_profiler_valgrind.h>
#include <d_profiler.h>

using namespace	pH::ph_tools;

c_profiler_valgrind::c_profiler_valgrind(const char* title): c_profiler(title)
{
	this->_v_profiler_options.push_back(new c_profiler_option(E_VALGRIND_MEMCHECK, D_VALGRIND_MEMCHECK));
}

c_profiler_valgrind::~c_profiler_valgrind(void)
{
}

/*
 * C_PROFILER_VALGRIND PUBLIC METHODS
 */

/*
 * C_PROFILER_VALGRIND PROTECTED METHODS
 */

/*
 * C_PROFILER_VALGRIND PRIVATE METHODS
 */
