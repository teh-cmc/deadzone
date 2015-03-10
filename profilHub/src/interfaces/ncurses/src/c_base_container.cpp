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

#include <c_base_container.h>
#include <tools.h>
#include <c_button.h>
#include <c_event.h>
#include <c_data.h>
#include <d_mouse.h>
#include <c_menu.h>
#include <e_menu_type.h>

/* constructer destructer */

c_base_container::c_base_container(e_obj_type obj_type,
				   c_ncurses* ncurses,
				   c_event* event,
				   c_base_container* parent,
				   bool width_resizable,
				   bool height_resizable,
				   bool movable,
				   bool render_active) : _v_obj_type(obj_type),
							 _v_window(parent, width_resizable, height_resizable, movable),
							 _v_ncurses(ncurses),
							 _v_event(event),
							 _v_parent(parent),
							 _v_scroll_tool(this),
							 _v_title(NULL),
							 __v_different_keyboard(NULL),
							 __v_different_mouse(NULL),
							 __v_render_active(render_active),
							 __v_data(NULL)
{

}

c_base_container::~c_base_container(void)
{
	tools::f_delete_aptr(this->_v_title);
	tools::f_delete_ptr_container(this->_v_container_child);
	this->_v_container_child.clear();
	this->__v_common_callback_map.clear();
	this->__v_single_callback_map.clear();
}

/* public function */

bool	c_base_container::f_not_focus_anymore(void)
{
	return true;
}

bool	c_base_container::f_add_child(c_base_container* child, e_insertion_child insertion)
{
	if (this->__f_need_scrollbars() == true && this->_v_scroll_tool.f_enable_scrollbars() == false)
		return false;
	if (tools::f_push_in_container(&this->_v_container_child, child, insertion) == false)
		return false;
	return true;
}

bool	c_base_container::f_delete_child_by_index(unsigned int index)
{
	if (index >= this->_v_container_child.size())
		return M_ERROR(false, "Error: index = %d > child number = %u\n", index, this->_v_container_child.size());
	delete this->_v_container_child[index];
	this->_v_container_child.erase(this->_v_container_child.begin() + index);
	if (this->__f_need_scrollbars() == false)
		this->_v_scroll_tool.f_disable_scrollbars();
	return true;
}

bool	c_base_container::f_delete_child_by_ptr(c_base_container* ptr_child)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i] == ptr_child)
		{
			delete this->_v_container_child[i];
			this->_v_container_child.erase(this->_v_container_child.begin() + i);
			if (this->__f_need_scrollbars() == false)
				this->_v_scroll_tool.f_disable_scrollbars();
			return true;
		}
		++i;
	}
	return M_ERROR(true, "Error; ptr_child = %p, not find in container child\n", ptr_child);
}

void	c_base_container::f_delete_all_child(void)
{
	tools::f_delete_ptr_container(this->_v_container_child);
}

bool	c_base_container::f_add_single_callback(int key, t_single_callback single_callback)
{
	try
	{
		if (this->__v_single_callback_map.find(key) != this->__v_single_callback_map.end())
			return M_ERROR(false, "Error: the key %d is already used by a single callback map\n", key);
		this->__v_single_callback_map[key] = single_callback;
	}
	catch (...)
	{
		return D_ERR_STL_PUSH;
	}
	return true;
}

bool	c_base_container::f_resize_by_ratio(float rw, float rh)
{
	unsigned int	i, size;

	if (this->_v_window.f_resize_by_ratio(rw, rh) == false)
		return false;
	if (wclear(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: wclear(%p)\n", this->_v_window.f_get_window());
	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_resize_by_ratio(rw, rh) == false)
			return false;
		++i;
	}
	return true;
}

bool	c_base_container::f_magnetic_borders(void)
{
	unsigned int	i, size;

	if (this->__f_check_borders() == false)
		return false;
	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_magnetic_borders() == false)
			return false;
		++i;
	}
	return true;
}

bool	c_base_container::f_have_obj(e_obj_type obj_type)
{
	unsigned int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == obj_type)
			return true;
		++i;
	}
	return false;
}

e_obj_type	c_base_container::f_get_obj_type(void)
{
	return this->_v_obj_type;
}

c_window*	c_base_container::f_get_window(void)
{
	return &this->_v_window;
}

