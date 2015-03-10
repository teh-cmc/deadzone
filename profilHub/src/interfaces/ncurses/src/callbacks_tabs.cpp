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

#include <c_ncurses.h>
#include <c_base_container.h>
#include <tools.h>
#include <c_button.h>
#include <d_children_indexes.h>

/* choice executable tab */

bool	browse_executable_tab_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	c_button*	button;

	(void)ncurses;
	button = (c_button*)(my_obj->f_get_child_by_index(D_BROWSE_EXECUTABLE_BUTTON_INDEX));
	if (button == NULL)
		return M_ERROR_NO_ARGS(false, "Error: button = NULL\n");
	return button->f_use_callback();
}

bool	launch_executable_tab_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	c_button*	button;

	(void)ncurses;
	button = (c_button*)(my_obj->f_get_child_by_index(D_LAUNCH_ANALYSE_BUTTON_INDEX));
	if (button == NULL)
		return M_ERROR_NO_ARGS(false, "Error: button = NULL\n");
	return button->f_use_callback();
}
