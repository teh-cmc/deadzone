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

#include <c_menu.h>
#include <c_event.h>
#include <e_obj_type.h>
#include <tools.h>
#include <d_menu.h>
#include <c_ncurses.h>
#include <c_pos.h>
#include <stdlib.h>
#include <d_color_ui.h>

/* constructer destructer */

c_menu::c_menu(c_ncurses* ncurses,
	       c_event* event,
	       c_base_container* parent,
	       e_menu_type menu_type,
	       bool render_active,
	       bool value_selectable,
	       bool multi_selection) : c_base_container(E_MENU,
							ncurses,
							event,
							parent,
							false,
							false,
							false,
							render_active),
				       _v_menu(NULL),
				       _v_items(NULL),
				       _v_sub_win_menu(NULL),
				       _v_menu_type(menu_type),
				       _v_driver_action(E_NOTHING_DRIVER),
				       _v_init(D_MENU_NO_INIT),
				       _v_nb_items(0),
				       _v_update(false),
				       _v_value_selectable(value_selectable),
				       _v_multi_selection(multi_selection),
				       _v_checked_char('X')
{
	this->_v_window.f_get_magnetic_border()->f_set(false, false, false, false);
}

c_menu::~c_menu(void)
{
	this->_f_clear_menu_data();
}

/* public function */

bool	c_menu::f_init(const char* title, int x, int y, int width, int height)
{
	if (this->_v_init != D_MENU_DURING_INIT)
		return M_ERROR_NO_ARGS(false, "Error: menu is already init\n");
	if (this->_f_init_title(title) == false ||
	    this->_v_window.f_init(x, y, width, height) == false ||
	    (this->_v_update == false && this->_f_init_event_method() == false))
		return false;
	return true;
}

void	c_menu::f_set_checked_char(char checked_char)
{
	this->_v_checked_char = checked_char;
}

