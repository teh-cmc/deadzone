/**
 * This is the content of the callgraph tab
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

#include <c_tab_content_callgraph.h>

using namespace	pH;

c_tab_content_callgraph::c_tab_content_callgraph(QWidget* father): c_tab_content(father)
{
}

c_tab_content_callgraph::~c_tab_content_callgraph(void)
{
}

/*
 * C_TAB_CONTENT_CALLGRAPH PUBLIC METHODS
 */

bool	c_tab_content_callgraph::f_init(void)
{
	return true;
}

/*
 * C_TAB_CONTENT_CALLGRAPH PROTECTED METHODS
 */

/*
 * C_TAB_CONTENT_CALLGRAPH PRIVATE METHODS
 */
