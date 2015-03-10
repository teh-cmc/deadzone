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

#include <c_data.h>
#include <c_base_container.h>
#include <c_window.h>

/* constructer destructer */

c_data::c_data(e_data_type data_type,
	       c_ncurses* ncurses,
	       c_event* event,
	       c_base_container* parent) : c_base_container(E_DATA,
							    ncurses,
							    event,
							    parent,
							    true,
							    true,
							    true,
							    true),
					   __v_data_type(data_type)
{
	this->_v_window.f_get_magnetic_border()->f_set(true, true, true, true);
}

c_data::~c_data(void)
{

}

/* public function */

/* protected function */

bool	c_data::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_method() == false)
		return false;
	return true;
}

e_data_type	c_data::f_get_data_type(void)
{
	return this->__v_data_type;
}

/* private function */

bool	c_data::__f_init_event_method(void)
{
	return true;
}
