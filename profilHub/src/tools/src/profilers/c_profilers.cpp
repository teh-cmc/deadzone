/**
 * This class is used to share the different usable profilers for every interfaces
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

#include <stdint.h>
#include <c_profilers.h>
#include <c_profiler_valgrind.h>
#include <c_profiler_gprof.h>

using namespace	pH::ph_tools;

bool	c_profilers::sf_get_choices(std::vector<c_profiler*>* vector)
{
	try
	{
		vector->push_back(new c_profiler_valgrind("valgrind"));
		//vector->push_back(new c_profiler_gprof("gprof"));
	}
	catch (...)
	{
		c_profilers::sf_destroy_vector(vector);
		return false;
	}
	return true;
}

void	c_profilers::sf_destroy_vector(std::vector<c_profiler*>* vector)
{
	uint32_t	counter;
	uint32_t	total;

	counter = 0;
	total = vector->size();
	while (counter < total)
	{
		delete (*vector)[counter];
		++counter;
	}
}
