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

#include <c_graphic.h>
#include <e_obj_type.h>
#include <d_color_ui.h>
#include <tools.h>
#include <d_graph.h>
#include <c_function_graphic.h>
#include <d_children_indexes.h>
#include <c_label_numeric.h>

/* constructer destructer */

c_graphic::c_graphic(c_ncurses* ncurses,
		     c_event* event,
		     c_base_container* parent) : c_base_container(E_GRAPHIC,
								  ncurses,
								  event,
								  parent,
								  false,
								  false,
								  false,
								  true),
								  __v_init(0),
								  __v_width_ratio(1),
								  __v_height_ratio(1)
{
	this->_v_window.f_get_magnetic_border()->f_set(false, false, false, false);
}

c_graphic::~c_graphic(void)
{
	tools::f_delete_ptr_container(this->__v_function_graphic_vect);
	this->__v_function_graphic_vect.clear();
}

/* public function */

bool	c_graphic::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if ((this->__v_init % 10) != 1)
		return M_ERROR_NO_ARGS(false, "Error: in the c_graph class, you have forget to call f_init_definition_domaine()\n");
	if ((this->__v_init % 100 / 10) != 1)
		return M_ERROR_NO_ARGS(false, "Error: in the c_graph class, you have forget to call f_init_display_precision()\n");
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_methode() == false)
		return false;
	this->f_init_graphic_data();
	return true;
}

