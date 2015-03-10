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

#include <c_popup_info_function.h>
#include <e_popup_type.h>
#include <tools.h>
#include <c_popup_manager.h>
#include <d_popup.h>
#include <c_event.h>
#include <d_color_ui.h>
#include <c_function_calltree.h>
#include <d_info_function.h>

/* constructer destructer */

c_popup_info_function::c_popup_info_function(c_ncurses* ncurses,
					     c_event* event,
					     c_base_container* parent,
					     c_popup_manager* popup_manager) : c_popup(ncurses,
										       event,
										       parent,
										       popup_manager,
										       E_POPUP_ERR_MSG),
									       __v_function(NULL)
{

}

c_popup_info_function::~c_popup_info_function(void)
{

}

/* public function */

bool	c_popup_info_function::f_init_popup(c_function_calltree* function, int x, int y, int width, int height)
{
	this->__v_function = function;
	if (this->f_init("Popup: info function", x, y, width, height) == false)
		return false;
	return true;
}

bool	c_popup_info_function::f_treat_render(void)
{
	if (this->__f_draw_popup() == false)
		return false;
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_POPUP)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_POPUP));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (this->_f_render_title() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

int	c_popup_info_function::f_treat_keyboard(int key)
{
	int	ret;

	ret = this->_f_treat_keyboard_method(key);
	if (ret != 0)
		return ret;
	return this->_f_treat_event_popup_child(key);
}

bool	c_popup_info_function::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == false)
		this->_f_close_popup();
	return true;
}

/* private function */

bool	c_popup_info_function::__f_draw_popup(void)
{
	WINDOW*			win = this->_v_window.f_get_window();
	c_info_function*	info = this->__v_function->f_get_info();
	const char		fct_name[] = "Function name: ";

	if (tools::f_my_mvwaddnstr(win, -1, D_Y_BEGIN_INFO, D_X_BEGIN_INFO, fct_name, -1) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, \"%s\", %d)\n", win, -1, D_Y_BEGIN_INFO, D_X_BEGIN_INFO, "Function name: ", -1);
	if (tools::f_my_mvwaddnstr(win, -1, D_Y_BEGIN_INFO, D_X_BEGIN_INFO + tools::f_strlen(fct_name), info->v_name, -1) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, \"%s\", %d)\n", win, -1, D_X_BEGIN_INFO, D_Y_BEGIN_INFO + tools::f_strlen(fct_name), info->v_name, -1);
	return true;
}