c_base_container*	c_base_container::f_get_parent(void)
{
	return this->_v_parent;
}

c_base_container*	c_base_container::f_get_child_by_index(unsigned int index)
{
	if (index >= this->_v_container_child.size())
		return NULL;
	return this->_v_container_child[index];
}

c_base_container*	c_base_container::f_get_child_by_type(e_obj_type type)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == type)
			return this->_v_container_child[i];
		++i;
	}
	return NULL;
}

std::vector<c_base_container*>*	c_base_container::f_get_child_vect(void)
{
	return &this->_v_container_child;
}

c_ncurses*	c_base_container::f_get_ncurses(void)
{
	return this->_v_ncurses;
}

bool	c_base_container::f_get_render_active(void)
{
	return this->__v_render_active;
}

void	c_base_container::f_render_active_off(void)
{
	this->__v_render_active = false;
}

void	c_base_container::f_render_active_on(void)
{
	this->__v_render_active = true;
}

void	c_base_container::f_set_render_active_all_child(bool value)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		this->_v_container_child[i]->__v_render_active = value;
		++i;
	}
}

e_focus_type	c_base_container::f_get_focus_type(void)
{
	return this->__v_focus_type;
}

void	c_base_container::f_set_focus_type(e_focus_type focus_type)
{
	this->__v_focus_type = focus_type;
}

int	c_base_container::f_get_info_size(char info)
{
	if (info == 'x')
		return getbegx(this->_v_window.f_get_window());
	else if (info == 'y')
		return getbegy(this->_v_window.f_get_window());
	else if (info == 'w')
		return getmaxx(this->_v_window.f_get_window());
	else if (info == 'h')
		return getmaxy(this->_v_window.f_get_window());
	else if (info == 'X')
		return getbegx(this->_v_window.f_get_window()) + getmaxx(this->_v_window.f_get_window());
	else if (info == 'Y')
		return getbegy(this->_v_window.f_get_window()) + getmaxy(this->_v_window.f_get_window());
	return -1;
}

void	c_base_container::f_set_different_keyboard(t_different_keyboard func_ptr)
{
	this->__v_different_keyboard = func_ptr;
}

void	c_base_container::f_set_different_mouse(t_different_mouse func_ptr)
{
	this->__v_different_mouse = func_ptr;
}

int	c_base_container::f_child_count(void)
{
	return this->_v_container_child.size();
}

bool	c_base_container::f_move(int x, int y)
{
	int	i, size, dx, dy;

	dx = x - this->f_get_info_size('x');
	dy = y - this->f_get_info_size('y');
	if (tools::f_my_mvwin(this->_v_window.f_get_window(), y, x) == false)
		return M_ERROR(false, "tools::f_my_mvwin(%p, %d, %d)", this->_v_window.f_get_window(), y, x);
	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (tools::f_my_mvwin(this->_v_container_child[i]->f_get_window()->f_get_window(),
				      this->_v_container_child[i]->f_get_info_size('y') + dy,
				      this->_v_container_child[i]->f_get_info_size('x') + dx) == false)
			return M_ERROR(false, "tools::f_my_mvwin(%p, %d, %d)", this->_v_container_child[i]->f_get_window()->f_get_window(), this->_v_container_child[i]->f_get_info_size('y') + dy, this->_v_container_child[i]->f_get_info_size('x') + dx);
		++i;
	}
	return true;
}

bool	c_base_container::f_resize(int w, int h)
{
	if (tools::f_my_wresize(this->_v_window.f_get_window(), h, w) == false)
		return M_ERROR(false, "tools::f_my_mvwin(%p, %d, %d)", this->_v_window.f_get_window(), h, w);
	return true;
}

bool	c_base_container::f_exterior_collide(bool parent_border)
{
	int	x_beg, y_beg, x_max, y_max;

	this->__f_set_cadre(&x_beg, &y_beg, &x_max, &y_max, parent_border);
	if ((this->f_get_info_size('x') < x_beg) ||
	    (this->f_get_info_size('y') < y_beg) ||
	    ((this->f_get_info_size('x') + this->f_get_info_size('w')) > x_max) ||
	    ((this->f_get_info_size('y') + this->f_get_info_size('h')) > y_max))
		return true;
	return false;
}

