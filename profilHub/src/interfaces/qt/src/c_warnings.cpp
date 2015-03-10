/**
 * This is the area where the warnings are displayed
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

#include <errors.h>
#include <c_warnings.h>
#include <QVBoxLayout>
#include <c_warning_lister.h>
#include <c_search_bar.h>
#include <c_search_area.h>

using namespace	pH;

c_warnings::c_warnings(QWidget* father): c_lister(father)
{
}

c_warnings::~c_warnings(void)
{
}

/*
 * C_WARNINGS PUBLIC METHODS
 */

bool	c_warnings::f_init(void)
{
	if (this->_f_init() == false ||
	    this->__f_init_warning_lister() == false)
		return false;
	QObject::connect((QObject*)this->_v_search_bar->f_text(), SIGNAL(key_pressed()), this, SLOT(f_search()));
	QObject::connect((QObject*)this->_v_search_bar->f_text(), SIGNAL(key_suppressed()), this, SLOT(f_search()));
	return true;
}

c_warning_lister*	c_warnings::f_warning_lister(void)
{
	return this->__v_warning_lister;
}

void	c_warnings::f_search(void)
{
	c_search_area*	search_area;

	search_area = (c_search_area*)QObject::sender();
	this->__v_warning_lister->f_search(search_area->text().toLocal8Bit().data());
}

/*
 * C_WARNINGS PROTECTED METHODS
 */

/*
 * C_WARNINGS PRIVATE METHODS
 */

bool	c_warnings::__f_init_warning_lister(void)
{
	this->__v_warning_lister = new(std::nothrow) c_warning_lister(this);
	if (this->__v_warning_lister == NULL ||
	    this->__v_warning_lister->f_init() == false)
		return false;
	this->_v_layout->addWidget(this->__v_warning_lister);
	return true;
}
