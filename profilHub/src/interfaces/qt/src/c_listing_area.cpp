/**
 * This is the right part of profilHub, where the listing are displayed
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

#include <c_listing_area.h>
#include <c_filters.h>
#include <c_warnings.h>
#include <QVBoxLayout>
#include <errors.h>

using namespace	pH;

c_listing_area::c_listing_area(QWidget* father): QSplitter(Qt::Vertical, father),
						 __v_layout(NULL),
						 __v_warnings(NULL),
						 __v_filters(NULL)
{
}

c_listing_area::~c_listing_area(void)
{
	delete this->__v_layout;
	delete this->__v_filters;
	delete this->__v_warnings;
}

/*
 * C_LISTING_AREA PUBLIC METHODS
 */

bool	c_listing_area::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_warnings() == false ||
	    this->__f_init_filters() == false)
		return false;
	this->setLayout(this->__v_layout);
	return true;
}

/*
 * C_LISTING_AREA PROTECTED METHODS
 */

/*
 * C_LISTING_AREA PRIVATE METHODS
 */

bool	c_listing_area::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QVBoxLayout;
	return this->__v_layout;
}

bool	c_listing_area::__f_init_warnings(void)
{
	this->__v_warnings = new(std::nothrow) c_warnings(this);
	if (this->__v_warnings == NULL ||
	    this->__v_warnings->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->__v_warnings);
	return true;
}

bool	c_listing_area::__f_init_filters(void)
{
	this->__v_filters = new(std::nothrow) c_filters(this);
	if (this->__v_filters == NULL ||
	    this->__v_filters->f_init(this->__v_warnings->f_warning_lister()) == false)
		return false;
	this->__v_layout->addWidget(this->__v_filters);
	return true;
}
