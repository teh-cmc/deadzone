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

#ifndef __PROFILERS_TOOL_CLASS_HEADER__
#define __PROFILERS_TOOL_CLASS_HEADER__

#include <vector>
#include <string>

namespace	pH
{
	namespace	ph_tools
	{
		class	c_profiler;
		class	c_profilers
		{
			public:
				static bool	sf_get_choices(std::vector<c_profiler*>* vector);
				static void	sf_destroy_vector(std::vector<c_profiler*>* vector);
			protected:
			private:
		};
	}
}

#endif
