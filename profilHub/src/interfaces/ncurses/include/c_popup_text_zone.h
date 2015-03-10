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


#ifndef __C_POPUP_TEXT_ZONE_H__
#define __C_POPUP_TEXT_ZONE_H__

#include <c_popup.h>

class	c_event;
class	c_ncurses;
class	c_text_zone;
class	c_popup_manager;
class	c_popup_text_zone : public c_popup
{
	public:
				c_popup_text_zone(c_ncurses* ncurses,
						  c_event* event,
						  c_base_container* parent,
						  c_popup_manager* popup_manager);
				~c_popup_text_zone(void);

		bool		f_init_popup(c_text_zone* text_zone, const char* title,
					     int x, int y, int width, int height);
		bool		f_treat_render(void);
		int		f_treat_keyboard(int key);
		bool		f_treat_mouse(void);
	private:
		bool		__f_render_popup(void);

		c_text_zone*	__v_text_zone;
};

#endif
