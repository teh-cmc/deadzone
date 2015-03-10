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

#include <c_popup.h>
#include <c_popup_manager.h>
#include <tools.h>
#include <c_event.h>

/* constructer destructer */

c_popup::c_popup(c_ncurses* ncurses,
		 c_event* event,
		 c_base_container* parent,
		 c_popup_manager* popup_manager,
		 e_popup_type popup_type) : c_base_container(E_POPUP,
							     ncurses,
							     event,
							     parent,
							     false,
							     false,
							     false,
							     true),
					    _v_popup_type(popup_type),
					    __v_popup_manager(popup_manager),
					    __v_close(false)
{
	this->_v_window.f_get_magnetic_border()->f_set(false, false, false, false);
}

c_popup::~c_popup(void)
{

}

/* public function */

bool	c_popup::f_init(const char* title, int x, int y, int width, int height)
{
	if (this->_f_init_title(title) == false ||
	    this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_method() == false)
		return false;
	return true;
}

bool	c_popup::f_event_escape(void)
{
	this->__v_close = true;
	return true;
}

bool	c_popup::f_get_close(void)
{
	return this->__v_close;
}

/* protected function */

int	c_popup::_f_treat_event_popup_child(int key)
{
	int	i, size, ret;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		ret = this->_v_container_child[i]->f_treat_keyboard(key);
		if (ret != 0)
			return ret;
		++i;
	}
	return 0;
}

void	c_popup::_f_close_popup(void)
{
	this->__v_close = true;
}

/* private function */

bool	c_popup::__f_init_event_method(void)
{
	if (this->_f_add_common_callback('q', (t_common_callback)(&c_popup::f_event_escape)) == false)
		return false;
	return true;
}
