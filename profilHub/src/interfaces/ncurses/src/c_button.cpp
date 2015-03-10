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

#include <c_button.h>
#include <c_event.h>
#include <d_color_ui.h>
#include <e_obj_type.h>
#include <c_ncurses.h>
#include <tools.h>
#include <c_tab.h>
#include <d_mouse.h>
#include <c_function_calltree.h>

/* constructer destructer */

c_button::c_button(c_ncurses* ncurses,
		   c_event* event,
		   c_base_container* parent,
		   e_button_type button_type,
		   c_base_container* obj_focus) : c_base_container(E_BUTTON,
								   ncurses,
								   event,
								   parent,
								   false,
								   false,
								   false,
								   true),
						  __v_callback(NULL),
						  __v_button_type(button_type),
						  __v_obj_focus(obj_focus)
{
	this->_v_window.f_get_magnetic_border()->f_set(false, false, false, false);
}

c_button::~c_button(void)
{

}

/* public function */

bool	c_button::f_init(const char* title, int x, int y, int width, int height)
{
	if (this->_f_init_title(title) == false ||
	    this->_v_window.f_init(x, y, width, height) == false)
		return false;
	this->__v_pos.f_set(x, y);
	return true;
}

bool	c_button::f_init_title(const char* title)
{
	return this->_f_init_title(title);
}

void	c_button::f_set_button_callback(t_callback callback)
{
	this->__v_callback = callback;
}

bool	c_button::f_treat_render(void)
{
	if (this->__f_render_button() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_button::f_treat_keyboard(int key)
{
	(void)key;
	return 0;
}

bool	c_button::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
	{
		if (this->_v_event->f_mouse_button_used(D_LEFT_BUTTON_CLICKED) == true)
			if (this->__f_manage_left_click() == false)
				return false;
	}
	return true;
}

bool	c_button::f_use_callback(void)
{
	if (this->__v_callback == NULL)
		return M_ERROR_NO_ARGS(false, "Error: callback == NULL\n");
	return this->__v_callback(this->_v_ncurses, this);
}

e_button_type	c_button::f_get_button_type(void)
{
	return this->__v_button_type;
}

c_pos*	c_button::f_get_pos(void)
{
	return &this->__v_pos;
}

int	c_button::f_get_width(void)
{
	return tools::f_strlen(this->_v_title);
}

/* private function */

bool	c_button::__f_manage_left_click(void)
{
	switch	(this->__v_button_type)
	{
		case	E_TAB_MANAGER_BUTTON:
			((c_tab*)(this->__v_obj_focus))->f_active_tab();
			return true;
		case	E_OPEN_CLOSE_FUNCTION_BUTTON:
			return ((c_function_calltree*)(this->__v_obj_focus))->f_switch_open_close();
		case	E_FUNCTION_BUTTON:
			return ((c_function_calltree*)(this->__v_obj_focus))->f_display_popup_info();
		default:
			if (this->__v_callback != NULL)
				return this->f_use_callback();
			return true;
	}
}

bool	c_button::__f_render_button(void)
{
	if (this->__f_draw_button() == ERR ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_button::__f_draw_button(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TOOLBAR)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TOOLBAR));
	if (this->_f_render_title() == false)
		return false;
	return true;
}