bool	c_base_container::f_init_scroll_callbacks(void)
{
	if (this->_f_add_common_callback(KEY_UP, &c_base_container::__f_scroll_top) == false ||
	    this->_f_add_common_callback(KEY_DOWN, &c_base_container::__f_scroll_bot) == false ||
	    this->_f_add_common_callback(KEY_LEFT, &c_base_container::__f_scroll_left) == false ||
	    this->_f_add_common_callback(KEY_RIGHT, &c_base_container::__f_scroll_right) == false ||
	    this->_f_add_common_callback('h', &c_base_container::__f_scroll_left) == false ||
	    this->_f_add_common_callback('j', &c_base_container::__f_scroll_bot) == false ||
	    this->_f_add_common_callback('k', &c_base_container::__f_scroll_top) == false ||
	    this->_f_add_common_callback('l', &c_base_container::__f_scroll_right) == false)
		return false;
	return true;
}

void	c_base_container::f_delete_scroll_callbacks(void)
{
	this->__v_common_callback_map.erase(KEY_UP);
	this->__v_common_callback_map.erase(KEY_DOWN);
	this->__v_common_callback_map.erase(KEY_LEFT);
	this->__v_common_callback_map.erase(KEY_RIGHT);
	this->__v_common_callback_map.erase('h');
	this->__v_common_callback_map.erase('j');
	this->__v_common_callback_map.erase('k');
	this->__v_common_callback_map.erase('l');
}

void	c_base_container::f_print_obj_type(void)
{
	switch	(this->_v_obj_type)
	{
		case	E_CONTAINER:	tools::f_debug_file("container");	return ;
		case	E_TOOLBAR:	tools::f_debug_file("toolbar");		return ;
		case	E_STATE_BAR:	tools::f_debug_file("state_bar");	return ;
		case	E_ZONE:		tools::f_debug_file("zone");		return ;
		case	E_BUTTON:	tools::f_debug_file("button");		return ;
		case	E_MENU:		tools::f_debug_file("menu");		return ;
		case	E_POPUP:	tools::f_debug_file("popup");		return ;
		case	E_LABEL:	tools::f_debug_file("label");		return ;
		case	E_TAB_MANAGER:	tools::f_debug_file("tab_manager");	return ;
		case	E_TAB:		tools::f_debug_file("tab");		return ;
		case	E_DATA:		tools::f_debug_file("data");		return ;
		case	E_INDICATOR:	tools::f_debug_file("indicator");	return ;
		case	E_GRAPH:	tools::f_debug_file("graph");		return ;
		case	E_GRAPHIC:	tools::f_debug_file("graphic");		return ;
		case	E_TEXT_ZONE:	tools::f_debug_file("text_zone");	return ;
	}
}

const char*	c_base_container::f_get_title(void)
{
	return this->_v_title;
}

/* protected function */

bool	c_base_container::_f_init_title(const char* title)
{
	tools::f_delete_aptr(this->_v_title);
	this->_v_title = tools::f_strdup(title);
	if (this->_v_title == NULL)
		return M_ERROR(false, "Error: tools::f_strdup(\"%s\")\n", title);
	return true;
}

bool	c_base_container::_f_render_child(void)
{
	size_t	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->__v_render_active == true &&
		    this->_v_container_child[i]->f_exterior_collide(false) == false &&
		    this->_v_container_child[i]->f_treat_render() == false)
			return false;
		++i;
	}
	return true;
}

int	c_base_container::_f_treat_keyboard_method(int key)
{
	int	ret;

	ret = this->_f_treat_singles_callbacks(key);
	if (ret != 0)
		return ret;
	if (this->__v_render_active == false)
		return 0;
	if (this->__v_common_callback_map.find(key) != this->__v_common_callback_map.end())
	{
		if ((this->*__v_common_callback_map[key])() == false)
			return -1;
		else
			return 1;
	}
	return 0;
}

int	c_base_container::_f_treat_singles_callbacks(int key)
{
	if (this->__v_single_callback_map.find(key) != this->__v_single_callback_map.end())
	{
		if ((this->__v_single_callback_map[key])(this->_v_ncurses, this) == false)
			return -1;
		return 1;
	}
	return 0;
}

