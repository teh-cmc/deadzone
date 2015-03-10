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

#include <c_label_numeric.h>
#include <e_label_type.h>

/* constructer destructer */

c_label_numeric::c_label_numeric(c_ncurses* ncurses,
				 c_event* event,
				 c_base_container* parent) : c_label(ncurses,
								     event,
								     parent,
								     E_LABEL_NUMERIC)
{

}

c_label_numeric::~c_label_numeric(void)
{

}

/* public function */

bool	c_label_numeric::f_init_label(const char* default_buffer, int size_buffer,
				      int x, int y, int width)
{
	if (this->_f_init_default_buffer_and_size_buffer(default_buffer, &size_buffer) == false ||
	    this->_f_init_buffer(size_buffer) == false ||
	    this->f_init(NULL, x, y, width, 1) == false)
		return false;
	return true;
}

void	c_label_numeric::f_set_negative_nbr(bool negative_nbr)
{
	this->_v_negative_nbr = negative_nbr;
}
