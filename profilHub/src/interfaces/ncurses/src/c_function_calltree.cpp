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

#include <c_function_calltree.h>
#include <tools.h>
#include <c_event.h>
#include <c_ncurses.h>
#include <c_base_container.h>
#include <d_calltree.h>
#include <callbacks_buttons.h>
#include <d_color_ui.h>
#include <c_popup_manager.h>
#include <c_ui.h>

/* constructer destructer */

c_function_calltree::c_function_calltree(c_ncurses* ncurses,
					 c_event* event,
					 c_base_container* parent,
					 c_function_calltree* function_parent) : __v_open(true),
										 __v_close_type(E_NOT_CLOSE),
										 __v_open_close_button(NULL),
										 __v_function_button(NULL),
										 __v_ncurses(ncurses),
										 __v_event(event),
										 __v_parent(parent),
										 __v_function_parent(function_parent)
{

}

c_function_calltree::~c_function_calltree(void)
{
	tools::f_delete_ptr_container(this->__v_sub_function_vect);
}

/* public function */

bool	c_function_calltree::f_init(const char* name, int x_depth, int y_depth)
{
	int	len = tools::f_strlen(name);
	char	str[len + 2];

	str[0] = ' ';
	tools::f_strncpy(str + 1, name, len);
	str[len + 1] = ' ';
	str[len + 2] = 0;
	this->__v_info_function.v_name = tools::f_strdup(str);
	if (this->__v_info_function.v_name == NULL)
		return M_ERROR(false, "Error: strdup(\"%s\")\n", str);
	this->__v_depth.f_set(x_depth, y_depth);
	return this->__f_init_buttons();
}

bool	c_function_calltree::f_add_sub_function(const char* name)
{
	c_function_calltree*	function = new (std::nothrow) c_function_calltree(this->__v_ncurses, this->__v_event, this->__v_parent, this);

	if (function == NULL)
		return D_ERR_ALLOC;
	if (tools::f_push_in_container(&this->__v_sub_function_vect, function, E_PUSH_BACK_INSERTION) == false)
	{
		delete function;
		return false;
	}
	if (this->__f_move_parent_under_children(D_Y_FUNCTION_OFFSET) == false ||
	    function->f_init(name,
			     this->__v_depth.v_x + D_X_FUNCTION_OFFSET,
			     this->__v_depth.v_y + (D_Y_FUNCTION_OFFSET * this->__f_nb_child())) == false)
		return false;
	return true;
}

bool	c_function_calltree::f_display_branch(void)
{
	int			x, i, size, nb_child;
	WINDOW*			win = this->__v_parent->f_get_window()->f_get_window();

	if (this->__v_open == false)
		return true;
	if (win == NULL)
		return M_ERROR_NO_ARGS(false, "Error: win = NULL\n");
	nb_child = this->__f_nb_child();
	x = this->__v_depth.v_x + D_X_BRANCH_OFFSET;
	switch	(nb_child)
	{
		case	0:
			return true;
		case	1:
			if (this->__f_draw_branch_to_one_child(win, x) == false)
				return false;
			break;
		default:
			if (this->__f_draw_branch_to_multiple_child(win, x, nb_child) == false)
				return false;
			break;
	}
	for (i = 0, size = this->__v_sub_function_vect.size(); i < size; ++i)
		if (this->__v_sub_function_vect[i]->f_display_branch() == false)
			return false;
	return true;
}

