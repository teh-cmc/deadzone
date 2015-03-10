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

#include <c_tab.h>
#include <d_color_ui.h>
#include <tools.h>
#include <c_button.h>
#include <c_tab_manager.h>
#include <c_event.h>
#include <d_mouse.h>

/* constructer destructer */

c_tab::c_tab(c_ncurses* ncurses,
	     c_event* event,
	     c_base_container* parent) : c_base_container(E_TAB,
							  ncurses,
							  event,
							  parent,
							  true,
							  true,
							  true,
							  false),
					 __v_button(NULL)
{
	this->_v_window.f_get_magnetic_border()->f_set(true, true, true, true);
}

c_tab::~c_tab(void)
{

}

/* public function */

bool	c_tab::f_init(const char* title, int x, int y, int width, int height)
{
	if (this->_v_parent->f_get_obj_type() != E_TAB_MANAGER ||
	    this->_f_init_title(title) == false ||
	    this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_methode() == false)
		return false;
	return true;
}

bool	c_tab::f_init_button(const char* title)
{
	int	max_x_button;

	this->__v_button = new (std::nothrow) c_button(this->_v_ncurses, this->_v_event, this->_v_parent, E_TAB_MANAGER_BUTTON, this);
	if (this->__v_button == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_button(%p, %p, %p, %d)\n", this->_v_ncurses, this->_v_event, this->_v_parent, E_TAB_MANAGER_BUTTON);
	max_x_button = ((c_tab_manager*)(this->_v_parent))->f_get_max_x_button();
	if (this->_v_parent->f_add_child(this->__v_button) == false)
	{
		tools::f_delete_ptr(this->__v_button);
		return false;
	}
	if (this->__v_button->f_init(title, max_x_button, 2, tools::f_strlen(title), 1) == false)
		return false;
	return true;
}

bool	c_tab::f_treat_render(void)
{
	if (this->__f_render_tab() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_tab::f_treat_keyboard(int key)
{
	return this->_f_treat_keyboard_method(key);
}

bool	c_tab::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
	{
		if (this->_v_event->f_mouse_button_used(D_LEFT_BUTTON_CLICKED) == true)
			if (this->__f_manager_left_click() == false)
				return false;
	}
	return true;
}

c_button*	c_tab::f_get_button(void)
{
	return this->__v_button;
}

void	c_tab::f_active_tab(void)
{
	((c_tab_manager*)(this->_v_parent))->f_disable_all_tabs();
	this->f_render_active_on();
}

/* private function */

bool	c_tab::__f_manager_left_click(void)
{
	if (this->_v_event->f_add_container_focused(this) == false)
		return false;
	return this->_f_send_mouse_event_to_child();
}

bool	c_tab::__f_render_tab(void)
{
	if (this->__f_draw_tab() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_tab::__f_draw_tab(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TAB)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TAB));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (this->_f_render_title() == false)
		return false;
	return true;
}

bool	c_tab::__f_init_event_methode(void)
{
	return true;
}
