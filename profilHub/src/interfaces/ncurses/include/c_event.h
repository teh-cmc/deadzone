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

#ifndef __C_EVENT_H__
#define __C_EVENT_H__

#include <vector>
#include <ncurses.h>
#include <e_insertion_child.h>

class	c_ui;
class	c_ncurses;
class	c_base_container;
class	c_event
{
	public:
						c_event(c_ncurses* ncurses, c_ui* ui);
						~c_event(void);

		bool				f_init(void);
		bool				f_treat(void);
		bool				f_add_container_focused(c_base_container* container, e_insertion_child insertion = E_PUSH_BACK_INSERTION);
		int				f_mouse_event_ok(void);
		int				f_mouse_action(void);
		int				f_mouse_x(void);
		int				f_mouse_y(void);
		bool				f_mouse_button_used(int button_state);
	private:
		int				__f_manage_special_key(int key);
		bool				__f_erase_previous_run_time_focused_container(void);
		bool				__f_manage_mouse_event(void);
		bool				__f_manage_label_focus(int key);
		bool				__f_manage_focused_container(int key);

		MEVENT				__v_event;
		c_ui*				__v_ui;
		c_ncurses*			__v_ncurses;
		std::vector<c_base_container*>	__v_container_focused;
};

#endif
