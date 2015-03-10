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

#ifndef __C_INIT_UI_H__
#define __C_INIT_UI_H__

#include <e_insertion_child.h>
#include <profilers.h>
#include <vector>
#include <e_obj_type.h>
#include <c_init_secondary_item.h>

class	c_tab;
class	c_menu;
class	c_event;
class	c_button;
class	c_ncurses;
class	c_data_ui;
class	c_container;
class	c_menu_scroll;
class	c_menu_button;
class	c_tab_manager;
class	c_label_alphanum;
class	c_base_container;
class	c_init_ui
{
	public:
					c_init_ui(c_ncurses* ncurses, c_event* event, c_data_ui* data_ui);
					~c_init_ui(void);

		bool			f_init_interface(void);
		bool			f_init_secondary_item(void);
		bool			f_update_profilers_infos_menu(c_menu_scroll* profiler_menu);
	private:
		bool			__f_init_toolbar(c_base_container* parent);
		bool			__f_init_midel_container(c_base_container* parent);
		bool			__f_init_state_bar(c_base_container* parent);
		bool			__f_fill_midel_container(c_base_container* midel_container);
		bool			__f_init_tab_manager(c_base_container* parent);
		bool			__f_fill_tab_manager(c_tab_manager* tab_manager);
		bool			__f_fill_first_tab(c_tab* tab);
		bool			__f_init_menu_first_tab(c_tab* tab);
		bool			__f_init_content_menu_first_tab(void);
		bool			__f_init_profiler_menu(void);
		bool			__f_init_select_tab_menu(void);
		bool			__f_alloc_tab(int nb_profiler);
		bool			__f_alloc_tab_infos(int nb_profiler);
		bool			__f_fill_tab_profilers(std::vector<pH::ph_tools::c_profiler*>* l_profiler);
		bool			__f_fill_tab_profiler_options(std::vector<pH::ph_tools::c_profiler_option*>* l_profiler_option);
		bool			__f_init_label_first_tab(c_tab* tab);
		bool			__f_init_button_first_tab(c_tab* tab);
		bool			__f_add_menu_in_tab(c_tab* tab, const char* title,
							    char** names, char** descriptions,
							    int x, int y, int width, int height,
							    bool value_selectable = false, bool multi_selection = false);
		bool			__f_set_somes_menu_options(c_tab* tab);
		bool			__f_init_search_module(c_base_container* parent);
		bool			__f_init_error_zone(c_base_container* parent);
		bool			__f_init_filter_module(c_base_container* parent);
		bool			__f_init_filter_zone(c_base_container* parent);
		bool			__f_init_toolbar_menus(void);
		c_base_container*	__f_get_child_by_type(e_obj_type obj_type, c_base_container* container);
		bool			__f_add_object_in_ui(c_base_container* obj,
							     const char* title,
							     int ax, int ay, int bx, int by,
							     bool event_focused = false,
							     e_insertion_child insertion = E_PUSH_BACK_INSERTION);
		bool			__f_add_label_alphanum_in_ui(c_label_alphanum* label,const char* default_buffer,
								     int size_buffer, int x, int y, int width);
		bool			__f_add_button_in_ui(c_button* button, const char* title, int x, int y, int width, int height);
		bool			__f_add_menu_button_in_ui(c_menu_button* menu);
		bool			__f_init_menu(c_menu* menu);
		bool			__f_init_file_menu_button(c_menu_button* menu);
		bool			__f_init_tools_menu_button(c_menu_button* menu);
		bool			__f_init_help_menu_button(c_menu_button* menu);

		c_event*		__v_event;
		c_ncurses*		__v_ncurses;
		c_data_ui*		__v_data_ui;
		c_init_secondary_item	__v_init_secondary_item;
};

#endif
