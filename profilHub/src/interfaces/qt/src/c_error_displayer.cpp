/**
 * This is the section displaying the errors, by file/line
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

#include <c_error_displayer.h>
#include <d_design.h>

using namespace	pH;

c_error_displayer::c_error_displayer(QWidget* father): QTextBrowser(father)
{
}

c_error_displayer::~c_error_displayer(void)
{
}

/*
 * C_ERROR_DISPLAYER PUBLIC METHODS
 */

bool	c_error_displayer::f_init(void)
{
	this->append("main.cpp:78 \n"
		     "foo.cpp:13\n"
		     "bar.cpp:53\n");
	this->setOpenExternalLinks(false);
	this->setLineWrapMode(QTextEdit::NoWrap);
	return true;
}

/*
 * C_ERROR_DISPLAYER PROTECTED METHODS
 */

/*
 * C_ERROR_DISPLAYER PRIVATE METHODS
 */
