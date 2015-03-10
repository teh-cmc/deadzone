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

#ifndef __C_FUNCTION_CALLTREE_H__
#define __C_FUNCTION_CALLTREE_H__

#include <vector>
#include <c_button.h>
#include <e_close_function.h>
#include <c_info_function.h>

class	c_event;
class	c_ncurses;
class	c_base_container;
class	c_function_calltree
{
	public:
							c_function_calltree(c_ncurses* ncurses,
									    c_event* event,
									    c_base_container* parent,
									    c_function_calltree* function_parent);
							~c_function_calltree(void);

		bool					f_init(const char* name, int x_depth, int y_depth);
		bool					f_add_sub_function(const char* name);
		bool					f_display_branch(void);
		c_function_calltree*			f_get_sub_function_by_index(unsigned int index);
		std::vector<c_function_calltree*>*	f_get_sub_function_vect(void);
		bool					f_open_function(void);
		bool					f_close_function(void);
		bool					f_switch_open_close(void);
		bool					f_display_popup_info(void);
		c_info_function*			f_get_info(void);
		c_function_calltree*			f_get_fct_by_multiple_index(const char* multiple_index);
	private:
		bool					__f_init_buttons(void);
		bool					__f_move_parent_under_children(int y_decal);
		int					__f_get_my_pos(std::vector<c_function_calltree*>* sub_function_vect, int size);
		bool					__f_y_decal(int y_decal);
		int					__f_nb_child(void);
		void					__f_set_children_render_active(bool value, bool grand_parent = false);
		bool					__f_fill_pos_child_vect(std::vector<int>* pos_child_vect);
		bool					__f_draw_hline_branch(int x, int y);
		bool					__f_draw_branch_to_one_child(WINDOW* win, int x);
		bool					__f_draw_branch_to_multiple_child(WINDOW* win, int x, int nb_child);

		bool					__v_open;
		c_info_function				__v_info_function;
		e_close_function			__v_close_type;
		c_button*				__v_open_close_button;
		c_button*				__v_function_button;
		std::vector<c_function_calltree*>	__v_sub_function_vect;
		c_ncurses*				__v_ncurses;
		c_event*				__v_event;
		c_base_container*			__v_parent;
		c_function_calltree*			__v_function_parent;
		c_pos					__v_depth;
};

#endif
