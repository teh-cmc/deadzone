/**
 * Qt application class used to create the main window
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

#include <c_window.h>
#include <errors.h>
#include <c_application.h>

using namespace	pH;

c_application::c_application(int& nb_args, char** args): QApplication(nb_args, args),
							__v_window(NULL)
{
}

c_application::~c_application(void)
{
	delete this->__v_window;
}

/*
 * C_APPLICATION PUBLIC METHODS
 */

bool	c_application::f_init(void)
{
	if (this->__f_init_window() == false)
		return false;
	return true;
}

/*
 * C_APPLICATION PROTECTED METHODS
 */

/*
 * C_APPLICATION PRIVATE METHODS
 */

bool	c_application::__f_init_window(void)
{
	this->__v_window = new(std::nothrow) c_window;
	if (this->__v_window == NULL ||
	    this->__v_window->f_init() == false)
		return false;
	this->__v_window->show();
	return true;
}