bool	c_base_container::_f_add_common_callback(int key, t_common_callback callback)
{
	try
	{
		if (this->__v_single_callback_map.find(key) != this->__v_single_callback_map.end())
			return M_ERROR(false, "Error: the key %d, '%c' is already used by a single callback map\n", key, key);
		if (this->__v_common_callback_map.find(key) != this->__v_common_callback_map.end())
			return M_ERROR(false, "Error: the key %d, '%c' is already used by a common callback\n", key, key);
		this->__v_common_callback_map[key] = callback;
	}
	catch (...)
	{
		return D_ERR_STL_PUSH;
	}
	return true;
}

bool	c_base_container::_f_render_title(void)
{
	if (this->_v_title != NULL)
	{
		if (this->_v_obj_type == E_BUTTON)
		{
			if (tools::f_my_mvwaddnstr(this->_v_window.f_get_window(), 2, 0, 0, this->_v_title, getmaxx(this->_v_window.f_get_window())) == false)
				return false; // wtf error
		}
		else
		{
			if (tools::f_my_mvwaddnstr(this->_v_window.f_get_window(), 5, 0, 2, this->_v_title, getmaxx(this->_v_window.f_get_window()) - 4) == false)
				return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, \"%s\", %d)\n", this->_v_window.f_get_window(), 5, 0, 2, this->_v_title, getmaxx(this->_v_window.f_get_window()) - 4);
		}
	}
	return true;
}

bool	c_base_container::_f_call_button(e_button_type button)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i <  size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_BUTTON &&
		    (((c_button*)(this->_v_container_child[i]))->f_get_button_type() == button))
			return ((c_button*)(this->_v_container_child[i]))->f_use_callback();
		++i;
	}
	return true;
}

bool	c_base_container::_f_click_on_me(void)
{
	WINDOW*	win = this->_v_window.f_get_window();

	if (this->_v_event->f_mouse_x() >= getbegx(win) && this->_v_event->f_mouse_x() < (getbegx(win) + getmaxx(win)) &&
	    this->_v_event->f_mouse_y() >= getbegy(win) && this->_v_event->f_mouse_y() < (getbegy(win) + getmaxy(win)))
		return true;
	return false;
}

bool	c_base_container::_f_send_mouse_event_to_child(void)
{
	int	i;

	i = this->_v_container_child.size() - 1;
	while (i >= 0)
	{
		if (this->_v_container_child[i]->f_get_render_active() == true &&
		    this->_v_container_child[i]->f_treat_mouse() == false)
			return false;
		--i;
	}
	return true;
}

/* private function */

void	c_base_container::__f_set_cadre(int* x_beg, int* y_beg, int* x_max, int* y_max, bool parent_border)
{
	if (this->_v_parent == NULL)
	{
		*x_beg = getbegx(stdscr);
		*y_beg = getbegy(stdscr);
		*x_max = getbegx(stdscr) + getmaxx(stdscr);
		*y_max = getbegy(stdscr) + getmaxy(stdscr);
	}
	else
	{
		*x_beg = this->_v_parent->f_get_info_size('x');
		*y_beg = this->_v_parent->f_get_info_size('y');
		*x_max = this->_v_parent->f_get_info_size('x') + this->_v_parent->f_get_info_size('w');
		*y_max = this->_v_parent->f_get_info_size('y') + this->_v_parent->f_get_info_size('h');
	}
	if (parent_border == true)
	{
		*x_beg += 1;
		*y_beg += 1;
		*x_max -= 1;
		*y_max -= 1;
	}
}

bool	c_base_container::__f_ui_obj_resizable(c_base_container* ui_obj)
{
	e_obj_type	obj_type = ui_obj->f_get_obj_type();

	if (obj_type == E_CONTAINER ||
	    obj_type == E_TOOLBAR ||
	    obj_type == E_STATE_BAR ||
	    obj_type == E_ZONE ||
	    obj_type == E_LABEL ||
	    obj_type == E_TAB_MANAGER ||
	    obj_type == E_TAB)
		return true;
	return false;
}

