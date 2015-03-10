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

#ifndef __C_MENU_H__
#define __C_MENU_H__

#include <map>
#include <c_base_container.h>
#include <e_menu_type.h>
#include <menu.h>
#include <e_driver_action.h>
#include <list>

class	c_ui;
class	c_pos;
class	c_event;
class	c_ncurses;
class	c_menu : public c_base_container
{
	public:
			virtual					~c_menu(void);

			bool					f_init(const char* title, int x, int y, int width, int height);
			void					f_set_checked_char(char checked_char);
			bool					f_treat_render(void);
			int					f_treat_keyboard(int key);
		virtual	bool					f_treat_mouse(void) = 0;
			bool					f_event_escape(void);
			bool					f_event_key_down(void);
			bool					f_event_key_up(void);
			e_menu_type				f_get_menu_type(void);
			bool					f_use_callback_by_mouse_y(int mouse_y);
			const char*				f_current_item_name(void);
			const char*				f_current_item_description(void);
			const char*				f_item_name_by_mouse_y(int mouse_y);
			const char*				f_item_name_by_index(int index);
			const char*				f_item_description_by_index(int index);
			int					f_current_item_index(void);
			ITEM*					f_current_item(void);
			int					f_item_count(void);
			int					f_get_index_where_clicked(int mouse_y);
			bool					f_get_value_selectable(void);
			bool					f_get_multi_selection(void);
			bool					f_set_value_all_item(bool value);
			bool					f_get_item_value_by_index(int index);
			bool					f_do_driver_action(e_driver_action action);
			int					f_get_first_item_selected_index(void);
			bool					f_get_items_selected_vector_index(std::vector<int>* l_index);
	protected:
								c_menu(c_ncurses* ncurses,
								       c_event* event,
								       c_base_container* parent,
								       e_menu_type menu_type,
								       bool render_active,
								       bool value_selectable = false,
								       bool multi_selection = false);

			bool					_f_render_menu(void);
			bool					_f_draw_menu(void);
			bool					_f_init_event_method(void);
			bool					_f_create_menu(void);
			int					_f_length_of_the_longest_item(const char** items);
			void					_f_clear_menu_data(void);
			bool					_f_init_option_value_menu(void);

			MENU*					_v_menu;
			ITEM**					_v_items;
			WINDOW*					_v_sub_win_menu;
			e_menu_type				_v_menu_type;
			e_driver_action				_v_driver_action;
			int					_v_init;
			int					_v_nb_items;
			bool					_v_update;
			bool					_v_value_selectable;
			bool					_v_multi_selection;
			char					_v_checked_char;
	private:
			void					__f_clear_menu_pointer(void);
			bool					__f_passive_resfresh(void);
			void					__f_save_item_value(bool* item_value_saved);
			bool					__f_affect_item_value_saved(bool* item_value_saved);
			bool					__f_display_selected_items(void);
			bool					__f_display_item_by_index(int index);
};

#endif