bool	c_function_calltree::__f_draw_branch_to_one_child(WINDOW* win, int x)
{
	if (tools::f_my_mvwaddch(win, this->__v_depth.v_y + 1, x, ACS_LLCORNER) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')", win, this->__v_depth.v_y + 1, x, ACS_LLCORNER);
	if (this->__f_draw_hline_branch(x + 1, this->__v_depth.v_y + 1) == false)
		return false;
	return true;
}

bool	c_function_calltree::__f_draw_branch_to_multiple_child(WINDOW* win, int x, int nb_child)
{
	int			i, size;
	std::vector<int>	pos_child_vect;

	if (this->__f_fill_pos_child_vect(&pos_child_vect) == false)
		return false;
	if (tools::f_my_mvwaddch(win, this->__v_depth.v_y + 1, x, ACS_LTEE) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')", win, this->__v_depth.v_y + 1, x, ACS_LTEE);
	if (this->__f_draw_hline_branch(x + 1, this->__v_depth.v_y + 1) == false)
		return false;
	i = this->__v_depth.v_y + 2;
	size = nb_child + this->__v_depth.v_y;
	while (i < size)
	{
		if (i == pos_child_vect[0])
		{
			if (tools::f_my_mvwaddch(win, i, x, ACS_LTEE) == false)
				return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')", win, i, x, ACS_LTEE);
			pos_child_vect.erase(pos_child_vect.begin());
			if (this->__f_draw_hline_branch(x + 1, i) == false)
				return false;
		}
		else if (tools::f_my_mvwaddch(win, i, x, ACS_VLINE) == false)
			return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')", win, i, x, ACS_VLINE);
		
		++i;
	}

	if (tools::f_my_mvwaddch(win, size, x, ACS_LLCORNER) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')", win, size, x, ACS_LLCORNER);
	if (this->__f_draw_hline_branch(x + 1, size) == false)
		return false;
	return true;
}

c_function_calltree*	c_function_calltree::f_get_sub_function_by_index(unsigned int index)
{
	if (index >= this->__v_sub_function_vect.size())
		return NULL;
	return this->__v_sub_function_vect[index];
}

std::vector<c_function_calltree*>*	c_function_calltree::f_get_sub_function_vect(void)
{
	return &this->__v_sub_function_vect;
}

bool	c_function_calltree::f_open_function(void)
{
	int	nb_child;

	if (this->__v_open == true)
		return true;
	this->__v_open = true;
	this->__v_close_type = E_NOT_CLOSE;
	nb_child = this->__f_nb_child();
	this->__f_set_children_render_active(true);
	if (this->__v_open_close_button->f_init_title(D_OPEN_BUTTON) == false ||
	    this->__f_move_parent_under_children(nb_child) == false)
		return false;
	return true;
}

bool	c_function_calltree::f_close_function(void)
{
	int	nb_child;

	if (this->__v_open == false)
		return true;
	this->__v_open = false;
	nb_child = this->__f_nb_child();
	this->__v_close_type = E_CLOSE_BY_ME;
	this->__f_set_children_render_active(false);
	if (this->__v_open_close_button->f_init_title(D_CLOSED_BUTTON) == false ||
	    this->__f_move_parent_under_children(-nb_child) == false)
		return false;
	return true;
}

bool	c_function_calltree::f_switch_open_close(void)
{
	if (this->__v_open == true)
		return this->f_close_function();
	return this->f_open_function();
}

bool	c_function_calltree::f_display_popup_info(void)
{
	return this->__v_ncurses->f_get_ui()->f_get_popup_manager()->f_add_popup_info_function(this);
}

c_info_function*	c_function_calltree::f_get_info(void)
{
	return &this->__v_info_function;
}

c_function_calltree*	c_function_calltree::f_get_fct_by_multiple_index(const char* multiple_index)
{
	unsigned int	index;

	if (*multiple_index == 0)
		return this;
	index = multiple_index[0] - '0';
	if (index >= this->__v_sub_function_vect.size())
		return NULL;
	return this->__v_sub_function_vect[index]->f_get_fct_by_multiple_index(multiple_index + 1);
}

/* private function */

bool	c_function_calltree::__f_init_buttons(void)
{
	this->__v_open_close_button = new (std::nothrow) c_button(this->__v_ncurses, this->__v_event, this->__v_parent, E_OPEN_CLOSE_FUNCTION_BUTTON, (c_base_container*)(this));
	if (this->__v_open_close_button == NULL)
		return D_ERR_ALLOC;
	if (this->__v_parent->f_add_child(this->__v_open_close_button) == false)
	{
		tools::f_delete_ptr(this->__v_open_close_button);
		return false;
	}

	this->__v_function_button = new (std::nothrow) c_button(this->__v_ncurses, this->__v_event, this->__v_parent, E_FUNCTION_BUTTON, (c_base_container*)(this));
	if (this->__v_function_button == NULL)
		return D_ERR_ALLOC;
	if (this->__v_parent->f_add_child(this->__v_function_button) == false)
	{
		tools::f_delete_ptr(this->__v_function_button);
		return false;
	}

	if (this->__v_open_close_button->f_init(D_OPEN_BUTTON,
						this->__v_parent->f_get_info_size('x') + this->__v_depth.v_x,
						this->__v_parent->f_get_info_size('y') + this->__v_depth.v_y,
						tools::f_strlen(D_OPEN_BUTTON), 1) == false ||
	    this->__v_function_button->f_init(this->__v_info_function.v_name,
					      this->__v_parent->f_get_info_size('x') + this->__v_depth.v_x + D_OFFSET_BETWEEN_BUTTONS,
					      this->__v_parent->f_get_info_size('y') + this->__v_depth.v_y,
					      tools::f_strlen(this->__v_info_function.v_name), 1) == false)
		return false;
	return true;
}

bool	c_function_calltree::__f_move_parent_under_children(int y_decal)
{
	int				pos, size;
	std::vector<c_function_calltree*>*	sub_function_vect;

	if (this->__v_function_parent == NULL)
		return true;
	sub_function_vect = this->__v_function_parent->f_get_sub_function_vect();
	size = sub_function_vect->size();
	pos = this->__f_get_my_pos(sub_function_vect, size);
	if (pos == -1)
		return false;
	++pos;
	while (pos < size)
	{
		if ((*sub_function_vect)[pos]->__f_y_decal(y_decal) == false)
			return false;
		++pos;
	}
	return this->__v_function_parent->__f_move_parent_under_children(y_decal);
}

int	c_function_calltree::__f_get_my_pos(std::vector<c_function_calltree*>* sub_function_vect, int size)
{
	int	i;

	i = 0; 
	while (i < size)
	{
		if ((*sub_function_vect)[i] == this)
			break;
		++i;
	}
	if (i >= size)
		return -1;
	return i;
}

bool	c_function_calltree::__f_y_decal(int y_decal)
{
	int	i, size;

	this->__v_depth.v_y += y_decal;
	if (tools::f_my_mvwin(this->__v_open_close_button->f_get_window()->f_get_window(),
			      this->__v_open_close_button->f_get_info_size('y') + y_decal,
			      this->__v_open_close_button->f_get_info_size('x')) == false)
		return M_ERROR(false, "tools::f_my_mvwin(%p, %d, %d)", this->__v_open_close_button->f_get_window()->f_get_window(), this->__v_open_close_button->f_get_info_size('x'), this->__v_open_close_button->f_get_info_size('y') + y_decal);
	if (tools::f_my_mvwin(this->__v_function_button->f_get_window()->f_get_window(),
			      this->__v_function_button->f_get_info_size('y') + y_decal,
			      this->__v_function_button->f_get_info_size('x')) == false)
		return M_ERROR(false, "tools::f_my_mvwin(%p, %d, %d)", this->__v_function_button->f_get_window()->f_get_window(), this->__v_function_button->f_get_info_size('x'), this->__v_function_button->f_get_info_size('y') + y_decal);
	i = 0;
	size = this->__v_sub_function_vect.size();
	while (i < size)
	{
		this->__v_sub_function_vect[i]->__f_y_decal(y_decal);
		++i;
	}
	return true;
}

int	c_function_calltree::__f_nb_child(void)
{
	int	i, size, nb_child;

	i = 0;
	size = this->__v_sub_function_vect.size();
	nb_child = size;
	while (i < size)
	{
		if (this->__v_sub_function_vect[i]->__v_open == true)
			nb_child += this->__v_sub_function_vect[i]->__f_nb_child();
		++i;
	}
	return nb_child;
}

void	c_function_calltree::__f_set_children_render_active(bool value, bool grand_parent)
{
	int	i, size;

	if (grand_parent == true && this->__v_close_type == E_CLOSE_BY_ME)
		return ;
	i = 0;
	size = this->__v_sub_function_vect.size();
	while (i < size)
	{
		if (value == true)
		{
			this->__v_sub_function_vect[i]->__v_open_close_button->f_render_active_on();
			this->__v_sub_function_vect[i]->__v_function_button->f_render_active_on();
		}
		else
		{
			this->__v_sub_function_vect[i]->__v_open_close_button->f_render_active_off();
			this->__v_sub_function_vect[i]->__v_function_button->f_render_active_off();
		}
		this->__v_sub_function_vect[i]->__f_set_children_render_active(value, true);
		++i;
	}
}

bool	c_function_calltree::__f_fill_pos_child_vect(std::vector<int>* pos_child_vect)
{
	int	i, size;

	i = 1;
	size = this->__v_sub_function_vect.size() - 1;
	while (i < size)
	{
		if (tools::f_push_in_container(pos_child_vect, this->__v_sub_function_vect[i]->__v_depth.v_y, E_PUSH_BACK_INSERTION) == false)
			return false;
		++i;
	}
	return true;
}

bool	c_function_calltree::__f_draw_hline_branch(int x, int y)
{
	for (int j = 0; j < 2; ++j)
		if (tools::f_my_mvwaddch(this->__v_parent->f_get_window()->f_get_window(), y, x + j, ACS_HLINE) == false)
			return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')", this->__v_parent->f_get_window()->f_get_window(), y, x + j, ACS_HLINE);
	return true;
}
