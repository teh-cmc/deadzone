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

#include <c_window.h>
#include <c_ncurses.h>
#include <tools.h>

/* constructer desctructer */

c_window::c_window(c_base_container* parent,
		   bool width_resizable,
		   bool height_resizable,
		   bool movable) : __v_window(NULL),
				   __v_parent(parent),
				   __v_magnetic_border(),
				   __v_width_resizable(width_resizable),
				   __v_height_resizable(height_resizable),
				   __v_movable(movable)
{

}

c_window::~c_window(void)
{
	this->f_close();
}

/* public function */

void	c_window::f_set_data_resize(bool width_resizable, bool height_resizable, bool movable)
{
	this->__v_width_resizable = width_resizable;
	this->__v_height_resizable = height_resizable;
	this->__v_movable = movable;
}

bool	c_window::f_get_data_resize(char c)
{
	if (c == 'w')
		return this->__v_width_resizable;
	else if (c == 'h')
		return this->__v_height_resizable;
	else if (c == 'm')
		return this->__v_movable;
	return false;
}

bool	c_window::f_init(int x, int y, int width, int height)
{
	this->f_close();
	this->__v_window = newwin(height, width, y, x);
	if (this->__v_window == NULL)
		return M_ERROR(false, "Error: newwin(%d, %d, %d, %d)\n", height, width, y, x);
	this->__v_orig_pos_dim.f_set(x, y, width, height);
	return true;
}

void	c_window::f_close(void)
{
	if (this->__v_window == NULL)
		return ;
	if (delwin(this->__v_window) == ERR)
		M_ERROR_VOID("Error: delwin(%p)\n", this->__v_window);
	this->__v_window = NULL;
}

bool	c_window::f_render(void)
{
	if (wrefresh(this->__v_window) == ERR)
		return M_ERROR(false, "Error: wrefresh(%p)\n", this->__v_window);
	return true;
}

bool	c_window::f_resize_by_ratio(float rw, float rh)
{
	c_pos_dim	tmp;

	tmp.v_dim.v_w = this->__v_width_resizable == true ? (int)(this->__v_orig_pos_dim.v_dim.v_w * rw) : this->__v_orig_pos_dim.v_dim.v_w;
	tmp.v_dim.v_h = this->__v_height_resizable == true ?  (int)(this->__v_orig_pos_dim.v_dim.v_h * rh) : this->__v_orig_pos_dim.v_dim.v_h;
	if (tools::f_my_wresize(this->__v_window, tmp.v_dim.v_h, tmp.v_dim.v_w) == ERR)
		return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", this->__v_window, tmp.v_dim.v_h, tmp.v_dim.v_w);
	if (this->__v_movable == true)
	{
		tmp.v_pos.v_x = (int)(this->__v_orig_pos_dim.v_pos.v_x * rw);
		tmp.v_pos.v_y = (int)(this->__v_orig_pos_dim.v_pos.v_y * rh);
		if (tools::f_my_mvwin(this->__v_window, tmp.v_pos.v_y, tmp.v_pos.v_x) == ERR)
			return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", this->__v_window, tmp.v_pos.v_y, tmp.v_pos.v_x);
	}
	return true;
}

WINDOW*	c_window::f_get_window(void)
{
	return this->__v_window;
}

bool	c_window::f_clean(void)
{
	if (wclear(this->__v_window) == ERR)
		return M_ERROR(false, "Error: wclear(%p)\n", this->__v_window);
	if (wrefresh(this->__v_window) == ERR)
		return M_ERROR(false, "Error: wrefresh(%p)\n", this->__v_window);
	return true;
}

c_magnetic_border*	c_window::f_get_magnetic_border(void)
{
	return &this->__v_magnetic_border;
}
