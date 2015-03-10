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

#include <ncurses.h>
#include <c_popup_manager.h>
#include <c_popup.h>
#include <stdlib.h>
#include <c_ncurses.h>
#include <c_event.h>
#include <tools.h>
#include <c_popup_err_msg.h>
#include <c_popup_read_dir_action.h>
#include <e_read_dir_action.h>
#include <c_base_container.h>
#include <c_function_calltree.h>
#include <c_popup_info_function.h>
#include <c_popup_text_zone.h>
#include <c_text_zone.h>

/* constrcter destructer */

c_popup_manager::c_popup_manager(c_ncurses* ncurses, c_event* event) : __v_ncurses(ncurses),
								       __v_event(event)
{

}

c_popup_manager::~c_popup_manager(void)
{
	tools::f_delete_ptr_container(this->__v_popup_vect);
	this->__v_popup_vect.clear();
}

/* public function */

bool	c_popup_manager::f_there_is_a_popup(void)
{
	return (this->__v_popup_vect.empty() == false);
}

bool	c_popup_manager::f_treat_keyboard(int key)
{
	int	ret;

	ret = this->__v_popup_vect[this->__v_popup_vect.size() - 1]->f_treat_keyboard(key);
	if (ret == -1)
		return false;
	else if (ret == 1)
		return true;
	return true;
}

bool	c_popup_manager::f_treat_mouse(void)
{
	int	ret;

	ret = this->__v_popup_vect[this->__v_popup_vect.size() - 1]->f_treat_mouse();
	if (ret == -1)
		return false;
	else if (ret == 1)
		return true;
	return true;
}

bool	c_popup_manager::f_treat_render(void)
{
	int	i, size;

	this->__f_erase_popups_finish();
	i = 0;
	size = this->__v_popup_vect.size();
	while (i < size)
	{
		if (this->__v_popup_vect[i]->f_treat_render() == false)
			return false;
		++i;
	}
	return true;
}

bool	c_popup_manager::f_add_popup_err_msg(const char* err_msg, ...)
{
	va_list			vargs;
	c_popup_err_msg*	popup_err_msg = (c_popup_err_msg*)(this->__f_factory_popup(E_POPUP_ERR_MSG));

	if (popup_err_msg == NULL)
		return M_ERROR_NO_ARGS(false, "Error: operator new\n");
	if (tools::f_push_in_container(&this->__v_popup_vect, (c_popup*)(popup_err_msg), E_PUSH_BACK_INSERTION) == false)
	{
		delete popup_err_msg;
		return M_ERROR(false, "Error: tools::f_push_in_container(%p, %p, %d)\n", &this->__v_popup_vect, (c_popup*)(popup_err_msg), E_PUSH_BACK_INSERTION);
	}
	va_start(vargs, err_msg);
	if (popup_err_msg->f_init_popup(this->__f_compute_size_popup('x'),
					this->__f_compute_size_popup('y'),
					this->__f_compute_size_popup('w'),
					this->__f_compute_size_popup('h'),
					err_msg, &vargs) == false)
	{
		va_end(vargs);
		return false;
	}
	va_end(vargs);
	return true;
}

template <typename T>
T	c_popup_manager::f_add_popup_err_msg(T ret, const char* err_msg, va_list* vargs)
{
	c_popup_err_msg*	popup_err_msg = (c_popup_err_msg*)(this->__f_factory_popup(E_POPUP_ERR_MSG));

	if (popup_err_msg == NULL)
		return M_ERROR_NO_ARGS(ret, "Error: operator new\n");
	if (tools::f_push_in_container(&this->__v_popup_vect, (c_popup*)(popup_err_msg), E_PUSH_BACK_INSERTION) == false)
	{
		delete popup_err_msg;
		return M_ERROR(ret, "Error: tools::f_push_in_container(%p, %p, %d)\n", &this->__v_popup_vect, (c_popup*)(popup_err_msg), E_PUSH_BACK_INSERTION);
	}
	if (popup_err_msg->f_init_popup(this->__f_compute_size_popup('x'),
					this->__f_compute_size_popup('y'),
					this->__f_compute_size_popup('w'),
					this->__f_compute_size_popup('h'),
					err_msg, vargs) == false)
		return ret;
	return true;
}

bool	c_popup_manager::f_add_popup_read_dir_action(e_read_dir_action action, const char* title, c_base_container* obj_linked)
{
	int				height;
	c_popup_read_dir_action*	popup_read_dir_action = (c_popup_read_dir_action*)(this->__f_factory_popup(E_POPUP_READ_DIR_ACTION));

	if (popup_read_dir_action == NULL)
		return M_ERROR_NO_ARGS(false, "Error: operator new\n");
	if (tools::f_push_in_container(&this->__v_popup_vect, (c_popup*)(popup_read_dir_action), E_PUSH_BACK_INSERTION) == false)
	{
		delete popup_read_dir_action;
		return M_ERROR(false, "Error: tools::f_push_in_container(%p, %p, %d)\n", &this->__v_popup_vect, (c_popup*)(popup_read_dir_action), E_PUSH_BACK_INSERTION);
	}
	popup_read_dir_action->f_set_obj_linked(obj_linked);
	height = this->__f_compute_size_popup('h');
	if (height < 10)
		height = 10;
	if (popup_read_dir_action->f_init_popup(action, title,
						this->__f_compute_size_popup('x'),
						this->__f_compute_size_popup('y'),
						this->__f_compute_size_popup('w'),
						height) == false)
		return false;
	return true;
}

