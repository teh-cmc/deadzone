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

#ifndef __C_UI_H__
#define __C_UI_H__

#include <c_container.h>
#include <c_event.h>
#include <e_menu_type.h>
#include <c_init_ui.h>
#include <c_data_ui.h>

class	c_tab;
class	c_menu;
class	c_label;
class	c_ncurses;
class	c_tab_manager;
class	c_popup_manager;
class	c_base_container;
class	c_ui
{
	public:
						c_ui(c_ncurses* ncurses);
						~c_ui(void);

			bool			f_init(void);
			bool			f_treat(void);
			bool			f_manage_resize(void);
			void			f_set_ratio_resize(float* rw, float* rh);
			bool			f_close(void);
			c_menu*			f_get_menu_by_type(e_menu_type menu_type);
			void			f_set_render_active_off_for_all_menus(void);
			c_popup_manager*	f_get_popup_manager(void);
			bool			f_treat_mouse(void);
			bool			f_there_is_a_label_focus(void);
			void			f_set_current_label_focus(c_label* label);
			int			f_send_keyboard_in_label(int key);
			bool			f_init_first_container_focused(void);
			c_init_ui*		f_get_init_ui(void);
			c_event*		f_get_event(void);
			bool			f_clear_terminal(void);
			c_data_ui*		f_get_data_ui(void);
	private:
			bool			__f_init_first_container_focused(c_base_container* container, int* index_obj_tab, int reccursion);
			bool			__f_init_color(void);
			bool			__f_set_256_color(void);
			bool			__f_set_8_color(void);
			bool			__f_init_ui_color(void);
			bool			__f_init_main_window(void);
			bool			__f_init_main_container(void);
			bool			__f_init_toolbar_menu(void);
			bool			__f_fill_tab_manager(c_tab_manager* tab_manager);
			bool			__f_fill_first_tab(c_tab* tab);
			bool			__f_init_label_first_tab(c_tab* tab);
			bool			__f_init_button_first_tab(c_tab* tab);
			bool			__f_treat_curr_menu(void);

			c_event			__v_event;
			c_ncurses*		__v_ncurses;
			c_data_ui		__v_data_ui;
			c_init_ui		__v_init_ui;
};

#endif
