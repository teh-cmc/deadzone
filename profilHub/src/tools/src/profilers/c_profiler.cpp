/**
 * This class is used to contain profiler options and name
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

#include <c_profiler.h>
#include <c_profiler_option.h>

using namespace	pH::ph_tools;

c_profiler::c_profiler(const char* string): __v_string(string)
{
}

c_profiler::~c_profiler(void)
{
	this->__f_destroy_options();
}

/*
 * C_PROFILER PUBLIC METHODS
 */

const char*	c_profiler::f_value(void)
{
	return this->__v_string;
}

std::vector<c_profiler_option*>*	c_profiler::f_options(void)
{
	return &this->_v_profiler_options;
}

/*
 * C_PROFILER PROTECTED METHODS
 */

/*
 * C_PROFILER PRIVATE METHODS
 */

void	c_profiler::__f_destroy_options(void)
{
	unsigned int	counter;
	unsigned int	total;

	counter = 0;
	total = this->_v_profiler_options.size();
	while (counter < total)
	{
		delete this->_v_profiler_options[counter];
		++counter;
	}
	this->_v_profiler_options.clear();
}
