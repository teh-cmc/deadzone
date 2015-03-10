/**
 * This class is a calltree item, that we can interact with.
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

#include <c_calltree_item.h>
#include <stdint.h>
#include <QTreeWidget>
#include <tools.h>
#include <iostream> //
#include <errors.h>

using namespace	pH;

c_calltree_item::c_calltree_item(c_calltree_item* father, const char* value): QTreeWidgetItem(father),
									      __v_value(value)
{
}

c_calltree_item::c_calltree_item(QTreeWidget* father, const char* value): QTreeWidgetItem(father),
									  __v_value(value)
{
}

c_calltree_item::~c_calltree_item(void)
{
	this->__f_kill_childs();
}

bool	c_calltree_item::f_load(ph_tools::c_calltree_element* element)
{
	if (element != NULL)
	{
		uint32_t					counter;
		uint32_t					total;
		std::vector<ph_tools::c_calltree_element*>*	vector;

		vector = element->f_childs();
		counter = 0;
		total = vector->size();
		while (counter < total)
		{
			if (__f_load_element((*vector)[counter]) == false)
				return false;
			++counter;
		}
	}
	return true;
}

/*
 * C_CALLTREE_ITEM PUBLIC METHODS
 */

/*
 * C_CALLTREE_ITEM PROTECTED METHODS
 */

/*
 * C_CALLTREE_ITEM PRIVATE METHODS
 */

bool	c_calltree_item::__f_load_element(ph_tools::c_calltree_element* element)
{
	c_calltree_item*	item;

	item = NULL;
	try
	{
		item = new c_calltree_item(this, element->f_value());
		if (item->f_load(element) == false)
			throw -1;
		item->setText(0, element->f_value());
		this->__v_childs.push_back(item);
	}
	catch (...)
	{
		delete item;
		return M_ERROR_BOOL(false, "Couldn't load the calltree item '%s'", element->f_value());
	}
	return true;
}

void	c_calltree_item::__f_kill_childs(void)
{
	uint32_t	counter;
	uint32_t	total;

	counter = 0;
	total = this->__v_childs.size();
	while (counter < total)
	{
		delete this->__v_childs[counter];
		++counter;
	}
	this->__v_childs.clear();
}
