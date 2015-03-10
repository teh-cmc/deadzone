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

#ifndef __PROFILER_OPTION_TOOL_CLASS_HEADER__
#define __PROFILER_OPTION_TOOL_CLASS_HEADER__

#include <launcher.h>

namespace	pH
{
	namespace	ph_tools
	{
		class	c_profiler_option
		{
			public:
							c_profiler_option(launcher_task_type task, const char* string);
				virtual			~c_profiler_option(void);
				launcher_task_type	f_option(void);
				const char*		f_string(void);
				bool			f_activated(void);
				void			f_activated(bool activated);
			protected:
			private:
				launcher_task_type	__v_option;
				const char*		__v_string;
				bool			__v_activated;
		};
	}
}

#endif
