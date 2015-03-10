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

#ifndef __C_DATA_H__
#define __C_DATA_H__

#include <c_base_container.h>
#include <e_obj_type.h>
#include <e_data_type.h>

class	c_event;
class	c_ncurses;
class	c_base_container;
class	c_data : public c_base_container
{
	public:
		virtual			~c_data(void);

		e_data_type		f_get_data_type(void);
	protected:
					c_data(e_data_type data_type,
					       c_ncurses* ncurses,
					       c_event* event,
					       c_base_container* parent);

		bool			f_init(const char* title, int x, int y, int width, int height);
	private:
		bool			__f_init_event_method(void);

		e_data_type		__v_data_type;
};

#endif