bool	c_graphic::f_treat_render(void)
{
	if (this->__f_draw_graphic() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

int	c_graphic::f_treat_keyboard(int key)
{
	(void)key;
	return true;
}

bool	c_graphic::f_treat_mouse(void)
{
	return true;
}

bool	c_graphic::f_init_definition_domaine(int x_min, int x_max, int y_min, int y_max)
{
	if (this->__f_check_definition_domaine(x_min, x_max, y_min, y_max) == false)
		return false;
	this->__v_x_min = x_min;
	this->__v_x_max = x_max;
	this->__v_y_min = y_min;
	this->__v_y_max = y_max;
	this->__v_init += 1;
	return true;
}

bool	c_graphic::f_init_display_precision(int x_precision, int y_precision)
{
	this->__v_x_precision = x_precision;
	this->__v_y_precision = y_precision;
	this->__v_init += 10;
	return true;
}

void	c_graphic::f_init_graphic_data(void)
{
	this->__v_width_ratio = ((float)(this->__v_x_max - this->__v_x_min)) / ((float)(this->f_get_info_size('w')));
	this->__v_height_ratio = ((float)(this->__v_y_max - this->__v_y_min)) / ((float)(this->f_get_info_size('h')));
}

void	c_graphic::f_set_x_min(int x_min)
{
	this->__v_x_min = x_min;
}

int	c_graphic::f_get_x_min(void)
{
	return this->__v_x_min;
}

void	c_graphic::f_set_x_max(int x_max)
{
	this->__v_x_max = x_max;
}

int	c_graphic::f_get_x_max(void)
{
	return this->__v_x_max;
}

void	c_graphic::f_set_y_min(int y_min)
{
	this->__v_y_min = y_min;
}

int	c_graphic::f_get_y_min(void)
{
	return this->__v_y_min;
}

void	c_graphic::f_set_y_max(int y_max)
{
	this->__v_y_max = y_max;
}

int	c_graphic::f_get_y_max(void)
{
	return this->__v_y_max;
}

void	c_graphic::f_set_x_precision(int x_precision)
{
	this->__v_x_precision = x_precision;
}

void	c_graphic::f_set_y_precision(int y_precision)
{
	this->__v_y_precision = y_precision;
}

bool	c_graphic::f_add_function_graphic(const char* name, char motif, int color_pair)
{
	c_function_graphic*	function_graphic;

	function_graphic = new (std::nothrow) c_function_graphic(this, motif, color_pair);
	if (function_graphic == NULL)
		return D_ERR_ALLOC;
	if (tools::f_push_in_container(&this->__v_function_graphic_vect, function_graphic, E_PUSH_BACK_INSERTION) == false)
	{
		delete function_graphic;
		return false;
	}
	return function_graphic->f_init(name);
}

int	c_graphic::f_function_graphic_count(void)
{
	return this->__v_function_graphic_vect.size();
}

c_function_graphic*	c_graphic::f_get_function_graphic_by_index(unsigned int index)
{
	if (index >= this->__v_function_graphic_vect.size())
		return NULL;
	return this->__v_function_graphic_vect[index];
}

bool	c_graphic::f_find_name_function(const char* name)
{
	int	i, size, len;

	if (name == NULL)
		return false;
	i = 0;
	len = tools::f_strlen(name);
	size = this->__v_function_graphic_vect.size();
	while (i < size)
	{
		if (tools::f_strncmp(this->__v_function_graphic_vect[i]->f_get_name(), name, len) == 0)
			return true;
		++i;
	}
	return false;
}

int	c_graphic::f_get_index_by_name_function(const char* name)
{
	int	i, size, len;

	i = 0;
	len = tools::f_strlen(name);
	size = this->__v_function_graphic_vect.size();
	while (i < size)
	{
		if (tools::f_strncmp(this->__v_function_graphic_vect[i]->f_get_name(), name, len) == 0)
			return i;
		++i;
	}
	return -1;
}

/* private function */

bool	c_graphic::__f_check_definition_domaine(int x_min, int x_max, int y_min, int y_max)
{
	bool	err = false;

	if (x_min >= x_max)
	{
		err = true;
		M_ERROR_VOID("Error: x_min = %d must be < to x_max = %d\n", x_min, x_max);
	}
	if (y_min >= y_max)
	{
		if (err == true)
			tools::f_debug_file("\n");
		else
			err = true;
		M_ERROR_VOID("Error: x_min = %d must be < to x_max = %d\n", x_min, x_max);
	}
	if (err == true)
		return false;
	return true;
}

bool	c_graphic::__f_init_event_methode(void)
{
	return true;
}

bool	c_graphic::__f_draw_graphic(void)
{
	if (this->_v_window.f_clean() == false)
		return false;
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_GRAPHIC)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_GRAPHIC));
	if (this->__f_draw_main_axes(D_X_DECAL_REPER, D_Y_DECAL_REPER) == false ||
	    this->__f_draw_precision_axes() == false ||
	    this->__f_draw_function_graphic() == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_main_axes(int x_decal, int y_decal)
{
	if (this->__f_draw_abscisses_axes(x_decal) == false ||
	    this->__f_draw_ordonnees_axes(y_decal) == false ||
	    this->__f_draw_cross_axes() == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_abscisses_axes(int decal)
{
	if (this->__v_y_min >= 0)
	{
		if (this->__f_draw_abscisses(this->f_get_info_size('h') - decal) == false)
			return false;
	}
	else if (this->__v_y_max <= 0)
	{
		if (this->__f_draw_abscisses(1) == false)
			return false;
	}
	else if (this->__f_draw_abscisses(this->f_get_info_size('h') - ((-1 * this->__v_y_min) * this->f_get_info_size('h') / (this->__v_y_max - this->__v_y_min))) == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_ordonnees_axes(int decal)
{
	if (this->__v_x_min >= 0)
	{
		if (this->__f_draw_ordonnees(1) == false)
			return false;
	}
	else if (this->__v_x_max <= 0)
	{
		if (this->__f_draw_ordonnees(this->f_get_info_size('w') - decal) == false)
			return false;
	}
	else if (this->__f_draw_ordonnees((-1 * this->__v_x_min) * this->f_get_info_size('w') / (this->__v_x_max - this->__v_x_min)) == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_abscisses(int pos)
{
	int	i, size;

	this->__v_pos_abscisse = pos;
	i = 0;
	size = this->f_get_info_size('w');
	while (i < size)
	{
		if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), pos, i, ACS_HLINE) == false)
			return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), pos, i, ACS_HLINE);
		++i;
	}
	return true;
}

bool	c_graphic::__f_draw_ordonnees(int pos)
{
	int	i;

	this->__v_pos_ordonnee = pos;
	i = this->f_get_info_size('h') - 1;
	while (i >= 0)
	{
		if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), i, pos, ACS_VLINE) == false)
			return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), i, pos, ACS_VLINE);
		--i;
	}
	return true;
}

bool	c_graphic::__f_draw_cross_axes(void)
{
	if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), this->__v_pos_abscisse, this->__v_pos_ordonnee, ACS_PLUS) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), this->__v_pos_abscisse, this->__v_pos_ordonnee, ACS_PLUS);
	return true;
}

