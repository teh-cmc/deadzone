/**
 * This is the main widget, used as the main container
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

#include <c_central_widget.h>
#include <QGridLayout>
#include <c_listing_area.h>
#include <c_main_content.h>
#include <d_design.h>
#include <errors.h>

using namespace	pH;

c_central_widget::c_central_widget(QWidget* father): QSplitter(Qt::Horizontal, father),
						     __v_listing_area(NULL),
						     __v_layout(NULL)
{
}

c_central_widget::~c_central_widget(void)
{
	delete this->__v_layout;
	delete this->__v_listing_area;
}

/*
 * C_CENTRAL_WIDGET PUBLIC METHODS
 */

bool	c_central_widget::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_main_content() == false ||
	    this->__f_create_listing_area() == false)
		return false;
	this->setLayout(this->__v_layout);
	return true;
}

/*
 * C_CENTRAL_WIDGET PROTECTED METHODS
 */

/*
 * C_CENTRAL_WIDGET PRIVATE METHODS
 */

bool	c_central_widget::__f_create_listing_area(void)
{
	this->__v_listing_area = new(std::nothrow) c_listing_area(this);
	if (this->__v_listing_area == NULL ||
	    this->__v_listing_area->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->__v_listing_area, 0, 1);
	return true;
}

bool	c_central_widget::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QGridLayout;
	if (this->__v_layout == NULL)
		return M_ERROR_BOOL(false, "Couldn't create the central widget layout\n", 0);
	this->__v_layout->setSpacing(5);
	this->__v_layout->setColumnMinimumWidth(0, this->width() - D_INFO_BAR_WIDTH);
	return true;
}

bool	c_central_widget::__f_init_main_content(void)
{
	this->__v_main_content = new(std::nothrow) c_main_content(this);
	if (this->__v_main_content == NULL ||
	    this->__v_main_content->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->__v_main_content);
	return true;
}
