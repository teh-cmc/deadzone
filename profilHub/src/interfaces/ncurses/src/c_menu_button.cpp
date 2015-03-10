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

#include <c_menu_button.h>
#include <d_menu.h>
#include <c_button.h>
#include <tools.h>
#include <c_event.h>
#include <stdlib.h>
#include <d_color_ui.h>
#include <d_event.h>
#include <c_ui.h>
#include <d_mouse.h>

/* constucter destructer */

c_menu_button::c_menu_button(c_ncurses* ncurses,
			     c_event* event,
			     c_base_container* parent,
			     c_button* button,
			     e_menu_type menu_type) : c_menu(ncurses,
							     event,
							     parent,
							     menu_type,
							     false),
						      __v_button(button)
{

}

c_menu_button::~c_menu_button(void)
{

}

/* public function */

bool	c_menu_button::f_init_menu(const char** items,
				   const char** description,
				   c_menu::t_single_callback* ptr_fun_tab,
				   const char* title)
{
	if (this->_v_init != D_MENU_NO_INIT)
		return M_ERROR_NO_ARGS(false, "Error: menu button is already init\n");
	this->_v_init = D_MENU_DURING_INIT;
	if (this->__f_fill_menu(title, items, description, ptr_fun_tab, this->__v_button->f_get_pos()) == false ||
	    this->__f_init_menu_options() == false ||
	    this->__f_init_event_method() == false)
		return false;
	this->_v_init = D_MENU_INITED;
	return true;
}

bool	c_menu_button::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
	{
		if (this->_v_event->f_mouse_button_used(D_LEFT_BUTTON_CLICKED) == true)
			return this->__f_treat_mouse_menu();
	}
	else
		this->f_render_active_off();
	return true;
}

bool	c_menu_button::f_event_key_left(void)
{
	return true;
}

bool	c_menu_button::f_event_key_right(void)
{
	return true;
}

bool	c_menu_button::f_event_enter(void)
{
	ITEM*				curr_item = NULL;
	c_menu::t_single_callback	callback_menu = NULL;

	curr_item = current_item(this->_v_menu);
	if (curr_item == NULL)
		return M_ERROR_NO_ARGS(false, "Error: current item pointer is NULL\n");
	callback_menu = (c_menu::t_single_callback)(item_userptr(curr_item));
	if (callback_menu == NULL)
		return M_ERROR_NO_ARGS(false, "Error: callback menu pointer is NULL\n");
	return callback_menu(this->_v_ncurses, this);
}

bool	c_menu_button::sf_treat_menu_from_button_callback(c_ui* ui, e_menu_type menu_type)
{
	c_menu*	menu;

	menu = ui->f_get_menu_by_type(menu_type);
	if (menu == NULL)
		return false;
	if (menu->f_get_render_active() == true)
	{
		menu->f_render_active_off();
		return true;
	}
	ui->f_set_render_active_off_for_all_menus();
	menu->f_render_active_on();
	return true;
}

/* private function */

bool	c_menu_button::__f_treat_mouse_menu(void)
{
	return this->f_use_callback_by_mouse_y(this->_v_event->f_mouse_y());
}

bool	c_menu_button::__f_fill_menu(const char* title, const char** items, const char** description, c_menu::t_single_callback* ptr_fun_tab, c_pos* pos)
{
	this->_v_nb_items = tools::f_nb_element(items);
	if (this->_v_nb_items != tools::f_nb_element(description))
		return M_ERROR(false, "Error: nb item = %d != nb description = %d\n", this->_v_nb_items, tools::f_nb_element(description));
	if (this->_v_nb_items != tools::f_nb_element(ptr_fun_tab))
		return M_ERROR(false, "Error: nb item = %d != nb function pointer = %d\n", this->_v_nb_items, tools::f_nb_element(ptr_fun_tab));
	if (this->__f_create_items(items, description, ptr_fun_tab) == false ||
	    this->_f_create_menu() == false ||
	    this->__f_init_window_menu(title, items, description, pos) == false)
		return false;
	return true;
}

bool	c_menu_button::__f_init_menu_options(void)
{
	if (set_menu_fore(this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU_SELECTION)) != E_OK)
		return M_ERROR(false, "Error: set_menu_fore(%p, %d)\n", this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU_SELECTION));
	if (set_menu_back(this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU)) != E_OK)
		return M_ERROR(false, "Error: set_menu_back(%p, %d)\n", this->_v_menu, COLOR_PAIR(D_COLOR_PAIR_MENU));
	return true;
}

bool	c_menu_button::__f_create_items(const char** items, const char** description, c_menu::t_single_callback* ptr_fun_tab)
{
	int	i;

	this->_v_items = (ITEM**)calloc(this->_v_nb_items, sizeof(ITEM*));
	if (this->_v_items == NULL)
		return M_ERROR(false, "Error: calloc(%d, %d)\n", this->_v_nb_items, sizeof(ITEM*));
	i = 0;
	while (i < this->_v_nb_items)
	{
		this->_v_items[i] = new_item(items[i], description[i]);
		if (this->_v_items[i] == NULL)
			return M_ERROR(false, "Error: new_item(\"%s\", \"%s\")\n", items[i], description[i]);
		if (set_item_userptr(this->_v_items[i], (void*)(ptr_fun_tab[i])) != E_OK)
			return M_ERROR(false, "Error: set_item_userptr(\"%s\", %p)\n", this->_v_items[i], (void*)(ptr_fun_tab[i]));
		++i;
	}
	return true;
}

bool	c_menu_button::__f_init_window_menu(const char* title, const char** items, const char** description, c_pos* pos)
{
	int	width = this->_f_length_of_the_longest_item(items) + this->_f_length_of_the_longest_item(description) + 5;

	if (this->f_init(title, pos->v_x, pos->v_y + 1, width, this->_v_nb_items + 2) == false)
		return false;
	if (set_menu_win(this->_v_menu, this->_v_window.f_get_window()) != E_OK)
		return M_ERROR(false, "Error: set_menu_win(%p, %p)\n", this->_v_menu, this->_v_window.f_get_window());
	this->_v_sub_win_menu = derwin(this->_v_window.f_get_window(), this->_v_nb_items, width - 1, 1, 1);
	if (this->_v_sub_win_menu == NULL)
		return M_ERROR(false, "Error: derwin(%p, %d, %d, %d, %d)\n", this->_v_window.f_get_window(), this->_v_nb_items, width - 1, 1, 1);
	if (set_menu_sub(this->_v_menu, this->_v_sub_win_menu) != E_OK)
		return M_ERROR(false, "Error: set_menu_sub(%p, %p)\n", this->_v_menu, this->_v_sub_win_menu);
	if (post_menu(this->_v_menu) != E_OK)
		return M_ERROR(false, "Error: post_menu(%p)\n", this->_v_menu);
	return true;
}

bool	c_menu_button::__f_init_event_method(void)
{
	if (this->_f_add_common_callback(KEY_LEFT, (t_common_callback)(&c_menu_button::f_event_key_left)) == false ||
	    this->_f_add_common_callback(KEY_RIGHT, (t_common_callback)(&c_menu_button::f_event_key_right)) == false ||
	    this->_f_add_common_callback(D_ENTER, (t_common_callback)(&c_menu_button::f_event_enter)) == false)
		return false;
	return true;
}
