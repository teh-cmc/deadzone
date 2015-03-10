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

#ifndef __C_DATA_UI_H__
#define __C_DATA_UI_H__

#include <c_container.h>
#include <c_pos_dim.h>
#include <c_popup_manager.h>
#include <c_profiler_menu.h>
#include <c_profiler_infos_menu.h>
#include <c_select_tab_menu.h>

class	c_label;
class	c_data_ui
{
	public:
					c_data_ui(c_ncurses* ncurses, c_event* event);
					~c_data_ui(void);

		c_container		v_main_container;
		c_pos_dim		v_orig_window_pos_dim;
		c_popup_manager		v_popup_manager;
		c_label*		v_current_label_focus;
		c_profiler_menu		v_profiler_menu;
		c_profiler_infos_menu	v_profiler_infos_menu;
		c_select_tab_menu	v_select_tab_menu;
};

#endif