bool	c_base_container::__f_check_borders(void)
{
	WINDOW*	parent = this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr;

	switch	(this->_v_obj_type)
	{
		case	E_TOOLBAR:
			if (tools::f_my_wresize(this->_v_window.f_get_window(), 1, getmaxx(parent)) == ERR)
				return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", this->_v_window.f_get_window(), 1, getmaxx(parent));
			if (tools::f_my_mvwin(this->_v_window.f_get_window(), 0, 0) == ERR)
				return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", this->_v_window.f_get_window(), 0, 0);
			break;
		case	E_STATE_BAR:
			if (tools::f_my_wresize(this->_v_window.f_get_window(), 1, getmaxx(parent)) == ERR)
				return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", this->_v_window.f_get_window(), 1, getmaxx(parent));
			if (tools::f_my_mvwin(this->_v_window.f_get_window(), getmaxy(parent), 0) == ERR)
				return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", this->_v_window.f_get_window(), getmaxy(parent), 0);
			break;
		case	E_TAB:
			if (tools::f_my_wresize(this->_v_window.f_get_window(), getmaxy(parent) - getbegy(parent) - 2, getmaxx(parent) - getbegx(parent) - 2) == ERR)
				return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", this->_v_window.f_get_window(), 1, getmaxx(parent));
			if (tools::f_my_mvwin(this->_v_window.f_get_window(), getbegy(parent) + 2, getbegx(parent) + 1) == ERR)
				return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", this->_v_window.f_get_window(), getmaxy(parent), 0);
			break;
		case	E_CONTAINER:
			if (this->__f_check_borders_container(parent) == false)
				return false;
			break;
		default:
			break;
	}
	return true;
}

bool	c_base_container::__f_check_borders_container(WINDOW* parent)
{
	bool	toolbar = this->_v_parent ? this->_v_parent->f_have_obj(E_TOOLBAR) : false;
	bool	state_bar = this->_v_parent ? this->_v_parent->f_have_obj(E_STATE_BAR) : false;
	int	y = getbegy(parent);
	int	height = getmaxy(parent);

	if (toolbar == true)
	{
		y += 1;
		height -= 1;
	}
	if (state_bar == true)
		height -= 1;
	if (tools::f_my_wresize(this->_v_window.f_get_window(), height - 1, this->_v_parent ? getmaxx(this->_v_window.f_get_window()) : getmaxx(stdscr)) == ERR)
		return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", this->_v_window.f_get_window(), height - 1, this->_v_parent ? getmaxx(this->_v_window.f_get_window()) : getmaxx(stdscr));
	if (tools::f_my_mvwin(this->_v_window.f_get_window(), y, this->_v_parent ? getbegx(this->_v_window.f_get_window()) : getmaxy(stdscr)) == ERR)
		return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", this->_v_window.f_get_window(), y, this->_v_parent ? getbegx(this->_v_window.f_get_window()) : getmaxy(stdscr));
	return this->__f_replace_my_child();
}

