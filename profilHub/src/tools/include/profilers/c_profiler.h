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

#ifndef __PROFILER_TOOLS_CLASS_HEADER__
#define __PROFILER_TOOLS_CLASS_HEADER__

#include <vector>

namespace	pH
{
	namespace	ph_tools
	{
		class	c_profiler_option;
		class	c_profiler
		{
			public:
									c_profiler(const char* string);
				virtual					~c_profiler(void);
				const char*				f_value(void);
				std::vector<c_profiler_option*>*	f_options(void);
			protected:
				std::vector<c_profiler_option*>		_v_profiler_options;
			private:
				const char*				__v_string;

				void					__f_destroy_options(void);
		};
	}
}

#endif
