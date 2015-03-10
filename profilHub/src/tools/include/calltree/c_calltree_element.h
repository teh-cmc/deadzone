/**
 * This is a calltree element, containing other calltree elements.
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

#ifndef __CALLTREE_ELEMENT_TOOL_CLASS_HEADER__
#define __CALLTREE_ELEMENT_TOOL_CLASS_HEADER__

#include <vector>

namespace	pH
{
	namespace	ph_tools
	{
		class	c_calltree_element
		{
			public:
									c_calltree_element(const char* title); /* May change with an identifier.. */
				virtual					~c_calltree_element(void);
				bool					f_display(void);
				void					f_display(bool display);
				const char*				f_value(void);
				std::vector<c_calltree_element*>*	f_childs(void);
			protected:
			private:
				bool					__v_display;
				const char*				__v_title;
				std::vector<c_calltree_element*>	__v_childs; /* May change with our own vector class */

				void					__f_delete_elements(void);
		};
	}
}

#endif