bool	c_base_container::__f_replace_my_child(void)
{
	unsigned int		i, size;
	WINDOW*			curr_child_win;
	c_base_container*	obj;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->__f_ui_obj_resizable(this->_v_container_child[i]) == false)
		{
			++i;
			continue;
		}
		curr_child_win = this->_v_container_child[i]->f_get_window()->f_get_window();
		if (getbegx(curr_child_win) < getbegx(this->_v_window.f_get_window()))
			if (tools::f_my_mvwin(curr_child_win, getbegy(curr_child_win), getbegx(this->_v_window.f_get_window())) == ERR)
				return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", curr_child_win, getbegy(curr_child_win), getbegx(this->_v_window.f_get_window()));
		if (getbegy(curr_child_win) < getbegy(this->_v_window.f_get_window()))
			if (tools::f_my_mvwin(curr_child_win, getbegy(this->_v_window.f_get_window()), getbegx(curr_child_win)) == ERR)
				return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", curr_child_win, getbegy(this->_v_window.f_get_window()), getbegx(curr_child_win));
		obj = this->_v_container_child[i]->__f_the_closer_obj_on_my(E_TOP);
		if (obj != NULL)
		{
			if (getbegy(curr_child_win) <= getmaxy(obj->f_get_window()->f_get_window()))
				if (tools::f_my_mvwin(curr_child_win, getmaxy(obj->f_get_window()->f_get_window()) + 1, getbegx(curr_child_win)) == ERR)
					return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", curr_child_win, getmaxy(obj->f_get_window()->f_get_window()) + 1, getbegx(curr_child_win));
		}
		else
		{
			if (tools::f_my_mvwin(curr_child_win, getbegy(this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr) + 1, getbegx(curr_child_win)) == ERR)
				return M_ERROR(false, "Error: tools::f_my_mvwin(%p, %d, %d)\n", curr_child_win, getbegy(this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr) + 1, getbegx(curr_child_win));
		}
		obj = this->_v_container_child[i]->__f_the_closer_obj_on_my(E_RIGHT);
		if (obj != NULL)
		{
			if (getmaxx(curr_child_win) != getbegx(obj->f_get_window()->f_get_window()))
				if (tools::f_my_wresize(curr_child_win,
							getmaxy(curr_child_win),
							getbegx(obj->f_get_window()->f_get_window()) + (getbegx(obj->f_get_window()->f_get_window()) - getmaxx(curr_child_win))) == ERR)
					return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", curr_child_win, getmaxy(curr_child_win), getbegx(obj->f_get_window()->f_get_window()) + (getbegx(obj->f_get_window()->f_get_window()) - getmaxx(curr_child_win)));
		}
		else
		{
			if (tools::f_my_wresize(curr_child_win,
						getmaxy(curr_child_win),
						getmaxx(this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr) - getbegx(curr_child_win)) == ERR)
				return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", curr_child_win, getmaxy(curr_child_win), getmaxx(this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr) - getbegx(curr_child_win));
		}
		obj = this->_v_container_child[i]->__f_the_closer_obj_on_my(E_BOT);
		if (obj != NULL)
		{
			if (getmaxy(curr_child_win) != getbegy(obj->f_get_window()->f_get_window()))
				if (tools::f_my_wresize(curr_child_win,
							getmaxy(curr_child_win) + (getbegy(obj->f_get_window()->f_get_window()) - (getbegy(curr_child_win) + getmaxy(curr_child_win))),
							getmaxx(curr_child_win)) == ERR)
					return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", curr_child_win, getmaxy(curr_child_win) + (getbegy(obj->f_get_window()->f_get_window()) - (getbegy(curr_child_win) + getmaxy(curr_child_win))), getmaxx(curr_child_win));
		}
		else
		{
			if (tools::f_my_wresize(curr_child_win,
						(getmaxy(this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr) - getbegy(curr_child_win)),
						getmaxx(curr_child_win)) == ERR)
				return M_ERROR(false, "Error: tools::f_my_wresize(%p, %d, %d)\n", curr_child_win, (getmaxy(this->_v_parent ? this->_v_parent->f_get_window()->f_get_window() : stdscr) - getbegy(curr_child_win)), getmaxx(curr_child_win));
		}
		++i;
	}
	return true;
}

