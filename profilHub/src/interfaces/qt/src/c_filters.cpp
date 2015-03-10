/**
 * This is the area where the filters will be displayed
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

#include <c_filters.h>
#include <errors.h>
#include <QVBoxLayout>
#include <QObject>
#include <c_search_bar.h>
#include <c_filter_lister.h>
#include <c_search_area.h>

using namespace	pH;

c_filters::c_filters(QWidget* father): c_lister(father)
{
}

c_filters::~c_filters(void)
{
}

/*
 * C_FILTERS PUBLIC METHODS
 */

bool	c_filters::f_init(c_warning_lister* warning_lister)
{
	if (this->_f_init() == false ||
	    this->__f_init_filter_lister(warning_lister) == false)
		return false;
	QObject::connect((QObject*)this->_v_search_bar->f_button(), SIGNAL(clicked()), this, SLOT(f_add_filter()));
	QObject::connect((QObject*)this->_v_search_bar->f_text(), SIGNAL(submit()), this, SLOT(f_add_filter()));
	return true;
}

void	c_filters::f_add_filter(void)
{
	this->__v_filter_lister->f_add_filter(this->_v_search_bar->f_text()->text().toLocal8Bit().data());
	this->_v_search_bar->f_text()->clear();
}

/*
 * C_FILTERS PROTECTED METHODS
 */

/*
 * C_FILTERS PRIVATE METHODS
 */

bool	c_filters::__f_init_filter_lister(c_warning_lister* warning_lister)
{
	this->__v_filter_lister = new(std::nothrow) c_filter_lister(this, warning_lister);
	if (this->__v_filter_lister == NULL ||
	    this->__v_filter_lister->f_init() == false)
		return false;
	this->_v_layout->addWidget(this->__v_filter_lister);
	return true;
}
