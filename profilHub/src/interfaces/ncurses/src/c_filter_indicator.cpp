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

#include <c_filter_indicator.h>
#include <callbacks_buttons.h>
#include <d_indicator.h>
#include <d_color_ui.h>
#include <c_ncurses.h>
#include <c_button.h>
#include <d_error.h>
#include <c_event.h>
#include <d_mouse.h>
#include <tools.h>

/* constructer destructer */

c_filter_indicator::c_filter_indicator(c_ncurses* ncurses,
				       c_event* event,
				       c_base_container* parent) : c_indicator(E_FILTER_INDICATOR,
									       ncurses,
									       event,
									       parent),
								   __v_filter(NULL),
								   __v_close_button(NULL)
{
	this->_v_window.f_set_data_resize(true, false, true);
}

c_filter_indicator::~c_filter_indicator(void)
{
	tools::f_delete_aptr(this->__v_filter);
}

/* public function */

bool	c_filter_indicator::f_init_indicator(const char* filter, int x, int y, int width, int height)
{
	if (this->__f_init_filter(filter) == false ||
	    this->__f_init_button(x, y, width) == false ||
	    this->f_init(NULL, x, y, width, height) == false)
		return false;
	return true;
}

bool	c_filter_indicator::f_treat_render(void)
{
	if (this->__f_render_indicator() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

bool	c_filter_indicator::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		return this->_f_send_mouse_event_to_child();
	return true;
}

const char*	c_filter_indicator::f_get_filter(void)
{
	return this->__v_filter;
}

/* private function */

bool	c_filter_indicator::__f_init_filter(const char* filter)
{
	this->__v_filter = tools::f_strdup(filter);
	if (this->__v_filter == NULL)
		return M_ERROR(false, "Error: tools::f_strdup(\"%s\")\n", filter);
	return true;
}

bool	c_filter_indicator::__f_init_button(int x, int y, int width)
{
	int	len = tools::f_strlen(D_FILTER_INDICATOR_CLOSE_BUTTON);

	this->__v_close_button = new (std::nothrow) c_button(this->_v_ncurses, this->_v_event, this, E_CLOSE_FILTER_BUTTON);
	if (this->__v_close_button == NULL)
		return D_ERR_ALLOC;
	if (this->f_add_child(this->__v_close_button) == false)
	{
		tools::f_delete_ptr(this->__v_close_button);
		return false;
	}
	this->__v_close_button->f_set_button_callback(&close_filter_indicator_button_callback);
	return this->__v_close_button->f_init(D_FILTER_INDICATOR_CLOSE_BUTTON, x + width - len - 2, y + 2, len, 1);
}

bool	c_filter_indicator::__f_render_indicator(void)
{
	if (this->__f_draw_indicator() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_filter_indicator::__f_draw_indicator(void)
{
	int	min_w_win = tools::f_strlen(D_FILTER_INDICATOR_CLOSE_BUTTON) + 8;
	int	n = (min_w_win > getmaxx(this->_v_window.f_get_window())) ? 0 : getmaxx(this->_v_window.f_get_window()) - min_w_win + 3;

	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_FILTER_INDICATOR)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_FILTER_INDICATOR));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (tools::f_my_mvwaddnstr(this->_v_window.f_get_window(), min_w_win, 2, 2, this->__v_filter, n) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, \"%s\", %d)\n", this->_v_window.f_get_window(), min_w_win , 2, 2, this->__v_filter, n);
	return true;
}
