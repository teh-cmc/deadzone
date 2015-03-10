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

#include <c_data_ui.h>
#include <c_ncurses.h>
#include <c_event.h>

/* constructer destructer */

c_data_ui::c_data_ui(c_ncurses* ncurses, c_event* event) : v_main_container(ncurses, event, NULL),
							   v_popup_manager(ncurses, event),
							   v_current_label_focus(NULL)
{

}

c_data_ui::~c_data_ui(void)
{

}
