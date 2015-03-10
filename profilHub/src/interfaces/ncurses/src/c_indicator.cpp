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

#include <c_indicator.h>
#include <c_ncurses.h>
#include <c_event.h>
#include <d_mouse.h>
#include <tools.h>

/* constructer destructer */

c_indicator::c_indicator(e_indicator_type indicator_type,
			 c_ncurses* ncurses,
			 c_event* event,
			 c_base_container* parent) : c_base_container(E_INDICATOR,
								      ncurses,
								      event,
								      parent,
								      true,
								      false,
								      true,
								      true),
						     __v_indicator_type(indicator_type)
{
	this->_v_window.f_get_magnetic_border()->f_set(false, false, true, true);
}

c_indicator::~c_indicator(void)
{

}

/* public function */

e_indicator_type	c_indicator::f_get_indicator_type(void)
{
	return this->__v_indicator_type;
}

/* protected function */

bool	c_indicator::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_methode() == false)
		return false;
	return true;
}

int	c_indicator::f_treat_keyboard(int key)
{
	return this->_f_treat_keyboard_method(key);
}

/* private function */

bool	c_indicator::__f_init_event_methode(void)
{
	return true;
}
