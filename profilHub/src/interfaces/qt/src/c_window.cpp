/**
 * Main window for the profilHub Qt interface
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

#include <d_defaults.h>
#include <c_window.h>
#include <c_menubar.h>
#include <c_central_widget.h>

using namespace	pH;

c_window::c_window(void)
{
}

c_window::~c_window(void)
{
	this->__f_cleanup_window();
}

/*
 * C_WINDOW PUBLIC METHODS
 */

bool	c_window::f_init(void)
{
	this->__f_init_window_properties();
	if (this->__f_init_menubar() == false ||
	    this->__f_init_central_widget() == false)
		return false;
	return true;
}

/*
 * C_WINDOW PROTECTED METHODS
 */

/*
 * C_WINDOW PRIVATE METHODS
 */


void	c_window::__f_init_window_properties(void)
{
	this->resize(D_DEFAULT_WINDOW_WIDTH, D_DEFAULT_WINDOW_HEIGHT);
	this->setWindowTitle(D_DEFAULT_WINDOW_TITLE);
}

void	c_window::__f_cleanup_window(void)
{
	delete this->__v_central_widget;
}

bool	c_window::__f_init_menubar(void)
{
	c_menubar*	cmb = new (std::nothrow) c_menubar(this);

	if (cmb == NULL)
		return false;
	if (cmb->f_init() == false)
	{
		delete cmb;
		return false;
	}
	this->setMenuBar(cmb->f_getMenubar());
	return true;
}

bool	c_window::__f_init_central_widget(void)
{
	this->__v_central_widget = new(std::nothrow) c_central_widget(this);
	if (this->__v_central_widget == NULL)
		return false;
	this->__v_central_widget->resize(this->width(), this->height());
	if (this->__v_central_widget->f_init() == false)
		return false;
	this->setCentralWidget(this->__v_central_widget);
	return true;
}
