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

#ifndef __C_TAB_H__
#define __C_TAB_H__

#include <c_base_container.h>

class	c_button;
class	c_tab : public c_base_container
{
	public:
				c_tab(c_ncurses* ncurses, c_event* event, c_base_container* parent);
				~c_tab(void);

		bool		f_init(const char* title, int x, int y, int width, int height);
		bool		f_init_button(const char* title);
		bool		f_treat_render(void);
		int		f_treat_keyboard(int key);
		bool		f_treat_mouse(void);
		c_button*	f_get_button(void);
		void		f_active_tab(void);
	private:
		bool		__f_manager_left_click(void);
		bool		__f_render_tab(void);
		bool		__f_draw_tab(void);
		bool		__f_init_event_methode(void);

		c_button*	__v_button;
};

#endif
