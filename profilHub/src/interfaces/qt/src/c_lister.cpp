/**
 * This is the c_lister based class, meant to be inherited from
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

#include <QVBoxLayout>
#include <c_search_bar.h>
#include <c_lister.h>

using namespace	pH;

c_lister::c_lister(QWidget* father): QFrame(father)
{
}

c_lister::~c_lister(void)
{
	delete this->_v_layout;
	delete this->_v_search_bar;
}

/*
 * C_LISTER PUBLIC METHODS
 */

/*
 * C_LISTER PROTECTED METHODS
 */

bool	c_lister::_f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_search_bar() == false)
		return false;
	this->setFrameShape(QFrame::WinPanel);
	this->setLayout(this->_v_layout);
	return true;
}

/*
 * C_LISTER PRIVATE METHODS
 */

bool	c_lister::__f_init_layout(void)
{
	this->_v_layout = new(std::nothrow) QVBoxLayout;
	return this->_v_layout;
}

bool	c_lister::__f_init_search_bar(void)
{
	this->_v_search_bar = new(std::nothrow) c_search_bar(this);
	if (this->_v_search_bar == NULL ||
	    this->_v_search_bar->f_init() == false)
		return false;
	this->_v_layout->addWidget(this->_v_search_bar);
	return true;
}
