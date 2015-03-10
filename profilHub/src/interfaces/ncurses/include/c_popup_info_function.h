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

#ifndef __C_POPUP_INFO_FUNCTION_H__
#define __C_POPUP_INFO_FUNCTION_H__

#include <c_popup.h>

class	c_function_calltree;
class	c_popup_manager;
class	c_popup_info_function : public c_popup
{
	public:
					c_popup_info_function(c_ncurses* ncurses,
							      c_event* event,
							      c_base_container* parent,
							      c_popup_manager* popup_manager);
					~c_popup_info_function(void);

		bool			f_init_popup(c_function_calltree* function, int x, int y, int width, int height);
		bool			f_treat_render(void);
		int			f_treat_keyboard(int key);
		bool			f_treat_mouse(void);
	private:
		bool			__f_draw_popup(void);

		c_function_calltree*	__v_function;
};

#endif
