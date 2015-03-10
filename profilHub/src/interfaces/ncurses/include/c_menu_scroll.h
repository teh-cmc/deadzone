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

#ifndef __C_MENU_SCROLL_H__
#define __C_MENU_SCROLL_H__

#include <c_menu.h>
#include <e_menu_type.h>
#include <c_pos_dim.h>

class	c_event;
class	c_ncurses;
class	c_menu_scroll : public c_menu
{
	public:
				c_menu_scroll(c_ncurses* ncurses, c_event* event, c_base_container* parent,
					      bool value_selectable = false, bool multi_selection = false);
				~c_menu_scroll(void);

		bool		f_init_menu(char** items, char** description,
					    int x, int y, int width, int height,
					    const char* title = "");
		bool		f_treat_mouse(void);
		bool		f_event_enter(void);
		bool		f_event_next_page(void);
		bool		f_event_prev_page(void);
		bool		f_update_data_menu(char** items, char** description);
	private:
		bool		__f_init_menu_options(void);
		bool		__f_fill_menu(char** items, char** description, const char* title,
					      int x, int  y, int width, int height);
		bool		__f_init_event_method(void);
		bool		__f_create_items(char** items, char** description);
		bool		__f_init_window_menu(const char* title, int x, int y, int width, int height);

		c_pos_dim	__v_save_menu_size;
};

#endif
