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

#include <c_popup_text_zone.h>
#include <e_popup_type.h>
#include <c_ncurses.h>
#include <c_event.h>
#include <c_popup_manager.h>
#include <c_base_container.h>
#include <d_color_ui.h>
#include <tools.h>

/* constructer destructer */

c_popup_text_zone::c_popup_text_zone(c_ncurses* ncurses,
				     c_event* event,
				     c_base_container* parent,
				     c_popup_manager* popup_manager) : c_popup(ncurses,
									       event,
									       parent,
									       popup_manager,
									       E_POPUP_TEXT_ZONE),
								       __v_text_zone(NULL)
{

}

c_popup_text_zone::~c_popup_text_zone(void)
{

}

/* public function */

bool	c_popup_text_zone::f_init_popup(c_text_zone* text_zone, const char* title,
					int x, int y, int width, int height)
{
	this->__v_text_zone = text_zone;
	if (this->f_init(title, x, y, width, height) == false)
		return false;
	return true;
}

bool	c_popup_text_zone::f_treat_render(void)
{
	if (this->__f_render_popup() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_popup_text_zone::f_treat_keyboard(int key)
{
	return this->_f_treat_keyboard_method(key);
}

bool	c_popup_text_zone::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		return this->_f_send_mouse_event_to_child();
	else
		this->_f_close_popup();
	return true;
}

/* private function */

bool	c_popup_text_zone::__f_render_popup(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_POPUP)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_POPUP));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (this->_f_render_title() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}
