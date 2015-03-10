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

#include <c_ui.h>
#include <c_window.h>
#include <ncurses.h>
#include <tools.h>
#include <e_term.h>
#include <c_ncurses.h>
#include <d_color_ui.h>
#include <c_menu.h>
#include <c_label.h>
#include <d_term.h>
#include <d_children_indexes.h>

/* constructer destructer */

c_ui::c_ui(c_ncurses* ncurses) : __v_event(ncurses, this),
				 __v_ncurses(ncurses),
				 __v_data_ui(this->__v_ncurses, &this->__v_event),
				 __v_init_ui(this->__v_ncurses, &this->__v_event, &this->__v_data_ui)
{

}

c_ui::~c_ui(void)
{

}

/* public function */

bool	c_ui::f_init(void)
{
	if (this->__v_event.f_init() == false ||
	    this->__f_init_color() == false ||
	    this->__f_init_main_window() == false ||
	    this->__f_init_main_container() == false ||
	    this->__v_init_ui.f_init_interface() == false)
		return false;
	return true;
}

bool	c_ui::f_treat(void)
{
	if (this->__v_data_ui.v_main_container.f_treat_render() == false ||
	    this->__v_data_ui.v_popup_manager.f_treat_render() == false ||
	    this->__v_event.f_treat() == false)
		return false;
	return true;
}

bool	c_ui::f_manage_resize(void)
{
	float	rw, rh;

	this->f_set_ratio_resize(&rw, &rh);
	if (wclear(stdscr) == ERR ||
	    this->__v_data_ui.v_main_container.f_resize_by_ratio(rw, rh) == false ||
	    this->__v_data_ui.v_main_container.f_resize(getmaxx(stdscr), getmaxy(stdscr)) == false ||
	    this->__v_data_ui.v_main_container.f_magnetic_borders() == false)
		return false;
	return true;
}

void	c_ui::f_set_ratio_resize(float* rw, float* rh)
{
	*rw = (float)(getmaxx(stdscr)) / (float)(this->__v_data_ui.v_orig_window_pos_dim.v_dim.v_w);
	*rh = (float)(getmaxy(stdscr)) / (float)(this->__v_data_ui.v_orig_window_pos_dim.v_dim.v_h);
}

bool	c_ui::f_close(void)
{
	bool	err = false;

	if (err == true)
		return false;
	return true;
}

c_menu*	c_ui::f_get_menu_by_type(e_menu_type menu_type)
{
	int 				i, size;
	std::vector<c_base_container*>*	child_vect = this->__v_data_ui.v_main_container.f_get_child_vect();

	i = 0;
	size = child_vect->size();
	while (i < size)
	{
		if ((*child_vect)[i]->f_get_obj_type() == E_MENU &&
		    ((c_menu*)((*child_vect)[i]))->f_get_menu_type() == menu_type)
			return ((c_menu*)((*child_vect)[i]));
		++i;
	}
	return NULL;
}

void	c_ui::f_set_render_active_off_for_all_menus(void)
{
	int	i, size;
	std::vector<c_base_container*>*	child_vect = this->__v_data_ui.v_main_container.f_get_child_vect();

	i = 0;
	size = child_vect->size();
	while (i < size)
	{
		if ((*child_vect)[i]->f_get_obj_type() == E_MENU)
			(*child_vect)[i]->f_render_active_off();
		++i;
	}
}

c_popup_manager*	c_ui::f_get_popup_manager(void)
{
	return &this->__v_data_ui.v_popup_manager;
}

bool	c_ui::f_treat_mouse(void)
{
	return this->__v_data_ui.v_main_container.f_treat_mouse();
}

bool	c_ui::f_there_is_a_label_focus(void)
{
	return (this->__v_data_ui.v_current_label_focus != NULL);
}

void	c_ui::f_set_current_label_focus(c_label* label)
{
	this->__v_data_ui.v_current_label_focus = label;
}

int	c_ui::f_send_keyboard_in_label(int key)
{
	return this->__v_data_ui.v_current_label_focus->f_treat_keyboard(key);
}

bool	c_ui::f_init_first_container_focused(void)
{
	int	index_obj_tab[] = {1, 0, 0, -1};

	return this->__f_init_first_container_focused(&this->__v_data_ui.v_main_container, index_obj_tab, 0);
}

c_init_ui*	c_ui::f_get_init_ui(void)
{
	return &this->__v_init_ui;
}

c_event*	c_ui::f_get_event(void)
{
	return &this->__v_event;
}

bool	c_ui::f_clear_terminal(void)
{
	if (clear() == ERR)
		return M_ERROR_NO_ARGS(false, "Error: wclear()\n");
	if (refresh() == ERR)
		return M_ERROR_NO_ARGS(false, "Error: wclear()\n");
	return true;
}

c_data_ui*	c_ui::f_get_data_ui(void)
{
	return &this->__v_data_ui;
}

/* private function */

bool	c_ui::__f_init_first_container_focused(c_base_container* container, int* index_obj_tab, int reccursion)
{
	c_base_container*	child = container->f_get_child_by_index(index_obj_tab[reccursion]);

	if (child == NULL)
		return M_ERROR(false, "Error: child = NULL, width reccursion = %d\n", reccursion);
	++reccursion;
	if (index_obj_tab[reccursion] == -1)
		return this->__v_event.f_add_container_focused(child);
	return this->__f_init_first_container_focused(child, index_obj_tab, reccursion);
}

