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

#ifndef __C_BUTTON_H__
#define __C_BUTTON_H__

#include <c_base_container.h>
#include <c_pos.h>
#include <callbacks_buttons.h>
#include <e_button_type.h>

class	c_button : public c_base_container
{
	public:
		typedef			bool (*t_callback)(c_ncurses* ncurses, c_button* button);
	public:
					c_button(c_ncurses* ncurses,
						 c_event* event,
						 c_base_container* parent,
						 e_button_type button_type,
						 c_base_container* obj_focus = NULL);
					~c_button(void);

		bool			f_init(const char* title, int x, int y, int width, int height);
		bool			f_init_title(const char* title);
		void			f_set_button_callback(t_callback ptr_fct);
		bool			f_treat_render(void);
		int			f_treat_keyboard(int key);
		bool			f_treat_mouse(void);
		bool			f_use_callback(void);
		e_button_type		f_get_button_type(void);
		c_pos*			f_get_pos(void);
		int			f_get_width(void);
	private:
		bool			__f_manage_left_click(void);
		bool			__f_render_button(void);
		bool			__f_draw_button(void);

		c_pos			__v_pos;
		t_callback		__v_callback;
		e_button_type		__v_button_type;
		c_base_container*	__v_obj_focus;
};

#endif
