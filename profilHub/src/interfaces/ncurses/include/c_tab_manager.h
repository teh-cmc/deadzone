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

#ifndef __C_TAB_MANAGER_H__
#define __C_TAB_MANAGER_H__

#include <c_base_container.h>

class	c_tab;
class	c_tab_manager : public c_base_container
{
	public:
					c_tab_manager(c_ncurses* ncurses, c_event* event, c_base_container* parent);
					~c_tab_manager(void);

		bool			f_init(const char* title, int x, int y, int width, int height);
		bool			f_treat_render(void);
		int			f_treat_keyboard(int key);
		bool			f_treat_mouse(void);
		bool			f_add_tab(const char* tab_title, const char* button_title);
		int			f_get_max_x_button(void);
		void			f_disable_all_tabs(void);
		void			f_set_tab_active_by_index(int index);
		c_tab*			f_get_tab_by_index(unsigned int index);
		c_tab*			f_get_tab_after_this(c_tab* tab);
		c_tab*			f_get_tab_before_this(c_tab* tab);
		c_tab*			f_get_first_tab_actif(void);
	private:
		bool			__f_render_tab_manager(void);
		bool			__f_draw_tab_manager(void);
		bool			__f_init_event_methode(void);
		int			__f_nb_tab(void);
		c_tab*			__f_get_tab_by_index(int index = 0);
		c_tab*			__f_first_tab(void);
		c_tab*			__f_last_tab(void);
};

#endif
