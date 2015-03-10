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

#include <c_scroll_tool.h>
#include <c_base_container.h>

/* constructer destructer */

c_scroll_tool::c_scroll_tool(c_base_container* obj) : __v_obj(obj),
						      __v_child_vect(obj->f_get_child_vect()),
						      __v_speed_scroll(1),
						      __v_scrollbar_active(false)
{

}

c_scroll_tool::~c_scroll_tool(void)
{

}

/* public function */

bool	c_scroll_tool::f_scroll(e_direction dir)
{
	switch	(dir)
	{
		case	E_TOP:		return this->__f_v_scroll(-this->__v_speed_scroll);
		case	E_BOT:		return this->__f_v_scroll(this->__v_speed_scroll);
		case	E_LEFT:		return this->__f_h_scroll(-this->__v_speed_scroll);
		case	E_RIGHT:	return this->__f_h_scroll(this->__v_speed_scroll);
		default:		return true;
	}
	return true;
}

bool	c_scroll_tool::f_enable_scrollbars(void)
{
	if (this->__v_scrollbar_active == true)
		return true;
	this->__v_scrollbar_active = true;
	return this->__v_obj->f_init_scroll_callbacks();
}

void	c_scroll_tool::f_disable_scrollbars(void)
{
	if (this->__v_scrollbar_active == false)
		return ;
	this->__v_scrollbar_active = false;
	this->__v_obj->f_delete_scroll_callbacks();
}

/* private function */

bool	c_scroll_tool::__f_v_scroll(int dy)
{
	int			i, size;
	c_base_container*	obj;

	if (this->__f_useless_v_scroll(dy) == true)
		return true;
	i = 0;
	size = this->__v_child_vect->size();
	while (i < size)
	{
		obj = (*this->__v_child_vect)[i];
		if (obj->f_move(obj->f_get_info_size('x'), obj->f_get_info_size('y') + dy) == false)
			return false;
		++i;
	}
	return true;
}

bool	c_scroll_tool::__f_h_scroll(int dx)
{
	int			i, size;
	c_base_container*	obj;

	if (this->__f_useless_h_scroll(dx) == true)
		return true;
	i = 0;
	size = this->__v_child_vect->size();
	while (i < size)
	{
		obj = (*this->__v_child_vect)[i];
		if (obj->f_move(obj->f_get_info_size('x') + dx, obj->f_get_info_size('y')) == false)
			return false;
		++i;
	}
	return true;
}

bool	c_scroll_tool::__f_useless_v_scroll(int dy)
{
	(void)dy;
	return false;
}

bool	c_scroll_tool::__f_useless_h_scroll(int dx)
{
	(void)dx;
	return false;
}
