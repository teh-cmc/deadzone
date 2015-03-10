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

#include <c_menu_scroll.h>
#include <d_menu.h>
#include <tools.h>
#include <stdlib.h>
#include <d_color_ui.h>
#include <d_event.h>
#include <d_file_description.h>
#include <errno.h>
#include <c_event.h>

/* constructer */

c_menu_scroll::c_menu_scroll(c_ncurses* ncurses,
			     c_event* event,
			     c_base_container* parent,
			     bool value_selectable,
			     bool multi_selection) : c_menu(ncurses,
							    event,
							    parent,
							    E_MENU_SCROLL,
							    true,
							    value_selectable,
							    multi_selection)
{

}

c_menu_scroll::~c_menu_scroll(void)
{

}

/* public function */

bool	c_menu_scroll::f_init_menu(char** items, char** description,
				   int x, int y, int width, int height,
				   const char* title)
{
	if (this->_v_init != D_MENU_NO_INIT && this->_v_init != D_MENU_UPDATE)
		return M_ERROR(false, "Error: menu scroll is already init or bad value for update, this->_v_init = %d\n", this->_v_init);
	this->_v_init = D_MENU_DURING_INIT;
	if (this->__f_fill_menu(items, description, title, x, y, width, height) == false ||
	    this->__f_init_menu_options() == false ||
	    (this->_v_update == false && this->__f_init_event_method() == false))
		return false;
	this->_v_init = D_MENU_INITED;
	this->__v_save_menu_size.f_set(x, y, width, height);
	return true;
}

bool	c_menu_scroll::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		if (this->_v_event->f_add_container_focused(this) == false)
			return false;
	return true;
}

bool	c_menu_scroll::f_event_next_page(void)
{
	this->_v_driver_action = E_NEXT_PAGE_DRIVER;
	return true;
}

bool	c_menu_scroll::f_event_prev_page(void)
{
	this->_v_driver_action = E_PREV_PAGE_DRIVER;
	return true;
}

bool	c_menu_scroll::f_event_enter(void)
{
	ITEM*	curr_item;

	if (this->_v_value_selectable == true)
	{
		if (this->_v_multi_selection == false && this->f_set_value_all_item(false) == false)
				return false;
		curr_item = this->f_current_item();
		if (curr_item == NULL)
			return M_ERROR_NO_ARGS(false, "Error: current item = NULL\n");
		if (menu_driver(this->_v_menu, E_SET_VALUE_DRIVER) != E_OK)
			return M_ERROR(false, "Error: menu_driver(%p, %d)\n", this->_v_menu, E_SET_VALUE_DRIVER);
	}
	return true;
}

bool	c_menu_scroll::f_update_data_menu(char** items, char** description)
{
	this->_v_update = true;
	this->_f_clear_menu_data();
	this->_v_init = D_MENU_UPDATE;
	if (this->f_init_menu(items, description,
			      this->__v_save_menu_size.v_pos.v_x,
			      this->__v_save_menu_size.v_pos.v_y,
			      this->__v_save_menu_size.v_dim.v_w,
			      this->__v_save_menu_size.v_dim.v_h) == false)
		return false;
	return true;
}

/* private function */

bool	c_menu_scroll::__f_fill_menu(char** items, char** description, const char* title,
				     int x, int y, int width, int height)
{
	this->_v_nb_items = tools::f_nb_element(items);
	if (this->_v_nb_items != tools::f_nb_element(description))
		return M_ERROR(false, "Error: nb item = %d != nb description = %d\n", this->_v_nb_items, tools::f_nb_element(description));
	if (this->__f_create_items(items, description) == false ||
	    this->_f_create_menu() == false ||
	    this->__f_init_window_menu(title, x, y, width, height) == false)
		return false;
	return true;
}

bool	c_menu_scroll::__f_init_menu_options(void)
{
	if (set_menu_fore(this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU_SELECTION)) != E_OK)
		return M_ERROR(false, "Error: set_menu_fore(%p, %d)\n", this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU_SELECTION));
	if (set_menu_back(this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU)) != E_OK)
		return M_ERROR(false, "Error: set_menu_back(%p, %d)\n", this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU));
	return true;
}

bool	c_menu_scroll::__f_init_event_method(void)
{
	if (this->_f_add_common_callback(KEY_NPAGE, (t_common_callback)(&c_menu_scroll::f_event_next_page)) == false ||
	    this->_f_add_common_callback(KEY_PPAGE, (t_common_callback)(&c_menu_scroll::f_event_prev_page)) == false ||
	    this->_f_add_common_callback(D_ENTER, (t_common_callback)(&c_menu_scroll::f_event_enter)) == false)
		return false;
	return true;
}

bool	c_menu_scroll::__f_create_items(char** items, char** description)
{
	int	i;

	this->_v_items = (ITEM**)calloc(this->_v_nb_items + 1, sizeof(ITEM*));
	if (this->_v_items == NULL)
		return M_ERROR(false, "Error: calloc(%d, %d)\n", this->_v_nb_items + 1, sizeof(ITEM*));
	i = 0;
	while (i < this->_v_nb_items)
	{
		this->_v_items[i] = new_item(items[i], description[i]);
		if (this->_v_items[i] == NULL)
			return M_ERROR(false, "Error: new_item(\"%s\", \"%s\")\n", items[i], description[i]);
		++i;
	}
	return true;
}

bool	c_menu_scroll::__f_init_window_menu(const char* title, int x, int y, int width, int height)
{
	if (this->f_init(title, x, y, width, height) == false)
		return false;
	if (set_menu_win(this->_v_menu, this->_v_window.f_get_window()) != E_OK)
		return M_ERROR(false, "Error: set_menu_win(%p, %p)\n", this->_v_menu, this->_v_window.f_get_window());
	if (this->_v_sub_win_menu != NULL)
	{
		if (delwin(this->_v_sub_win_menu) == ERR)
			M_ERROR_VOID("Error: delwin(%p)\n", this->_v_sub_win_menu);
		this->_v_sub_win_menu = NULL;
	}
	this->_v_sub_win_menu = derwin(this->_v_window.f_get_window(), height - 2, width - 2, 1, 1);
	if (this->_v_sub_win_menu == NULL)
		return M_ERROR(false, "Error: derwin(%p, %d, %d, %d, %d)\n", this->_v_window.f_get_window(), height - 2, width - 2, 1, 1);
	if (set_menu_sub(this->_v_menu, this->_v_sub_win_menu) != E_OK)
		return M_ERROR(false, "Error: set_menu_sub(%p, %p)\n", this->_v_menu, this->_v_sub_win_menu);
	if (set_menu_format(this->_v_menu, height - 2, 1) != E_OK)
		return M_ERROR(false, "Error: set_menu_format(%p, %d, %d)\n", this->_v_menu, height - 2, 1);
	if (this->_v_value_selectable == true && menu_opts_off(this->_v_menu, O_ONEVALUE) != E_OK)
		return M_ERROR(false, "Error: menu_opts_off(%p, %d)\n", this->_v_menu, O_ONEVALUE);
	if (post_menu(this->_v_menu) != E_OK)
		return M_ERROR(false, "Error: post_menu(%p)\n", this->_v_menu);
	return true;
}