bool	c_popup_manager::f_add_popup_info_function(c_function_calltree* function)
{
	int			height;
	c_popup_info_function*	popup_info_function = (c_popup_info_function*)(this->__f_factory_popup(E_POPUP_INFO_FUNCTION));

	if (popup_info_function == NULL)
		return M_ERROR_NO_ARGS(false, "Error: operator new\n");
	if (tools::f_push_in_container(&this->__v_popup_vect, (c_popup*)(popup_info_function), E_PUSH_BACK_INSERTION) == false)
	{
		delete popup_info_function;
		return M_ERROR(false, "Error: tools::f_push_in_container(%p, %p, %d)\n", &this->__v_popup_vect, (c_popup*)(popup_info_function), E_PUSH_BACK_INSERTION);
	}
	height = this->__f_compute_size_popup('h');
	if (height < 10)
		height = 10;
	if (popup_info_function->f_init_popup(function,
					      this->__f_compute_size_popup('x'),
					      this->__f_compute_size_popup('y'),
					      this->__f_compute_size_popup('w'),
					      height) == false)
		return false;
	return true;
}

bool	c_popup_manager::f_add_popup_text_zone(const char* text, const char* title)
{
	int			height;
	c_text_zone*		text_zone;
	c_popup_text_zone*	popup_text_zone;

	popup_text_zone = (c_popup_text_zone*)(this->__f_factory_popup(E_POPUP_TEXT_ZONE));
	if (popup_text_zone == NULL)
		return D_ERR_ALLOC;
	height = this->__f_compute_size_popup('h');
	if (height < 10)
		height = 10;
	text_zone = this->__f_init_text_zone(text, popup_text_zone,
					     this->__f_compute_size_popup('x') + 2,
					     this->__f_compute_size_popup('y') + 2,
					     this->__f_compute_size_popup('w') - 2,
					     height - 2);
	if (text_zone == NULL)
	{
		delete popup_text_zone;
		return false;
	}
	if (tools::f_push_in_container(&this->__v_popup_vect, (c_popup*)(popup_text_zone), E_PUSH_BACK_INSERTION) == false)
	{
		delete text_zone;
		delete popup_text_zone;
		return M_ERROR(false, "Error: tools::f_push_in_container(%p, %p, %d)\n", &this->__v_popup_vect, (c_popup*)(popup_text_zone), E_PUSH_BACK_INSERTION);
	}
	if (popup_text_zone->f_add_child(text_zone) == false)
	{
		delete text_zone;
		return false;
	}
	if (popup_text_zone->f_init_popup(text_zone, title,
					  this->__f_compute_size_popup('x'),
					  this->__f_compute_size_popup('y'),
					  this->__f_compute_size_popup('w'),
					  height) == false)
		return false;
	return true;
}

bool	c_popup_manager::f_manage_resize(void)
{
	float	rw, rh;
	int	i, size;

	i = 0;
	size = this->__v_popup_vect.size();
	this->__v_ncurses->f_get_ui()->f_set_ratio_resize(&rw, &rh);
	while (i < size)
	{
		if (this->__v_popup_vect[i]->f_resize_by_ratio(rw, rh) == false)
			return false;
		++i;
	}
	return true;
}

/* private function */

c_popup*	c_popup_manager::__f_factory_popup(e_popup_type popup_type)
{
	switch	(popup_type)
	{
		case	E_POPUP_ERR_MSG:
			return new (std::nothrow) c_popup_err_msg(this->__v_ncurses, this->__v_event, NULL, this);
		case	E_POPUP_READ_DIR_ACTION:
			return new (std::nothrow) c_popup_read_dir_action(this->__v_ncurses, this->__v_event, NULL, this);
		case	E_POPUP_INFO_FUNCTION:
			return new (std::nothrow) c_popup_info_function(this->__v_ncurses, this->__v_event, NULL, this);
		case	E_POPUP_TEXT_ZONE:
			return new (std::nothrow) c_popup_text_zone(this->__v_ncurses, this->__v_event, NULL, this);
	}
	return NULL;
}

void	c_popup_manager::__f_erase_popups_finish(void)
{
	int	i, size;

	i = 0;
	size = this->__v_popup_vect.size();
	while (i < size)
	{
		if (this->__v_popup_vect[i]->f_get_close() == true)
		{
			delete this->__v_popup_vect[i];
			this->__v_popup_vect.erase(this->__v_popup_vect.begin() + i);
			size = this->__v_popup_vect.size();
		}
		else
			++i;
	}
}

int	c_popup_manager::__f_compute_size_popup(char axe)
{
	switch (axe)
	{
		case	'x':	return getbegx(stdscr) + (getmaxx(stdscr) >> 2) + this->__f_decal_next_popup();
		case	'y':	return getbegy(stdscr) + (getmaxy(stdscr) >> 2) + this->__f_decal_next_popup();
		case	'w':	return getmaxx(stdscr) >> 1;
		case	'h':	return getmaxy(stdscr) >> 1;
	}
	return M_ERROR(0, "Error: axe = '%c'\n", axe);
}

int	c_popup_manager::__f_decal_next_popup(void)
{
	return this->__v_popup_vect.size();
}

c_text_zone*	c_popup_manager::__f_init_text_zone(const char* text, c_base_container* parent,
						    int x, int y, int w, int h)
{
	c_text_zone*	text_zone = new (std::nothrow) c_text_zone(this->__v_ncurses, this->__v_event, parent);

	if (text_zone == NULL)
		return M_ERROR_NO_ARGS((c_text_zone*)(NULL), "Error: operator new\n");
	if (text_zone->f_init(NULL, x, y, w, h) == false ||
	    text_zone->f_fill_text_by_alloc(text) == false)
	{
		delete text_zone;
		return (c_text_zone*)(NULL);
	}
	return text_zone;
}