bool	c_graphic::__f_draw_precision_axes(void)
{
	if (this->__f_draw_precision_on_main_axes() == false ||
	    this->__f_draw_sub_axes() == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_precision_on_main_axes(void)
{
	if (this->__f_draw_precision_abscisses() == false ||
	    this->__f_draw_precision_ordonnees() == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_precision_abscisses(void)
{
	int	i, size;
	float	j, next_precision;

	j = 0.0f;
	i = this->__v_pos_ordonnee;
	size = this->f_get_info_size('w');
	next_precision = (float)(this->__v_x_precision);
	while (i < size)
	{
		if (j >= next_precision)
		{
			if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), this->__v_pos_abscisse, i, ACS_PLUS) == false)
				return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), this->__v_pos_abscisse, i, ACS_PLUS);
			next_precision += this->__v_x_precision;
		}
		++i;
		j += this->__v_width_ratio;
	}
	j = 0.0f;
	i = this->__v_pos_ordonnee;
	next_precision = (float)(this->__v_x_precision);
	while (i >= 0)
	{
		if (j >= next_precision)
		{
			if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), this->__v_pos_abscisse, i, ACS_PLUS) == false)
				return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), this->__v_pos_abscisse, i, ACS_PLUS);
			next_precision += this->__v_x_precision;
		}
		--i;
		j += this->__v_width_ratio;
	}
	return true;
}

bool	c_graphic::__f_draw_precision_ordonnees(void)
{
	int	i, size;
	float	j, next_precision;

	j = 0.0f;
	i = this->__v_pos_abscisse;
	size = this->f_get_info_size('h');
	next_precision = (float)(this->__v_y_precision);
	while (i < size)
	{
		if (j >= next_precision)
		{
			if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), i, this->__v_pos_ordonnee, ACS_PLUS) == false)
				return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), i, this->__v_pos_ordonnee, ACS_PLUS);
			next_precision += this->__v_y_precision;
		}
		++i;
		j += this->__v_height_ratio;
	}
	j = 0.0f;
	i = this->__v_pos_abscisse;
	next_precision = (float)(this->__v_y_precision);
	while (i >= 0)
	{
		if (j >= next_precision)
		{
			if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), i, this->__v_pos_ordonnee, ACS_PLUS) == false)
				return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), i, this->__v_pos_ordonnee, ACS_PLUS);
			next_precision += this->__v_y_precision;
		}
		--i;
		j += this->__v_height_ratio;
	}
	return true;
}

bool	c_graphic::__f_draw_sub_axes(void)
{
	return true;
}

bool	c_graphic::__f_draw_function_graphic(void)
{
	int	nbr = tools::f_atoi(((c_label_numeric*)(this->_v_parent->f_get_child_by_index(D_NBR_FUNCTION_LABEL_INDEX)))->f_get_default_buffer());

	if (nbr <= -1)
	{
		if (this->__f_draw_all_functions() == false)
			return false;
	}
	else if (nbr < ((int)(this->__v_function_graphic_vect.size())) &&
		 this->__f_draw_one_function(this->__v_function_graphic_vect[nbr]) == false)
		return false;
	return true;
}

bool	c_graphic::__f_draw_all_functions(void)
{
	int	i, size;

	i = 0;
	size = this->__v_function_graphic_vect.size();
	while (i < size)
	{
		if (this->__f_draw_one_function(this->__v_function_graphic_vect[i]) == false)
			return false;
		++i;
	}
	return true;
}

bool	c_graphic::__f_draw_one_function(c_function_graphic* function_graphic)
{
	int						i, size;
	c_function_graphic::t_pair*			pair;
	std::vector<c_function_graphic::t_pair>*	point_vect = function_graphic->f_get_point_vect();

	i = 0;
	size = point_vect->size();
	while (i < size)
	{
		pair = &((*point_vect)[i]);
		if (pair->v_x >= this->__v_x_min && pair->v_x < this->__v_x_max &&
		    pair->v_y >= this->__v_y_min && pair->v_y < this->__v_y_max)
		{
			if (this->__f_draw_point(pair->v_x / this->__v_width_ratio,
						 pair->v_y / this->__v_height_ratio,
						 function_graphic->f_get_motif(),
						 function_graphic->f_get_color_pair()) == false)
				return false;
		}
		++i;
	}
	return true;
}

bool	c_graphic::__f_draw_point(int x, int y, char motif, int color_pair)
{
	if (wattron(this->_v_window.f_get_window(), COLOR_PAIR(color_pair)) == ERR)
		return M_ERROR(false, "Error: attron(COLOR_PAIR(%d)\n", color_pair);
	if (tools::f_my_mvwaddch(this->_v_window.f_get_window(),
				 (this->__v_pos_abscisse + y) - (2 * y),
				 this->__v_pos_ordonnee + x,
				 motif) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddch(%p, %d, %d, '%c')\n",
			       this->_v_window.f_get_window(),
			       (this->__v_pos_abscisse + y) - (2 * y),
			       this->__v_pos_ordonnee + x,
			       motif);
	if (wattroff(this->_v_window.f_get_window(), COLOR_PAIR(color_pair)) == ERR)
		return M_ERROR(false, "Error: attroff(COLOR_PAIR(%d)\n", color_pair);
	return true;
}
