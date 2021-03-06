/**
 * This is the tab_content base class, meant to be inherited from
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

#include <c_tab_content.h>

using namespace	pH;

c_tab_content::c_tab_content(QWidget* father): QTextBrowser(father)
{
}

c_tab_content::~c_tab_content(void)
{
}

/*
 * C_TAB_CONTENT PUBLIC METHODS
 */

/*
 * C_TAB_CONTENT PROTECTED METHODS
 */

/*
 * C_TAB_CONTENT PRIVATE METHODS
 */