bool	c_ui::__f_init_color(void)
{
	if (can_change_color() == true)
	{
		if (this->__f_init_ui_color() == false)
			return false;
	}
	else
	{
		if (this->__v_ncurses->f_get_ui()->f_get_popup_manager()->f_add_popup_err_msg("Your terminal is in 8 color bits mode\n"
											      "  You can to have 256 color mode with this command\n"
											      "  export TERM=xterm-256color\n") == false ||
		    this->__f_init_ui_color() == false)
			return false;
	}
	return true;
}

bool	c_ui::__f_init_ui_color(void)
{
	if (this->__v_ncurses->f_get_env()->f_get_nb_color() == D_256_COLOR)
	{
		if (this->__f_set_256_color() == false)
			return false;
	}
	else if (this->__f_set_8_color() == false)
		return false;
	return true;
}

bool	c_ui::__f_set_256_color(void)
{
	if (init_pair(D_COLOR_PAIR_TOOLBAR,		COLOR_WHITE,	D_LIGHT_GREEN) == ERR ||
	    init_pair(D_COLOR_PAIR_MIDEL_ZONE,		COLOR_WHITE,	D_LIGHT_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_STATE_BAR,		COLOR_RED,	COLOR_YELLOW) == ERR ||
	    init_pair(D_COLOR_PAIR_MENU,		COLOR_WHITE,	D_LIGHT_GREEN) == ERR ||
	    init_pair(D_COLOR_PAIR_MENU_SELECTION, 	COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_POPUP,		COLOR_WHITE,	D_LIGHT_GREEN) == ERR ||
	    init_pair(D_COLOR_PAIR_LABEL,		COLOR_BLACK,	COLOR_WHITE) == ERR ||
	    init_pair(D_COLOR_PAIR_TAB,			COLOR_WHITE,	D_LIGHT_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_CALLTREE,		COLOR_WHITE,	D_LIGHT_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_FILTER_INDICATOR,	COLOR_WHITE,	D_LIGHT_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_FUNCTION_INDICATOR,	COLOR_WHITE,	D_LIGHT_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPH,		COLOR_WHITE,	D_LIGHT_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPHIC,		COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPHIC_AXES,	COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPHIC_SUB_AXES,	D_GREY,		COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_TEXT_ZONE,		COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_1,		COLOR_RED,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_2,		COLOR_GREEN,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_3,		COLOR_BLUE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_4,		COLOR_YELLOW,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_5,		COLOR_MAGENTA,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_6,		COLOR_CYAN,	COLOR_BLACK) == ERR)
		return M_ERROR_NO_ARGS(false, "Error: init_pair()\n");
	return true;
}

bool	c_ui::__f_set_8_color(void)
{
	if (init_pair(D_COLOR_PAIR_TOOLBAR,		COLOR_WHITE,	COLOR_GREEN) == ERR ||
	    init_pair(D_COLOR_PAIR_MIDEL_ZONE,		COLOR_WHITE,	COLOR_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_STATE_BAR,		COLOR_RED,	COLOR_YELLOW) == ERR ||
	    init_pair(D_COLOR_PAIR_MENU,		COLOR_WHITE,	COLOR_GREEN) == ERR ||
	    init_pair(D_COLOR_PAIR_MENU_SELECTION, 	COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_POPUP,		COLOR_WHITE,	COLOR_GREEN) == ERR ||
	    init_pair(D_COLOR_PAIR_LABEL,		COLOR_BLACK,	COLOR_WHITE) == ERR ||
	    init_pair(D_COLOR_PAIR_TAB,			COLOR_WHITE,	COLOR_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_CALLTREE,		COLOR_WHITE,	COLOR_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_FILTER_INDICATOR,	COLOR_WHITE,	COLOR_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_FUNCTION_INDICATOR,	COLOR_WHITE,	COLOR_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPH,		COLOR_WHITE,	COLOR_BLUE) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPHIC,		COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPHIC_AXES,	COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_GRAPHIC_SUB_AXES,	COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_TEXT_ZONE,		COLOR_WHITE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_1,		COLOR_RED,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_2,		COLOR_GREEN,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_3,		COLOR_BLUE,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_4,		COLOR_YELLOW,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_5,		COLOR_MAGENTA,	COLOR_BLACK) == ERR ||
	    init_pair(D_COLOR_PAIR_FCT_GRAPH_6,		COLOR_CYAN,	COLOR_BLACK) == ERR)
		return M_ERROR_NO_ARGS(false, "Error: init_pair()\n");
	return true;
}

bool	c_ui::__f_init_main_window(void)
{
	if (getmaxx(stdscr) == 0 || getmaxy(stdscr) == 0)
		return M_ERROR_NO_ARGS(false, "Error: bad size stdscr window\n");
	this->__v_data_ui.v_orig_window_pos_dim.f_set(0, 0, getbegx(stdscr) + getmaxx(stdscr), getbegy(stdscr) +  getmaxy(stdscr));
	return true;
}

bool	c_ui::__f_init_main_container(void)
{
	if (this->__v_data_ui.v_main_container.f_init(NULL, 0, 0, getmaxx(stdscr), getmaxy(stdscr)) == false ||
	    this->__v_event.f_add_container_focused(&this->__v_data_ui.v_main_container) == false)
		return false;
	return true;
}
