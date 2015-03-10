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

#ifndef __CALLBACKS_BUTTONS_H__
#define __CALLBACKS_BUTTONS_H__

class	c_ui;
class	c_menu;
class	c_button;
class	c_menu_scroll;
class	c_label_alphanum;
bool	file_toolbar_button_callback(c_ncurses* ncurses, c_button* button);
bool	tools_toolbar_button_callback(c_ncurses* ncurses, c_button* button);
bool	help_toolbar_button_callback(c_ncurses* ncurses, c_button* button);
bool	browse_executable_button_callback(c_ncurses* ncurses, c_button* button);
bool	launch_executable_button_callback(c_ncurses* ncurses, c_button* button);
bool	launch_analyze(char* prog_args, c_menu_scroll* sub_option_menu);
bool	fill_prog_args(char** prog_args, c_label_alphanum* path_executable, c_label_alphanum* arguments_executable);
bool	close_filter_indicator_button_callback(c_ncurses* ncurses, c_button* button);
bool	update_all_filter_position(c_base_container* filter_zone);
bool	prev_function_graphic(c_ncurses* ncurses, c_button* button);
bool	next_function_graphic(c_ncurses* ncurses, c_button* button);
bool	switch_fct(int offset, c_button* button);

#endif
