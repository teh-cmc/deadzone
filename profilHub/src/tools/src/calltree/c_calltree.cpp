/**
 * This class will be used as an interface to manipulate the calltree elements.
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

#include <c_calltree.h>
#include <c_calltree_element.h>
#include <stdio.h>

using namespace	pH::ph_tools;

c_calltree::c_calltree(void): __v_root(NULL)
{
}

c_calltree::~c_calltree(void)
{
	delete this->__v_root;
}

/*
 * C_CALLTREE PUBLIC METHODS
 */

c_calltree_element*	c_calltree::f_root(void)
{
	return this->__v_root;
}

void	c_calltree::f_clear(void)
{
	delete this->__v_root;
	this->__v_root = NULL;
}

bool	c_calltree::f_load(void)
{
	std::vector<c_calltree_element*>*	v;

	// Temporary :
	this->__v_root = new c_calltree_element("program");
	v = this->__v_root->f_childs();
	v->push_back(new c_calltree_element("foo"));
	v->push_back(new c_calltree_element("bar"));
	v = (*this->__v_root->f_childs())[0]->f_childs();
	v->push_back(new c_calltree_element("strlen"));
	v->push_back(new c_calltree_element("strcmp"));
	// Load the content from the ph API
	return true;
}

/*
 * C_CALLTREE PROTECTED METHODS
 */

/*
 * C_CALLTREE PRIVATE METHODS
 */
