/**
 * This is a calltree element, containing other calltree elements.
 * Copyright (C) 2013  Hugo Nedelec <hugo.nedelec@gmail.com>
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

#include <c_calltree_element.h>

using namespace	pH::ph_tools;

c_calltree_element::c_calltree_element(const char* title): __v_display(true),
							   __v_title(title)
{
	this->__v_childs.clear();
}

c_calltree_element::~c_calltree_element(void)
{
	this->__f_delete_elements();
}

/*
 * C_CALLTREE_ELEMENT PUBLIC METHODS
 */

std::vector<c_calltree_element*>*	c_calltree_element::f_childs(void)
{
	return &this->__v_childs;
}

const char*	c_calltree_element::f_value(void)
{
	return this->__v_title;
}

bool	c_calltree_element::f_display(void)
{
	return this->__v_display;
}

void	c_calltree_element::f_display(bool display)
{
	this->__v_display = display;
}

/*
 * C_CALLTREE_ELEMENT PROTECTED METHODS
 */

/*
 * C_CALLTREE_ELEMENT PRIVATE METHODS
 */

void	c_calltree_element::__f_delete_elements(void)
{
	std::vector<c_calltree_element*>::iterator	it;
	std::vector<c_calltree_element*>::iterator	end;

	it = this->__v_childs.begin();
	end = this->__v_childs.end();
	while (it != end)
	{
		delete *it;
		++it;
	}
	this->__v_childs.clear();
}
