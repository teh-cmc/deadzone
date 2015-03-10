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

#ifndef __C_MENU_BUTTON_H__
#define __C_MENU_BUTTON_H__

#include <c_menu.h>
#include <e_menu_type.h>

class	c_button;
class	c_event;
class	c_ncurses;
class	c_menu_button : public c_menu
{
	public:
					c_menu_button(c_ncurses* ncurses,
						      c_event* event,
						      c_base_container* parent,
						      c_button* button,
						      e_menu_type menu_type);
					~c_menu_button(void);

			bool		f_init_menu(const char** items,
						    const char** description,
						    c_menu::t_single_callback* ptr_fun_tab,
						    const char* title = "");
			bool		f_treat_mouse(void);
			bool		f_event_key_left(void);
			bool		f_event_key_right(void);
			bool		f_event_enter(void);
		static	bool		sf_treat_menu_from_button_callback(c_ui* ui, e_menu_type menu_type);
	private:
			bool		__f_treat_mouse_menu(void);
			bool		__f_fill_menu(const char* title, const char** items, const char** description, c_menu::t_single_callback* ptr_fun_tab, c_pos* pos);
			bool		__f_init_menu_options(void);
			bool		__f_create_items(const char** items, const char** description, c_menu::t_single_callback* ptr_fun_tab);
			bool		__f_init_window_menu(const char* title, const char** items, const char** description, c_pos* pos);
			bool		__f_init_event_method(void);

			c_button*	__v_button;
};

#endif
