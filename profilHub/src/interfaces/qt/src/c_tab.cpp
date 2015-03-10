/**
 * Tabs base class, meant to be inherited from
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

#include <c_tab.h>
#include <c_tab_header.h>
#include <d_design.h>
#include <c_tab_content.h>
#include <QVBoxLayout>
#include <c_tab_label.h>

using namespace	pH;

c_tab::c_tab(QWidget* father): _v_tab_header(NULL),
			       _v_tab_content(NULL),
			       _v_father(father),
			       __v_here(false),
			       __v_activated(true)
{
}

c_tab::~c_tab(void)
{
	delete this->_v_tab_header;
	delete this->_v_tab_content;
}

/*
 * C_TAB PUBLIC METHODS
 */

const char*	c_tab::f_value(void)
{
	return this->_v_value;
}

void	c_tab::show(void)
{
	this->_v_tab_header->show();
	this->_v_tab_content->show();
}

bool*	c_tab::f_activated(void)
{
	return &this->__v_activated;
}

void	c_tab::f_here(bool here)
{
	this->__v_here = here;
}

bool	c_tab::f_here(void)
{
	return this->__v_here;
}

void	c_tab::hide(void)
{
	this->_v_tab_header->hide();
	this->_v_tab_content->hide();
}

c_tab_header*	c_tab::f_tab_header(void)
{
	return this->_v_tab_header;
}

c_tab_content*	c_tab::f_tab_content(void)
{
	return this->_v_tab_content;
}

/*
 * C_TAB PROTECTED METHODS
 */

bool	c_tab::_f_init_header(const char* label_title, const char* image_path, e_tab_header_state state)
{
	this->_v_tab_header = new(std::nothrow) c_tab_header(this->_v_father, label_title, image_path, state);
	if (this->_v_tab_header == NULL)
		return false;
	return this->_v_tab_header->f_init(this);
}

bool	c_tab::_f_init_content(c_tab_content* tab_content)
{
	this->_v_tab_content = tab_content;
	if (this->_v_tab_content == NULL)
		return false;
	return this->_v_tab_content->f_init();
}

/*
 * C_TAB PRIVATE METHODS
 */
