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

#include <c_container.h>
#include <c_event.h>
#include <d_event.h>
#include <c_ncurses.h>
#include <e_obj_type.h>
#include <tools.h>
#include <c_tab_manager.h>
#include <c_tab.h>
#include <c_button.h>
#include <d_children_indexes.h>

/* constructer destructer */

c_container::c_container(c_ncurses* ncurses, c_event* event, c_base_container* parent) : c_base_container(E_CONTAINER,
													  ncurses,
													  event,
													  parent,
													  true,
													  true,
													  true,
													  true)
{
	this->_v_window.f_get_magnetic_border()->f_set(true, true, true, true);
}

c_container::~c_container(void)
{

}

/* public function */

bool	c_container::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_method() == false)
		return false;
	return true;
}

bool	c_container::f_treat_render(void)
{
	return this->_f_render_child();
}

int	c_container::f_treat_keyboard(int key)
{
	return this->_f_treat_keyboard_method(key);
}

bool	c_container::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		return this->_f_send_mouse_event_to_child();
	return true;
}

bool	c_container::f_event_escape(void)
{
	this->_v_ncurses->f_stop_run();
	return true;
}

bool	c_container::f_event_switch_next_tab(void)
{
	c_tab*		next_tab;
	c_tab*		tab_actif;
	c_tab_manager*	tab_manager = (c_tab_manager*)(this->_v_ncurses->f_get_ui()->f_get_data_ui()->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX)->f_get_child_by_type(E_TAB_MANAGER));

	if (tab_manager == NULL)
		return true;
	tab_actif = tab_manager->f_get_first_tab_actif();
	if (tab_actif == NULL)
		return true;
	next_tab = tab_manager->f_get_tab_after_this(tab_actif);
	if (next_tab == NULL)
		return true;
	tab_actif->f_render_active_off();
	next_tab->f_render_active_on();
	return true;
}

bool	c_container::f_event_switch_prev_tab(void)
{
	c_tab*		next_tab;
	c_tab*		tab_actif;
	c_tab_manager*	tab_manager = (c_tab_manager*)(this->_v_ncurses->f_get_ui()->f_get_data_ui()->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX)->f_get_child_by_type(E_TAB_MANAGER));

	if (tab_manager == NULL)
		return true;
	tab_actif = tab_manager->f_get_first_tab_actif();
	if (tab_actif == NULL)
		return true;
	next_tab = tab_manager->f_get_tab_before_this(tab_actif);
	if (next_tab == NULL)
		return true;
	tab_actif->f_render_active_off();
	next_tab->f_render_active_on();
	return true;
}

/* private function */

bool	c_container::__f_init_event_method(void)
{
	if (this->_f_add_common_callback('q', (t_common_callback)(&c_container::f_event_escape)) == false ||
	    this->_f_add_common_callback('t', (t_common_callback)(&c_container::f_event_switch_next_tab)) == false ||
	    this->_f_add_common_callback('T', (t_common_callback)(&c_container::f_event_switch_prev_tab)) == false)
		return false;
	return true;
}
