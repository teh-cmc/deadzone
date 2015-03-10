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

#include <c_state_bar.h>
#include <c_event.h>
#include <d_color_ui.h>
#include <tools.h>
#include <e_obj_type.h>

/* constructer destructer */

c_state_bar::c_state_bar(c_ncurses* ncurses, c_event* event, c_base_container* parent) : c_base_container(E_STATE_BAR,
													  ncurses,
													  event,
													  parent,
													  true,
													  false,
													  true,
													  true)
{
	this->_v_window.f_get_magnetic_border()->f_set(false, true, true, true);
}

c_state_bar::~c_state_bar(void)
{

}

/* public function */

bool	c_state_bar::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false)
		return false;
	return true;
}

bool	c_state_bar::f_treat_render(void)
{
	if (this->__f_render_state_bar() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_state_bar::f_treat_keyboard(int key)
{
	(void)key;
	return 0;
}

bool	c_state_bar::f_treat_mouse(void)
{
	return true;
}

/* private function */

bool	c_state_bar::__f_render_state_bar(void)
{
	if (this->__f_draw_state_bar() == ERR ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_state_bar::__f_draw_state_bar(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_STATE_BAR)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_STATE_BAR));
	return true;
}
