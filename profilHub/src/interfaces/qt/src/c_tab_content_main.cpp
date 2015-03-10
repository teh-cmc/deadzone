/**
 * This is the content of the main_tab
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

#include <c_tab_content_main.h>

using namespace	pH;

c_tab_content_main::c_tab_content_main(QWidget* father): c_tab_content(father)
{
}

c_tab_content_main::~c_tab_content_main(void)
{
}

/*
 * C_TAB_CONTENT_MAIN PUBLIC METHODS
 */

bool	c_tab_content_main::f_init(void)
{
	this->append("Welcome to profilHub\n"
		     "This is free software: you can redistribute it and/or modify it\n"
		     "under the terms of the GNU General Public License as published by\n"
		     "the Free Software Foundation, either verison 3 of the License.\n\n"
		     "You can find more informations about this project on our github home page at:\n"
		     "https://github.com/reyclement/profilHub");
	this->setLineWrapMode(QTextEdit::NoWrap);
	return true;
}

/*
 * C_TAB_CONTENT_MAIN PROTECTED METHODS
 */

/*
 * C_TAB_CONTENT_MAIN PRIVATE METHODS
 */
