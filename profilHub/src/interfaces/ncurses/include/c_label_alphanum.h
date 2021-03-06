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

#ifndef __C_LABEL_ALPHANUM_H__
#define __C_LABEL_ALPHANUM_H__

#include <c_label.h>

class	c_label_alphanum : public c_label
{
	public:
			c_label_alphanum(c_ncurses* ncurses, c_event* event, c_base_container* parent);
			~c_label_alphanum(void);

		bool	f_init_label(const char* default_buffer, int size_buffer,
				     int x, int y, int width);
	private:
};

#endif
