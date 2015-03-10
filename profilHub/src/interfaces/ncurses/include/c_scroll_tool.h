/**
 * Copyright (C) 2013 Jean Hasdenteufel <jeanhasdenteufel@gmail.com>
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

#ifndef __C_SCROLL_TOOL_H__
#define __C_SCROLL_TOOL_H__

#include <e_direction.h>
#include <vector>

class	c_base_container;
class	c_scroll_tool
{
	public:
						c_scroll_tool(c_base_container* obj);
						~c_scroll_tool(void);

		bool				f_scroll(e_direction dir);
		bool				f_enable_scrollbars(void);
		void				f_disable_scrollbars(void);
	private:
		bool				__f_v_scroll(int dy);
		bool				__f_h_scroll(int dx);
		bool				__f_useless_v_scroll(int dy);
		bool				__f_useless_h_scroll(int dx);

		c_base_container*		__v_obj;
		std::vector<c_base_container*>*	__v_child_vect;
		int				__v_speed_scroll;
		bool				__v_scrollbar_active;
};

#endif
