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

#ifndef __CALLBACKS_LABELS_H__
#define __CALLBACKS_LABELS_H__

#include <vector>

class	c_ncurses;
class	c_base_container;
class	c_function_indicator;
bool	filter_label_enter_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	check_bad_content_in_current_children(c_base_container* filter_zone, const char* content);
bool	y_min_graph_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	y_precision_graph_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	y_max_graph_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	x_min_graph_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	x_precision_graph_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	x_max_graph_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	not_focus_anymore_label_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	select_nbr_function_graphic(c_ncurses* ncurses, c_base_container* my_obj);
bool	select_name_function_graphic(c_ncurses* ncurses, c_base_container* my_obj);
bool	search_module_real_time_callback(c_ncurses* ncurses, c_base_container* my_obj);
bool	find_fct_indict_match_str(c_base_container* error_zone, std::vector<c_function_indicator*>* fct_indict_vect, const char* str);
bool	update_error_zone(c_base_container* error_zone, std::vector<c_function_indicator*>* fct_indict_vect);
bool	replace_error_zone_children_by_render_active_on(std::vector<c_base_container*>* child_vect);

#endif
