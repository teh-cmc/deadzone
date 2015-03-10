/**
 * This class will be used as an interface to manipulate the calltree elements.
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

#ifndef __CALLTREE_TOOL_CLASS_HEADER__
#define __CALLTREE_TOOL_CLASS_HEADER__

namespace	pH
{
	namespace	ph_tools
	{
		class	c_calltree_element;
		class	c_calltree
		{
			public:
							c_calltree(void);
				virtual			~c_calltree(void);
				c_calltree_element*	f_root(void);
				void			f_clear(void);
				bool			f_load(void); /* May change with a given .ph file */
			protected:
			private:
				c_calltree_element*	__v_root;
		};
	}
}

#endif
