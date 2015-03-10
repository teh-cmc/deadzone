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

#ifndef __C_BASE_CONTAINER_H__
#define __C_BASE_CONTAINER_H__

#include <ncurses.h>
#include <c_window.h>
#include <vector>
#include <map>
#include <e_obj_type.h>
#include <e_direction.h>
#include <e_button_type.h>
#include <e_insertion_child.h>
#include <e_focus_type.h>
#include <c_scroll_tool.h>

class	c_data;
class	c_event;
class	c_ncurses;
class	c_base_container
{
	private:
			typedef					int (*t_different_keyboard)(c_base_container* my_obj);
			typedef					bool (*t_different_mouse)(c_base_container* my_obj);
	public:
			typedef					bool (*t_single_callback)(c_ncurses* ncurses, c_base_container* my_obj);

		virtual						~c_base_container(void);

		virtual	bool					f_init(const char* title, int x, int y, int width, int height) = 0;
		virtual	bool					f_treat_render(void) = 0;
		virtual	int					f_treat_keyboard(int key) = 0;
		virtual	bool					f_treat_mouse(void) = 0;
		virtual	bool					f_not_focus_anymore(void);
			bool					f_add_child(c_base_container* child, e_insertion_child insertion = E_PUSH_BACK_INSERTION);
			bool					f_delete_child_by_index(unsigned int index);
			bool					f_delete_child_by_ptr(c_base_container* ptr_child);
			void					f_delete_all_child(void);
			bool					f_add_single_callback(int key, t_single_callback single_callback);
			bool					f_resize_by_ratio(float rw, float rh);
			bool					f_magnetic_borders(void);
			bool					f_have_obj(e_obj_type obj_type);
			c_window*				f_get_window(void);
			c_base_container*			f_get_parent(void);
			c_base_container*			f_get_child_by_index(unsigned int index);
			c_base_container*			f_get_child_by_type(e_obj_type type);
			e_obj_type				f_get_obj_type(void);
			std::vector<c_base_container*>*		f_get_child_vect(void);
			c_ncurses*				f_get_ncurses(void);
			bool					f_get_render_active(void);
			void					f_render_active_off(void);
			void					f_render_active_on(void);
			void					f_set_render_active_all_child(bool value);
			e_focus_type				f_get_focus_type(void);
			void					f_set_focus_type(e_focus_type focus_type);
			int					f_get_info_size(char info);
			void					f_set_different_keyboard(t_different_keyboard func_ptr);
			void					f_set_different_mouse(t_different_mouse func_ptr);
			int					f_child_count(void);
			bool					f_move(int x, int y);
			bool					f_resize(int w, int h);
			bool					f_exterior_collide(bool parent_border);
			bool					f_init_scroll_callbacks(void);
			void					f_delete_scroll_callbacks(void);
			void					f_print_obj_type(void);
			const char*				f_get_title(void);
	protected:
			typedef					bool (c_base_container::*t_common_callback)(void);

								c_base_container(e_obj_type,
										 c_ncurses* ncurses,
										 c_event* event,
										 c_base_container* parent,
										 bool width_resizable,
										 bool height_resizable,
										 bool movable,
										 bool render_active);

			bool					_f_init_title(const char* title);
			bool					_f_render_child(void);
			int					_f_treat_keyboard_method(int key);
			int					_f_treat_singles_callbacks(int key);
			bool					_f_add_common_callback(int key, t_common_callback callback);
			bool					_f_render_title(void);
			bool					_f_call_button(e_button_type button);
			bool					_f_click_on_me(void);
			bool					_f_send_mouse_event_to_child(void);

			e_obj_type				_v_obj_type;
			c_window				_v_window;
			c_ncurses*				_v_ncurses;
			c_event*				_v_event;
			c_base_container*			_v_parent;
			std::vector<c_base_container*>		_v_container_child;
			c_scroll_tool				_v_scroll_tool;
			bool					_v_width_resizable;
			bool					_v_height_resizable;
			char*					_v_title;
	private:
			void					__f_set_cadre(int* x_beg, int* y_beg, int* x_max, int* y_max, bool parent_border);
			bool					__f_ui_obj_resizable(c_base_container* ui_obj);
			bool					__f_check_borders(void);
			bool					__f_check_borders_container(WINDOW* parent);
			bool					__f_replace_my_child(void);
			c_base_container*			__f_the_closer_obj_on_my(e_direction direction, bool superimpose = true);
			bool					__f_scroll_top(void);
			bool					__f_scroll_bot(void);
			bool					__f_scroll_left(void);
			bool					__f_scroll_right(void);
			bool					__f_need_scrollbars(void);

			std::map<int, t_common_callback>	__v_common_callback_map;
			std::map<int, t_single_callback>	__v_single_callback_map;
			t_different_keyboard			__v_different_keyboard;
			t_different_mouse			__v_different_mouse;
			bool					__v_render_active;
			e_focus_type				__v_focus_type;
			c_data*					__v_data;
};

#endif
