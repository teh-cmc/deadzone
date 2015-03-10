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

#ifndef __C_FILTER_INDICATOR_H__
#define __C_FILTER_INDICATOR_H__

#include <c_indicator.h>

class	c_event;
class	c_button;
class	c_ncurses;
class	c_function;
class	c_base_container;
class	c_filter_indicator : public c_indicator
{
	public:
				c_filter_indicator(c_ncurses* ncurses,
						   c_event* event,
						   c_base_container* parent);
				~c_filter_indicator(void);

		bool		f_init_indicator(const char* filter, int x, int y, int width, int height);
		bool		f_treat_render(void);
		bool		f_treat_mouse(void);
		const char*	f_get_filter(void);
	private:
		bool		__f_init_filter(const char* filter);
		bool		__f_init_button(int x, int y, int width);
		bool		__f_render_indicator(void);
		bool		__f_draw_indicator(void);

		char*		__v_filter;
		c_button*	__v_close_button;
};

#endif
