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

#include <c_function_graphic.h>
#include <c_graphic.h>
#include <tools.h>

/* constructer destructer */

c_function_graphic::c_function_graphic(c_graphic* graphic,
				       char motif,
				       int color_pair) : __v_graphic(graphic),
							 __v_name(NULL),
							 __v_motif(motif),
							 __v_color_pair(color_pair)
{

}

c_function_graphic::~c_function_graphic(void)
{
	this->__v_point_vect.clear();
	tools::f_delete_aptr(this->__v_name);
}

/* public function */

bool	c_function_graphic::f_init(const char* name)
{
	int	len = tools::f_strlen(name);

	tools::f_delete_aptr(this->__v_name);
	this->__v_name = new (std::nothrow) char[len];
	if (this->__v_name == NULL)
		return D_ERR_ALLOC;
	tools::f_strncpy(this->__v_name, name, len);
	this->__v_name[len] = 0;
	return true;
}

bool	c_function_graphic::f_add_point(int x, int y)
{
	t_pair	pair(x, y);

	if (this->__f_find_pair(x) == true)
		return M_ERROR(false, "Error: this point with this x (%d) already exist\n", x);
	if (tools::f_push_in_container(&this->__v_point_vect, pair, E_PUSH_BACK_INSERTION) == false)
		return false;
	return true;
}

const char*	c_function_graphic::f_get_name(void)
{
	return this->__v_name;
}

std::vector<c_function_graphic::t_pair>*	c_function_graphic::f_get_point_vect(void)
{
	return &this->__v_point_vect;
}

char	c_function_graphic::f_get_motif(void)
{
	return this->__v_motif;
}

int	c_function_graphic::f_get_color_pair(void)
{
	return this->__v_color_pair;
}

/* private function */

bool	c_function_graphic::__f_find_pair(int x)
{
	int	i, size;

	i = 0;
	size = this->__v_point_vect.size();
	while (i < size)
	{
		if (this->__v_point_vect[i].v_x == x)
			return true;
		++i;
	}
	return false;
}
