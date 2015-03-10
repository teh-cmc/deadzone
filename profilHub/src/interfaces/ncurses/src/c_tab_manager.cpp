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

#include <c_tab_manager.h>
#include <c_tab.h>
#include <d_color_ui.h>
#include <tools.h>
#include <e_insertion_child.h>
#include <c_button.h>
#include <c_event.h>

/* constructer destructer */

c_tab_manager::c_tab_manager(c_ncurses* ncurses, c_event* event, c_base_container* parent) : c_base_container(E_TAB_MANAGER,
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

c_tab_manager::~c_tab_manager(void)
{

}

/* public function */

bool	c_tab_manager::f_init(const char* title, int x, int y, int width, int height)
{
	if (this->_f_init_title(title) == false ||
	    this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_methode() == false)
		return false;
	return true;
}

bool	c_tab_manager::f_treat_render(void)
{
	if (this->__f_render_tab_manager() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_tab_manager::f_treat_keyboard(int key)
{
	(void)key;
	return true;
}

bool	c_tab_manager::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
		return this->_f_send_mouse_event_to_child();
	return true;
}

bool	c_tab_manager::f_add_tab(const char* tab_title, const char* button_title)
{
	c_tab*	tab = new (std::nothrow) c_tab(this->_v_ncurses, this->_v_event, this);

	if (tab == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_tab(%p, %p, %p)\n", this->_v_ncurses, this->_v_event, this);
	if (this->f_add_child(tab) == false)
	{
		delete tab;
		return false;
	}
	if (tab->f_init(tab_title, 1, 3, getmaxx(this->_v_window.f_get_window()) - 2, getmaxy(this->_v_window.f_get_window()) - 3) == false)
		return M_ERROR(false, "Error: tab->f_init(\"%s\", %d, %d, %d, %d)", tab_title, 1, 3, getmaxx(this->_v_window.f_get_window()) - 2, getmaxy(this->_v_window.f_get_window()) - 3);
	if (tab->f_init_button(button_title) == false)
		return M_ERROR(false, "Error: tab->f_init_button(\"%s\")\n", button_title);
	return true;
}

int	c_tab_manager::f_get_max_x_button(void)
{
	int	i, size, max;

	i = 0;
	max = 1;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_BUTTON)
			max += ((c_button*)(this->_v_container_child[i]))->f_get_width() + 1;
		++i;
	}
	return max;
}

void	c_tab_manager::f_disable_all_tabs(void)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
			this->_v_container_child[i]->f_render_active_off();
		++i;
	}
}

void	c_tab_manager::f_set_tab_active_by_index(int index)
{
	c_tab*	tab = this->__f_get_tab_by_index(index);

	if (tab == NULL)
		return ;
	this->f_disable_all_tabs();
	tab->f_render_active_on();
}

c_tab*	c_tab_manager::f_get_tab_by_index(unsigned int index)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB && index == 0)
			return (c_tab*)(this->_v_container_child[i]);
		--index;
		++i;
	}
	return NULL;
}

c_tab*	c_tab_manager::f_get_tab_after_this(c_tab* tab)
{
	int	i, size;

	if (this->__f_nb_tab() <= 1)
		return NULL;
	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB &&
		    this->_v_container_child[i] == tab)
		{
			++i;
			while (i < size)
			{
				if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
					return (c_tab*)(this->_v_container_child[i]);
				++i;
			}
			return this->__f_first_tab();
		}
		++i;
	}
	return NULL;
}

c_tab*	c_tab_manager::f_get_tab_before_this(c_tab* tab)
{
	int	i, size;

	if (this->__f_nb_tab() <= 1)
		return NULL;
	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB &&
		    this->_v_container_child[i] == tab)
		{
			--i;
			while (i >= 0)
			{
				if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
					return (c_tab*)(this->_v_container_child[i]);
				--i;
			}
			return this->__f_last_tab();
		}
		++i;
	}
	return NULL;
}

c_tab*	c_tab_manager::f_get_first_tab_actif(void)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB &&
		    this->_v_container_child[i]->f_get_render_active() == true)
			return (c_tab*)(this->_v_container_child[i]);
		++i;
	}
	return NULL;
}

/* private function */

bool	c_tab_manager::__f_render_tab_manager(void)
{
	if (this->__f_draw_tab_manager() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_tab_manager::__f_draw_tab_manager(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_MIDEL_ZONE)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_MIDEL_ZONE));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (this->_f_render_title() == false)
		return false;
	return true;
}

bool	c_tab_manager::__f_init_event_methode(void)
{
	return true;
}

int	c_tab_manager::__f_nb_tab(void)
{
	int	i, size, nb_tab;

	i = 0;
	nb_tab = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
			++nb_tab;
		++i;
	}
	return nb_tab;
}

c_tab*	c_tab_manager::__f_get_tab_by_index(int index)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
		{
			if (index == 0)
				return ((c_tab*)(this->_v_container_child[i]));
			--index;
		}
		++i;
	}
	return NULL;
}

c_tab*	c_tab_manager::__f_first_tab(void)
{
	int	i, size;

	i = 0;
	size = this->_v_container_child.size();
	while (i < size)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
			return (c_tab*)(this->_v_container_child[i]);
		++i;
	}
	return NULL;
}

c_tab*	c_tab_manager::__f_last_tab(void)
{
	int	i;

	i = this->_v_container_child.size() - 1;
	while (i >= 0)
	{
		if (this->_v_container_child[i]->f_get_obj_type() == E_TAB)
			return (c_tab*)(this->_v_container_child[i]);
		--i;
	}
	return NULL;
}
