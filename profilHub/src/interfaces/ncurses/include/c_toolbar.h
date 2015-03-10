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

#ifndef __C_TOOLBAR_H__
#define __C_TOOLBAR_H__

#include <c_base_container.h>
#include <c_button.h>
#include <e_button_type.h>

class	c_event;
class	c_ncurses;
class	c_toolbar : public c_base_container
{
	public:
				c_toolbar(c_ncurses* ncurses, c_event* event, c_base_container* parent);
				~c_toolbar(void);

		bool		f_init(const char* title, int x, int y, int width, int height);
		bool		f_add_button(const char* name, e_button_type button_type, c_button::t_callback callback);
		c_button*	f_get_button_by_type(e_button_type button_type);
		bool		f_treat_render(void);
		int		f_treat_keyboard(int key);
		bool		f_treat_mouse(void);
		bool		f_event_file(void);
		bool		f_event_tools(void);
		bool		f_event_help(void);
	private:
		bool		__f_render_toolbar(void);
		bool		__f_draw_toolbar(void);
		bool		__f_init_event_method(void);

		int		__v_offset_button;
};

#endif
