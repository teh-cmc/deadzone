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

#ifndef __C_CONTAINER_H__
#define __C_CONTAINER_H__

#include <c_base_container.h>

class	c_event;
class	c_ncurses;
class	c_container : public c_base_container
{
	public:
			c_container(c_ncurses* ncurses, c_event* event, c_base_container* parent);
			~c_container(void);

		bool	f_init(const char* title, int x, int y, int width, int height);
		bool	f_treat_render(void);
		int	f_treat_keyboard(int key);
		bool	f_treat_mouse(void);
		bool	f_event_escape(void);
		bool	f_event_switch_next_tab(void);
		bool	f_event_switch_prev_tab(void);
	private:
		bool	__f_init_event_method(void);
};

#endif
