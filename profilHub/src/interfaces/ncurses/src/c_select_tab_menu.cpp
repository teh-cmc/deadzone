/**
 * Copyright (C) 2013 Jean Hasdenteufel <jeanhasdenteufel@gmail.com>
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

#include <c_select_tab_menu.h>
#include <tools.h>

/* destructer destructer */

c_select_tab_menu::c_select_tab_menu(void) : v_name_tab(NULL),
					     v_description_tab(NULL),
					     v_nb_tab(0)
{

}

c_select_tab_menu::~c_select_tab_menu(void)
{
	tools::f_delete_tab_aptr(this->v_name_tab, this->v_nb_tab);
	tools::f_delete_tab_aptr(this->v_description_tab, this->v_nb_tab);
}
