/**
 * This is the graph tab
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

#include <c_tab.h>
#include <c_tab_content_graph.h>
#include <c_tab_graph.h>
#include <errors.h>
#include <d_paths.h>

using namespace	pH;

c_tab_graph::c_tab_graph(QWidget* father): c_tab(father)
{
	this->_v_value = "graph";
}

c_tab_graph::~c_tab_graph(void)
{
}

/*
 * C_TAB_GRAPH PUBLIC METHODS
 */

bool	c_tab_graph::f_init(void)
{
	if (this->_f_init_header("Graph", D_QUIT_BUTTON_PATH, QUITABLE) == false ||
	    this->_f_init_content(new(std::nothrow) c_tab_content_graph(this->_v_father)) == false)
		return M_ERROR_BOOL(false, "Couldn't create the Graph tab\n", 0);
	return true;
}

/*
 * C_TAB_GRAPH PROTECTED METHODS
 */

/*
 * C_TAB_GRAPH PRIVATE METHODS
 */