c_base_container*	c_base_container::__f_the_closer_obj_on_my(e_direction direction, bool superimpose)
{
	unsigned int			i, size;
	std::vector<c_base_container*>*	child_vect_parent;
	c_base_container*		the_closer_obj = NULL;
	c_base_container*		curr_obj;
	WINDOW*				win_curr_obj;
	WINDOW*				my_win = this->_v_window.f_get_window();

	if (this->_v_parent == NULL)
		return NULL;
	child_vect_parent = this->_v_parent->f_get_child_vect();
	i = 0;
	size = child_vect_parent->size();
	while (i < size)
	{
		curr_obj = (*child_vect_parent)[i];
		if (curr_obj != this)
		{
			win_curr_obj = curr_obj->f_get_window()->f_get_window();
			switch	(direction)
			{
				case	E_LEFT:
				case	E_RIGHT:
					if (((getbegy(win_curr_obj) >= getbegy(my_win)) && (getbegy(win_curr_obj) < getmaxy(my_win))) ||
					    ((getmaxy(win_curr_obj) >= getbegy(my_win)) && (getmaxy(win_curr_obj) < getmaxy(my_win))) ||
					    ((getbegy(win_curr_obj) < getbegy(my_win)) && (getmaxy(win_curr_obj) >= getmaxy(my_win))))
					{
						if (direction == E_LEFT)
						{
							if (superimpose == true)
							{
								if (getmaxx(win_curr_obj) <= getmaxx(my_win))
								{
									if (the_closer_obj == NULL || (getmaxx(win_curr_obj) > getmaxx(the_closer_obj->f_get_window()->f_get_window())))
										the_closer_obj = curr_obj;
								}
							}
							else
							{
								if (getmaxx(win_curr_obj) <= getbegx(my_win))
								{
									if (the_closer_obj == NULL || (getmaxx(win_curr_obj) > getmaxx(the_closer_obj->f_get_window()->f_get_window())))
										the_closer_obj = curr_obj;
								}
							}
						}
						else if (direction == E_RIGHT)
						{
							if (superimpose == true)
							{
								if (getbegx(win_curr_obj) > getbegx(my_win))
								{
									if (the_closer_obj == NULL || (getbegx(win_curr_obj) < getbegx(the_closer_obj->f_get_window()->f_get_window())))
										the_closer_obj = curr_obj;
								}
							}
							else
							{
								if (getbegx(win_curr_obj) > getmaxx(my_win))
								{
									if (the_closer_obj == NULL || (getbegx(win_curr_obj) < getbegx(the_closer_obj->f_get_window()->f_get_window())))
										the_closer_obj = curr_obj;
								}
							}
						}
					}
					break;
				case	E_TOP:
				case	E_BOT:
					if (((getbegx(win_curr_obj) >= getbegx(my_win)) && (getbegx(win_curr_obj) < (getbegx(my_win) + getmaxx(my_win)))) ||
					    (((getbegx(win_curr_obj) + getmaxx(win_curr_obj)) >= getbegx(my_win)) && ((getbegx(win_curr_obj) + getmaxx(win_curr_obj)) < getmaxx(my_win))) ||
					    ((getbegx(win_curr_obj) < getbegx(my_win)) && ((getbegx(win_curr_obj) + getmaxx(win_curr_obj)) >= (getbegx(my_win) + getmaxx(my_win)))))
					{
						if (direction == E_TOP)
						{
							if (superimpose == true)
							{
								if ((getbegy(win_curr_obj) + getmaxy(win_curr_obj)) <= (getbegy(my_win) + getmaxy(my_win)))
								{
									if (the_closer_obj == NULL || ((getbegy(win_curr_obj) + getmaxy(win_curr_obj)) > (getbegy(the_closer_obj->f_get_window()->f_get_window()) + getmaxy(the_closer_obj->f_get_window()->f_get_window()))))
										the_closer_obj = curr_obj;
								}
							}
							else
							{
								if ((getbegy(win_curr_obj) + getmaxy(win_curr_obj)) <= getbegy(my_win))
								{
									if (the_closer_obj == NULL || ((getbegy(win_curr_obj) + getmaxy(win_curr_obj)) > (getbegy(the_closer_obj->f_get_window()->f_get_window()) + getmaxy(the_closer_obj->f_get_window()->f_get_window()))))
										the_closer_obj = curr_obj;
								}
							}
						}
						else if (direction == E_BOT)
						{
							if (superimpose == true)
							{
								if (getbegy(win_curr_obj) > getbegy(my_win))
								{
									if (the_closer_obj == NULL || (getbegy(win_curr_obj) < getbegy(the_closer_obj->f_get_window()->f_get_window())))
										the_closer_obj = curr_obj;
								}
							}
							else
							{
								if (getbegy(win_curr_obj) > (getbegy(my_win) + getmaxy(my_win)))
								{
									if (the_closer_obj == NULL || (getbegy(win_curr_obj) < getbegy(the_closer_obj->f_get_window()->f_get_window())))
										the_closer_obj = curr_obj;
								}
							}
						}
					}
				case	E_NO_DIRECTION:
					break;
			};
		}
		++i;
	}
	return the_closer_obj;
}

bool	c_base_container::__f_scroll_top(void)
{
	return this->_v_scroll_tool.f_scroll(E_TOP);
}

bool	c_base_container::__f_scroll_bot(void)
{
	return this->_v_scroll_tool.f_scroll(E_BOT);
}

bool	c_base_container::__f_scroll_left(void)
{
	return this->_v_scroll_tool.f_scroll(E_LEFT);
}

bool	c_base_container::__f_scroll_right(void)
{
	return this->_v_scroll_tool.f_scroll(E_RIGHT);
}

bool	c_base_container::__f_need_scrollbars(void)
{
	return false;
}
