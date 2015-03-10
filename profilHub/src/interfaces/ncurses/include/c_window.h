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

#ifndef __C_WINDOW_H__
#define __C_WINDOW_H__

#include <ncurses.h>
#include <c_pos_dim.h>
#include <c_magnetic_border.h>

class	c_base_container;
class	c_window
{
	public:
					c_window(c_base_container* parent,
						 bool width_resizable,
						 bool height_resizable,
						 bool movable);
					~c_window(void);

		bool			f_init(int x, int y, int width, int height);
		void			f_close(void);
		bool			f_render(void);
		bool			f_resize_by_ratio(float rw, float rh);
		WINDOW*			f_get_window(void);
		void			f_set_data_resize(bool width_resizable, bool height_resizable, bool movable);
		bool			f_clean(void);
		c_magnetic_border*	f_get_magnetic_border(void);
		bool			f_get_data_resize(char c);
		bool			f_get_reset_origine_size(void);
		void			f_set_reset_origine_size(bool reset_origine_size);
	private:
		WINDOW*			__v_window;
		c_base_container*	__v_parent;
		c_pos_dim		__v_orig_pos_dim;
		c_magnetic_border	__v_magnetic_border;
		bool			__v_width_resizable;
		bool			__v_height_resizable;
		bool			__v_movable;
};

#endif
