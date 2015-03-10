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

#include <c_toolbar.h>
#include <c_event.h>
#include <d_color_ui.h>
#include <e_obj_type.h>
#include <c_button.h>
#include <tools.h>
#include <e_menu_type.h>
#include <c_ncurses.h>
#include <e_button_type.h>

/* constructer destructer */

c_toolbar::c_toolbar(c_ncurses* ncurses, c_event* event, c_base_container* parent) : c_base_container(E_TOOLBAR,
												      ncurses,
												      event,
												      parent,
												      true,
												      false,
												      true,
												      true),
										     __v_offset_button(0)
{
	this->_v_window.f_get_magnetic_border()->f_set(true, false, true, true);
}

c_toolbar::~c_toolbar(void)
{

}

/* public function */

bool	c_toolbar::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_method() == false)
		return false;
	return true;
}

bool	c_toolbar::f_add_button(const char* name, e_button_type button_type, c_button::t_callback callback)
{
	unsigned int	len;
	c_button*	button = new (std::nothrow) c_button(this->_v_ncurses, this->_v_event, this, button_type);

	len = tools::f_strlen(name);
	if (button == NULL)
		return M_ERROR(false, "Error: operater new (std::nothrow) c_button(%p, %p, %d)\n", this->_v_ncurses, this->_v_event, this, button_type);
	if (this->f_add_child(button) == false)
	{
		tools::f_delete_ptr(button);
		return false;
	}
	if (button->f_init(name, this->__v_offset_button, 0, len, 1) == false)
		return false;
	button->f_set_button_callback(callback);
	this->__v_offset_button += len;
	return true;
}

c_button*	c_toolbar::f_get_button_by_type(e_button_type button_type)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_BUTTON &&
		    ((c_button*)(this->_v_container_child[i]))->f_get_button_type() == button_type)
			return ((c_button*)(this->_v_container_child[i]));
		++i;
	}
	return NULL;
}

bool	c_toolbar::f_treat_render(void)
{
	if (this->__f_render_toolbar() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_toolbar::f_treat_keyboard(int key)
{
	return this->_f_treat_keyboard_method(key);
}

bool	c_toolbar::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		return this->_f_send_mouse_event_to_child();
	return true;
}

bool	c_toolbar::f_event_file(void)
{
	return this->_f_call_button(E_TOOLBAR_FILE_BUTTON);
}

bool	c_toolbar::f_event_tools(void)
{
	return this->_f_call_button(E_TOOLBAR_TOOLS_BUTTON);
}

bool	c_toolbar::f_event_help(void)
{
	return this->_f_call_button(E_TOOLBAR_HELP_BUTTON);
}

/* private function */

bool	c_toolbar::__f_render_toolbar(void)
{
	if (this->__f_draw_toolbar() == ERR ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_toolbar::__f_draw_toolbar(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TOOLBAR)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TOOLBAR));
	return true;
}

bool	c_toolbar::__f_init_event_method(void)
{
	if (this->_f_add_common_callback('F', (t_common_callback)(&c_toolbar::f_event_file)) == false ||
	    this->_f_add_common_callback('T', (t_common_callback)(&c_toolbar::f_event_tools)) == false ||
	    this->_f_add_common_callback('H', (t_common_callback)(&c_toolbar::f_event_help)) == false)
		return false;
	return true;
}
