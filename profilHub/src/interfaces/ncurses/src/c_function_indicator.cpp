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

#include <c_function_indicator.h>
#include <c_function_calltree.h>
#include <d_color_ui.h>
#include <c_ncurses.h>
#include <c_event.h>
#include <d_mouse.h>
#include <tools.h>

/* constructer destructer */

c_function_indicator::c_function_indicator(c_ncurses* ncurses,
					   c_event* event,
					   c_base_container* parent) : c_indicator(E_FUNCTION_INDICATOR,
										   ncurses,
										   event,
										   parent),
								       __v_function(NULL)
{

}

c_function_indicator::~c_function_indicator(void)
{

}

/* public function */

bool	c_function_indicator::f_init_indicator(c_function_calltree* function, int x, int y, int width, int height)
{
	this->__v_function = function;
	if (this->f_init(NULL, x, y, width, height) == false)
		return false;
	return true;
}

bool	c_function_indicator::f_treat_render(void)
{
	if (this->__f_render_indicator() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

bool	c_function_indicator::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		if (this->__v_function->f_display_popup_info() == false)
			return false;
	return true;
}

c_function_calltree*	c_function_indicator::f_get_fct(void)
{
	return this->__v_function;
}

/* private function */

bool	c_function_indicator::__f_render_indicator(void)
{
	if (this->__f_draw_indicator() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_function_indicator::__f_draw_indicator(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_FUNCTION_INDICATOR)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_FUNCTION_INDICATOR));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (tools::f_my_mvwaddnstr(this->_v_window.f_get_window(), 6, 2, 2, this->__v_function->f_get_info()->v_name, this->f_get_info_size('w') - 4) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, \"%s\", %d)\n", this->_v_window.f_get_window(), 6, 2, 2, this->__v_function->f_get_info()->v_name, this->f_get_info_size('w') - 4);
	return true;
}
