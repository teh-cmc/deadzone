/**
 * This is the content of the calltree tab
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

#include <c_tab_content_calltree.h>
#include <QTreeWidget>
#include <c_calltree_item.h>
#include <tools.h>
#include <errors.h>
#include <QVBoxLayout>

using namespace	pH;

c_tab_content_calltree::c_tab_content_calltree(QWidget* father): c_tab_content(father),
								 __v_calltree(NULL),
								 __v_program_item(NULL),
								 __v_layout(NULL),
								 __v_tree(NULL)
{
}

c_tab_content_calltree::~c_tab_content_calltree(void)
{
	delete this->__v_calltree;
	delete this->__v_layout;
	delete this->__v_program_item;
	delete this->__v_tree;
}

/*
 * C_TAB_CONTENT_CALLTREE PUBLIC METHODS
 */

bool	c_tab_content_calltree::f_init(void)
{
	if (this->__f_init_calltree() == false ||
	    this->__f_init_tree() == false)
		return false;
	return true;
}

bool	c_tab_content_calltree::f_load(void)
{
	bool	ret;

	// Read the informations from the api, and send it to the calltree
	if (this->__v_calltree->f_load() == false)/* Will change and instead send the ph API informations */
		return M_ERROR_BOOL(false, "Couldn't load the calltree", 0);
	if ((ret = this->__f_load_tree(this->__v_calltree->f_root())) == true)
		this->setLayout(this->__v_layout);
	this->__v_calltree->f_clear();
	return ret;
}

/*
 * C_TAB_CONTENT_CALLTREE PROTECTED METHODS
 */

/*
 * C_TAB_CONTENT_CALLTREE PRIVATE METHODS
 */

bool	c_tab_content_calltree::__f_load_tree(ph_tools::c_calltree_element* element)
{
	if (element != NULL)
	{
		delete this->__v_program_item;
		this->__v_program_item = new(std::nothrow) c_calltree_item(this->__v_tree, element->f_value());
		if (this->__v_program_item == NULL || this->__v_program_item->f_load(element) == false)
			return false;
		this->__v_program_item->setText(0, "program");
	}
	return true;
}

bool	c_tab_content_calltree::__f_init_calltree(void)
{
	this->__v_calltree = new(std::nothrow) ph_tools::c_calltree;
	if (this->__v_calltree == NULL)
		return false;
	return true;
}

bool	c_tab_content_calltree::__f_init_tree(void)
{
	this->__v_layout = new(std::nothrow) QVBoxLayout;
	if (this->__v_layout == NULL)
		return false;
	this->__v_tree = new(std::nothrow) QTreeWidget(this);
	if (this->__v_tree == NULL)
		return false;
	this->__v_tree->setHeaderLabel("Calltree");
	this->__v_layout->addWidget(this->__v_tree);
	return true;
}