bool	c_menu::f_treat_render(void)
{
	if (this->_f_render_menu() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_menu::f_treat_keyboard(int key)
{
	return this->_f_treat_keyboard_method(key);
}

bool	c_menu::f_event_escape(void)
{
	this->f_render_active_off();
	return true;
}

bool	c_menu::f_event_key_down(void)
{
	ITEM*	curr_item = current_item(this->_v_menu);

	if (curr_item == NULL)
		return M_ERROR_NO_ARGS(false, "Error: current item pointer = NULL\n");
	if (item_index(curr_item) < this->_v_nb_items - 1)
		this->_v_driver_action = E_DOWN_DRIVER;
	else
		this->_v_driver_action = E_FIRST_DRIVER;
	return true;
}

bool	c_menu::f_event_key_up(void)
{
	ITEM*	curr_item = current_item(this->_v_menu);

	if (curr_item == NULL)
		return M_ERROR_NO_ARGS(false, "Error: current item pointer = NULL\n");
	if (item_index(curr_item) > 0)
		this->_v_driver_action = E_UP_DRIVER;
	else
		this->_v_driver_action = E_LAST_DRIVER;
	return true;
}

e_menu_type	c_menu::f_get_menu_type(void)
{
	return this->_v_menu_type;
}

bool	c_menu::f_use_callback_by_mouse_y(int mouse_y)
{
	int	item_y = mouse_y - getbegy(this->_v_sub_win_menu);
	void*	ptr_func;

	if (item_y >= this->_v_nb_items)
		return true;
	ptr_func = item_userptr(this->_v_items[item_y]);
	if (ptr_func == NULL)
		return M_ERROR(false, "Error: item_userptr(%p), item_y = %d\n", this->_v_items[item_y], item_y);
	return ((c_menu::t_single_callback)(ptr_func))(this->_v_ncurses, this);
}

const char*	c_menu::f_current_item_name(void)
{
	ITEM*		curr_item;
	const char*	name;

	curr_item = current_item(this->_v_menu);
	if (curr_item == NULL)
		return M_ERROR_NO_ARGS((const char*)(NULL), "Error: current item pointer = NULL\n");
	name = item_name(curr_item);
	if (name == NULL)
		return M_ERROR_NO_ARGS((const char*)(NULL), "Error: current item name pointer = NULL\n");
	return name;
}

const char*	c_menu::f_current_item_description(void)
{
	ITEM*		curr_item;
	const char*	description;

	curr_item = current_item(this->_v_menu);
	if (curr_item == NULL)
		return M_ERROR((const char*)(NULL), "Error: current_item(%p)\n", this->_v_menu);
	description = item_description(curr_item);
	if (description == NULL)
		return M_ERROR((const char*)(NULL), "Error: item_description(%p)\n", curr_item);
	return description;
}

const char*	c_menu::f_item_name_by_mouse_y(int mouse_y)
{
	int	index = mouse_y - getbegy(this->_v_sub_win_menu);
	int	item_count = this->f_item_count();

	if (item_count == ERR)
		return M_ERROR((const char*)(NULL), "Error: item_count = %d\n", item_count);
	if (index < 0 || index >= item_count)
		return M_ERROR((const char*)(NULL), "Error: index = %d\n", index);
	return this->_v_items[index]->name.str;
}

const char*	c_menu::f_item_name_by_index(int index)
{
	const char*	name;

	if (index < 0 || index >= this->f_item_count())
		return NULL;
	name = item_name(this->_v_items[index]);
	if (name == NULL)
		return M_ERROR_NO_ARGS((const char*)(NULL), "Error: name = NULL\n");
	return name;
}

const char*	c_menu::f_item_description_by_index(int index)
{
	const char*	description;
	
	if (index < 0 || index >= this->f_item_count())
		return NULL;
	description = item_description(this->_v_items[index]);
	if (description == NULL)
		return M_ERROR_NO_ARGS((const char*)(NULL), "Error: description = NULL\n");
	return description;
}

int	c_menu::f_current_item_index(void)
{
	ITEM*	curr_item;
	int	curr_item_index;

	curr_item = current_item(this->_v_menu);
	if (curr_item == NULL)
		return M_ERROR(-1, "Error: current_item(%p)\n", this->_v_menu);
	curr_item_index = item_index(curr_item);
	if (curr_item_index < 0)
		return M_ERROR(-1, "Error: item_index(%p)\n", curr_item_index);
	return curr_item_index;
}

ITEM*	c_menu::f_current_item(void)
{
	return current_item(this->_v_menu);
}

int	c_menu::f_item_count(void)
{
	return item_count(this->_v_menu);
}

int	c_menu::f_get_index_where_clicked(int mouse_y)
{
	if (mouse_y < 0)
		M_ERROR_VOID("Error: bad mouse_y: %d\n", mouse_y);
	return mouse_y - getbegy(this->_v_sub_win_menu);
}

bool	c_menu::f_get_value_selectable(void)
{
	return this->_v_value_selectable;
}

bool	c_menu::f_get_multi_selection(void)
{
	return _v_multi_selection;
}

bool	c_menu::f_set_value_all_item(bool value)
{
	int	i;

	i = 0;
	while (i < this->_v_nb_items)
	{
		if (set_item_value(this->_v_items[i], value) != E_OK)
			return M_ERROR(false, "Error: set_item_value(%p, %d)\n", this->_v_items[i], (int)(value));
		++i;
	}
	return true;
}

bool	c_menu::f_get_item_value_by_index(int index)
{
	if (index >= this->_v_nb_items)
		return false;
	return item_value(this->_v_items[index]);
}

bool	c_menu::f_do_driver_action(e_driver_action action)
{
	if (menu_driver(this->_v_menu, action) != E_OK)
		return M_ERROR(false, "Error: menu_driver(%p, %d)\n", this->_v_menu, action);
	return true;
}

int	c_menu::f_get_first_item_selected_index(void)
{
	int	i;

	i = 0;
	while (i < this->_v_nb_items)
	{
		if (item_value(this->_v_items[i]) == true)
			return i;
		++i;
	}
	return -1;
}

bool	c_menu::f_get_items_selected_vector_index(std::vector<int>* l_index)
{
	int	i;

	i = 0;
	while (i < this->_v_nb_items)
	{
		if (item_value(this->_v_items[i]) == true &&
		    tools::f_push_in_container(l_index, i, E_PUSH_BACK_INSERTION) == false)
			return D_ERR_STL_PUSH;
		++i;
	}
	return true;
}

/* protected function */

bool	c_menu::_f_render_menu(void)
{
	if (this->_f_draw_menu() == ERR ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_menu::_f_draw_menu(void)
{
	if (this->__f_passive_resfresh() == false)
		return false;
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_MENU)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_MENU));
	if (tools::f_my_border(this->_v_window.f_get_window()) == false)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (this->_v_driver_action != E_NOTHING_DRIVER)
	{
		if (menu_driver(this->_v_menu, this->_v_driver_action) != E_OK)
		{
			this->_v_driver_action = E_NOTHING_DRIVER;
			return M_ERROR(false, "Error: menu_driver(%p, %d)\n", this->_v_menu, this->_v_driver_action);
		}
		this->_v_driver_action = E_NOTHING_DRIVER;
	}
	if (this->__f_display_selected_items() == false ||
	    this->_f_render_title() == false)
		return false;
	return true;
}

bool	c_menu::_f_init_event_method(void)
{
	if (this->_f_add_common_callback('q', (t_common_callback)(&c_menu::f_event_escape)) == false ||
	    this->_f_add_common_callback(KEY_DOWN, (t_common_callback)(&c_menu::f_event_key_down)) == false ||
	    this->_f_add_common_callback(KEY_UP, (t_common_callback)(&c_menu::f_event_key_up)) == false)
		return false;
	return true;
}

bool	c_menu::_f_create_menu(void)
{
	this->__f_clear_menu_pointer();
	this->_v_menu = new_menu(this->_v_items);
	if (this->_v_menu == NULL)
		return M_ERROR(false, "Error: new_menu(%p)\n", this->_v_items);
	return true;
}

int	c_menu::_f_length_of_the_longest_item(const char** items)
{
	int	i, len, tmp;

	i = 0;
	len = 0;
	while (i < this->_v_nb_items)
	{
		tmp = tools::f_strlen(items[i]);
		if (len < tmp)
			len = tmp;
		++i;
	}
	return len;
}

void	c_menu::_f_clear_menu_data(void)
{
	int	i;

	this->__f_clear_menu_pointer();
	if (this->_v_items != NULL)
	{
		i = 0;
		while (i < this->_v_nb_items)
		{
			if (free_item(this->_v_items[i]) != E_OK)
				M_ERROR_VOID("Error: free_item(%p)\n", this->_v_items[i]);
			this->_v_items[i] = NULL;
			++i;
		}
		free(this->_v_items);
		this->_v_items = NULL;
	}
	if (this->_v_sub_win_menu != NULL)
	{
		if (delwin(this->_v_sub_win_menu) == ERR)
			M_ERROR_VOID("Error: delwin(%p)\n", this->_v_sub_win_menu);
		this->_v_sub_win_menu = NULL;
	}
}

/* private function */

void	c_menu::__f_clear_menu_pointer(void)
{
	if (this->_v_menu != NULL)
	{
		if (unpost_menu(this->_v_menu) != E_OK)
			M_ERROR_VOID("Error: unpost_menu(%p)\n", this->_v_menu);
		if (free_menu(this->_v_menu) != E_OK)
			M_ERROR_VOID("Error: free_menu(%p)\n", this->_v_menu);
		this->_v_menu = NULL;
	}
}

bool	c_menu::__f_passive_resfresh(void)
{
	bool	item_value_saved[this->_v_nb_items];

	if (this->_v_value_selectable == true)
		this->__f_save_item_value(item_value_saved);
	if (unpost_menu(this->_v_menu) != E_OK)
		return M_ERROR(false, "Error: unpost_menu(%p)\n", this->_v_menu);
	if (post_menu(this->_v_menu) != E_OK)
		return M_ERROR(false, "Error: post_menu(%p)\n", this->_v_menu);
	if (this->_v_value_selectable == true && this->__f_affect_item_value_saved(item_value_saved) == false)
		return false;
	return true;
}

void	c_menu::__f_save_item_value(bool* item_value_saved)
{
	int	i;

	i = 0;
	while (i < this->_v_nb_items)
	{
		item_value_saved[i] = item_value(this->_v_items[i]);
		++i;
	}
}

bool	c_menu::__f_affect_item_value_saved(bool* item_value_saved)
{
	int	i;

	i = 0;
	while (i < this->_v_nb_items)
	{
		if (set_item_value(this->_v_items[i], item_value_saved[i]) != E_OK)
			return M_ERROR(false, "Error: set_item_value(%p, %d)\n", this->_v_items[i], (int)(item_value_saved[i]));
		++i;
	}
	return true;
}

bool	c_menu::__f_display_selected_items(void)
{
	int	i;

	i = 0;
	while (i < this->_v_nb_items)
	{
		if (item_value(this->_v_items[i]) == true && tools::f_my_mvwaddnstr(this->_v_sub_win_menu, -1, i, 0, &this->_v_checked_char, 1) == false)
			return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, \"%s\", %d)\n", this->_v_sub_win_menu, -1, i, 0, &this->_v_checked_char, 1);
		++i;
	}
	return true;
}
