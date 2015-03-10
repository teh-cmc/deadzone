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

#ifndef __C_CALLTREE_H__
#define __C_CALLTREE_H__

#include <c_data.h>
#include <c_function_calltree.h>

class	c_event;
class	c_ncurses;
class	c_base_container;
class	c_calltree : public c_data
{
	public:
					c_calltree(c_ncurses* ncurses,
						   c_event* event,
						   c_base_container* parent);
					~c_calltree(void);

		bool			f_init_calltree(void);
		bool			f_treat_render(void);
		int			f_treat_keyboard(int key);
		bool			f_treat_mouse(void);
		c_function_calltree*	f_get_fct_by_multiple_index(const char* multiple_index);
	private:
		bool			__f_init_size_like_parent(void);
		bool			__f_draw_calltree(void);

		c_function_calltree	__v_main_function;
};

#endif
