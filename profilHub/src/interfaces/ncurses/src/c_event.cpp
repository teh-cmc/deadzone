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

#include <c_event.h>
#include <d_event.h>
#include <ncurses.h>
#include <c_ncurses.h>
#include <c_base_container.h>
#include <tools.h>
#include <c_ui.h>
#include <d_mouse.h>

/* constructer desctructer */

c_event::c_event(c_ncurses* ncurses, c_ui* ui) : __v_ui(ui),
						 __v_ncurses(ncurses)
{

}

c_event::~c_event(void)
{

}

/* public function */

bool	c_event::f_init(void)
{
	if (keypad(stdscr, TRUE) == ERR)
		return M_ERROR_NO_ARGS(false, "Error: keypad()\n");
	if (mousemask(D_LEFT_BUTTON_CLICKED, NULL) == 0)
		return M_ERROR_NO_ARGS(false, "Error: mousemask()\n");
	if (mouseinterval(-1) == ERR)
		return M_ERROR_NO_ARGS(false, "Error: mouseinterval(1)\n");
	return true;
}

bool	c_event::f_treat(void)
{
	int	key, ret;

	key = getch();
	if (key == ERR)
		return true;
	ret = this->__f_manage_special_key(key);
	if (ret == -1)
		return false;
	else if (ret == 1)
		return true;
	if (key == KEY_MOUSE)
		return this->__f_manage_mouse_event();
	if (this->__v_ui->f_get_popup_manager()->f_there_is_a_popup() == true)
		return this->__v_ui->f_get_popup_manager()->f_treat_keyboard(key);
	if (this->__v_ui->f_there_is_a_label_focus() == true)
		return __f_manage_label_focus(key);
	return __f_manage_focused_container(key);
}

bool	c_event::f_add_container_focused(c_base_container* container, e_insertion_child insertion)
{
	if (this->__f_erase_previous_run_time_focused_container() == false)
		return false;
	if (container->f_get_obj_type() == E_LABEL)
		this->__v_ui->f_set_current_label_focus((c_label*)(container));
	if (this->__v_ncurses->f_get_run() == true)
		container->f_set_focus_type(E_FOCUS_BY_RUN_TIME);
	else
		container->f_set_focus_type(E_FOCUS_BY_INIT);
	return tools::f_push_in_container(&this->__v_container_focused, container, insertion);
}

int	c_event::f_mouse_action(void)
{
	return this->__v_event.bstate;
}

int	c_event::f_mouse_x(void)
{
	return this->__v_event.x;
}

int	c_event::f_mouse_y(void)
{
	return this->__v_event.y;
}

int	c_event::f_mouse_event_ok(void)
{
	return getmouse(&this->__v_event);
}

bool	c_event::f_mouse_button_used(int button_state)
{
	return (this->__v_event.bstate & button_state);
}

/* private function */

int	c_event::__f_manage_special_key(int key)
{
	switch	(key)
	{
		case	KEY_RESIZE:
			if (this->__v_ui->f_get_popup_manager()->f_manage_resize() == false ||
			    this->__v_ncurses->f_get_ui()->f_manage_resize() == false)
				return -1;
			return 1;
	}
	return 0;
}

bool	c_event::__f_erase_previous_run_time_focused_container(void)
{
	int	i, size;

	i = 0;
	size = this->__v_container_focused.size();
	while (i < size)
	{
		if (this->__v_container_focused[i]->f_get_focus_type() == E_FOCUS_BY_RUN_TIME)
		{
			if (this->__v_container_focused[i]->f_get_obj_type() == E_LABEL)
				this->__v_ui->f_set_current_label_focus(NULL);
			if (this->__v_container_focused[i]->f_not_focus_anymore() == false)
				return false;
			this->__v_container_focused[i]->f_set_focus_type(E_NO_FOCUS);
			this->__v_container_focused.erase(this->__v_container_focused.begin() + i);
			size = this->__v_container_focused.size();
		}
		else
			++i;
	}
	return true;
}

bool	c_event::__f_manage_mouse_event(void)
{
	if (this->f_mouse_event_ok() == OK)
	{
		if (this->__v_ui->f_get_popup_manager()->f_there_is_a_popup() == true)
			return this->__v_ui->f_get_popup_manager()->f_treat_mouse();
		if (this->__v_ui->f_treat_mouse() == false)
			return false;
	}
	return true;
}

bool	c_event::__f_manage_label_focus(int key)
{
	if (this->__v_ui->f_send_keyboard_in_label(key) == -1)
		return false;
	return true;
}

bool	c_event::__f_manage_focused_container(int key)
{
	int		ret;
	unsigned int	i, size;

	i = 0;
	size = this->__v_container_focused.size();
	while (i < size)
	{
		if (this->__v_container_focused[i]->f_get_render_active() == true ||
		    this->__v_container_focused[i]->f_get_obj_type() == E_MENU)
		{
			ret = this->__v_container_focused[i]->f_treat_keyboard(key);
			if (ret == -1)
				return false;
			else if (ret == 1)
				return true;
		}
		++i;
	}
	return true;
}
