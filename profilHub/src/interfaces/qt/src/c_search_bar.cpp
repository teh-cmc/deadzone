/**
 * This is the search bar, containing the search_area and the search_button
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

#include <QHBoxLayout>
#include <c_search_bar.h>
#include <c_search_area.h>
#include <c_img.h>
#include <d_design.h>
#include <d_paths.h>
#include <errors.h>

using namespace	pH;

c_search_bar::c_search_bar(QWidget* father): QFrame(father)
{
}

c_search_bar::~c_search_bar(void)
{
	delete this->__v_layout;
	delete this->__v_search_area;
	delete this->__v_search_button;
}

/*
 * C_SEARCH_BAR PUBLIC METHODS
 */

bool	c_search_bar::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_search_area() == false ||
	    this->__f_init_search_button() == false)
		return false;
	this->setFrameShape(QFrame::WinPanel);
	this->setFrameShadow(Raised);
	this->setLayout(this->__v_layout);
	return true;
}

c_img*	c_search_bar::f_button(void)
{
	return this->__v_search_button;
}

c_search_area*	c_search_bar::f_text(void)
{
	return this->__v_search_area;
}

/*
 * C_SEARCH_BAR PROTECTED METHODS
 */

/*
 * C_SEARCH_BAR PRIVATE METHODS
 */

bool	c_search_bar::__f_init_search_area(void)
{
	this->__v_search_area = new(std::nothrow) c_search_area(this);
	if (this->__v_search_area == NULL ||
	    this->__v_search_area->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->__v_search_area);
	return true;
}

bool	c_search_bar::__f_init_search_button(void)
{
	this->__v_search_button = new(std::nothrow) c_img(this);
	if (this->__v_search_button == NULL ||
	    this->__v_search_button->f_init(D_SEARCH_BUTTON_PATH) == false)
		return false;
	this->__v_layout->addWidget(this->__v_search_button);
	return true;
}

bool	c_search_bar::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QHBoxLayout;
	if (this->__v_layout == NULL)
		return M_ERROR_BOOL(false, "Couldn't create the search bar layout\n", 0);
	this->__v_layout->setContentsMargins(D_SEARCH_BAR_MARGIN, D_SEARCH_BAR_MARGIN,
					     D_SEARCH_BAR_MARGIN, D_SEARCH_BAR_MARGIN);
	return true;
}
