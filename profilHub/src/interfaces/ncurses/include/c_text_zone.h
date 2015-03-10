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

#ifndef __C_TEXT_ZONE_H__
#define __C_TEXT_ZONE_H__

#include <c_base_container.h>

class	c_text_zone : public c_base_container
{
	public:
			c_text_zone(c_ncurses* ncurses, c_event* event, c_base_container* parent);
			~c_text_zone(void);

		bool	f_init(const char* title, int x, int y, int width, int height);
		bool	f_treat_render(void);
		int	f_treat_keyboard(int key);
		bool	f_treat_mouse(void);
		bool	f_fill_text_by_alloc(const char* str);
		void	f_fill_text_by_reference(char* str);
	private:
		bool	__f_draw_text_zone(void);
		bool	__f_init_event_methode(void);

		bool	__v_allocated;
		char*	__v_text;
};

#endif
