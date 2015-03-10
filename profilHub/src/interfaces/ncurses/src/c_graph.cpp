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

#include <c_graph.h>
#include <c_event.h>
#include <c_ncurses.h>
#include <e_obj_type.h>
#include <tools.h>
#include <d_color_ui.h>
#include <c_graphic.h>
#include <d_graph.h>
#include <c_label_numeric.h>
#include <d_label.h>
#include <d_event.h>
#include <callbacks_labels.h>
#include <d_children_indexes.h>
#include <e_button_type.h>
#include <callbacks_buttons.h>
#include <c_function_graphic.h>
#include <d_color_ui.h>
#include <math.h>
#include <c_label_alphanum.h>

/* constructer destructer */

c_graph::c_graph(c_ncurses* ncurses,
		 c_event* event,
		 c_base_container* parent) : c_base_container(E_GRAPH,
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

c_graph::~c_graph(void)
{

}

/* public function */

bool	c_graph::f_treat_render(void)
{
	if (this->__f_render_graph() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_graph::f_treat_keyboard(int key)
{
	(void)key;
	return true;
}

bool	c_graph::f_treat_mouse(void)
{
	return this->_f_send_mouse_event_to_child();
}

bool	c_graph::f_init_graph(void)
{
	if (this->f_init(NULL,
			 this->_v_parent->f_get_info_size('x') + 1,
			 this->_v_parent->f_get_info_size('y') + 1,
			 this->_v_parent->f_get_info_size('w') - 2,
			 this->_v_parent->f_get_info_size('h') - 2) == false ||
	    this->__f_init_my_child() == false ||
	    this->__f_fill_graphic_to_test() == false)
		return false;
	return true;
}

/* private function */

bool	c_graph::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_methode() == false)
		return false;
	return true;
}

bool	c_graph::__f_render_graph(void)
{
	if (this->__f_draw_graph() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_graph::__f_draw_graph(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_GRAPH)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_GRAPH));
	return true;
}

bool	c_graph::__f_init_event_methode(void)
{
	return true;
}

bool	c_graph::__f_init_my_child(void)
{
	if (this->__f_init_graphic() == false ||
	    this->__f_init_ordonnees_labels() == false ||
	    this->__f_init_abscisses_labels() == false ||
	    this->__f_init_graphic_interface() == false)
		return false;
	return true;
}

bool	c_graph::__f_init_graphic(void)
{
	c_graphic*	graphic;

	graphic = new (std::nothrow) c_graphic(this->_v_ncurses, this->_v_event, this);
	if (graphic == NULL)
		return D_ERR_ALLOC;
	if (this->f_add_child(graphic) == false)
	{
		delete graphic;
		return false;
	}
	if (graphic->f_init_definition_domaine(tools::f_atoi(D_X_MIN),
					       tools::f_atoi(D_X_MAX),
					       tools::f_atoi(D_Y_MIN),
					       tools::f_atoi(D_Y_MAX)) == false ||
	    graphic->f_init_display_precision(tools::f_atoi(D_X_PRECISION),
					      tools::f_atoi(D_Y_PRECISION)) == false ||
	    graphic->f_init(NULL,
			    this->f_get_info_size('x') + D_OFFSET_X_GRAPHIC,
			    this->f_get_info_size('y') + 1,
			    this->f_get_info_size('w') - D_OFFSET_X_GRAPHIC,
			    this->f_get_info_size('h') - D_OFFSET_Y_GRAPHIC - 1) == false)
		return false;
	return true;
}

bool	c_graph::__f_init_ordonnees_labels(void)
{
	if (this->__f_init_label(D_Y_MAX,
				 this->f_get_info_size('x'),
				 this->f_get_info_size('y') + 1,
				 D_OFFSET_X_GRAPHIC,
				 true,
				 true,
				 &y_max_graph_callback) == false ||
	    this->__f_init_label(D_Y_PRECISION,
				 this->f_get_info_size('x'),
				 this->f_get_info_size('h') >> 1,
				 D_OFFSET_X_GRAPHIC,
				 true,
				 false,
				 &y_precision_graph_callback) == false ||
	    this->__f_init_label(D_Y_MIN,
				 this->f_get_info_size('x'),
				 this->f_get_info_size('Y') - D_OFFSET_Y_GRAPHIC - 1,
				 D_OFFSET_X_GRAPHIC,
				 true,
				 true,
				 &y_min_graph_callback) == false)
		return false;
	return true;
}

bool	c_graph::__f_init_abscisses_labels(void)
{
	if (this->__f_init_label(D_X_MIN,
				 this->f_get_info_size('x') + D_OFFSET_X_GRAPHIC,
				 this->f_get_info_size('Y') - D_OFFSET_Y_GRAPHIC,
				 D_OFFSET_X_GRAPHIC,
				 true,
				 true,
				 &x_min_graph_callback) == false ||
	    this->__f_init_label(D_X_PRECISION,
				 this->f_get_info_size('w') >> 1,
				 this->f_get_info_size('Y') - D_OFFSET_Y_GRAPHIC,
				 D_OFFSET_X_GRAPHIC,
				 true,
				 false,
				 &x_precision_graph_callback) == false ||
	    this->__f_init_label(D_X_MAX,
				 this->f_get_info_size('w') - D_OFFSET_X_GRAPHIC + 2,
				 this->f_get_info_size('Y') - D_OFFSET_Y_GRAPHIC,
				 D_OFFSET_X_GRAPHIC,
				 true,
				 true,
				 &x_max_graph_callback) == false)
		return false;
	return true;
}

bool	c_graph::__f_init_graphic_interface(void)
{
	int	pos_x, len;

	pos_x = this->f_get_info_size('x') + D_OFFSET_X_GRAPHIC;
	len = tools::f_strlen(D_PREV_FUNCTION);
	if (this->__f_init_button(D_PREV_FUNCTION, pos_x, this->f_get_info_size('y'), len, 1, &prev_function_graphic, NULL) == false)
		return false;
	pos_x += len + 1;
	len = 5;
	if (this->__f_init_label(D_CURR_NBR_FUNCTION, pos_x, this->f_get_info_size('y'), len, true, true, &select_nbr_function_graphic) == false)
		return false;
	pos_x += len + 1;
	len = 30;
	if (this->__f_init_label(D_CURR_NAME_FUNCTION, pos_x, this->f_get_info_size('y'), len, false, false, &select_name_function_graphic) == false)
		return false;
	pos_x += len + 1;
	len = tools::f_strlen(D_NEXT_FUNCTION);
	if (this->__f_init_button(D_NEXT_FUNCTION, pos_x, this->f_get_info_size('y'), len, 1, &next_function_graphic, NULL) == false)
		return false;
	return true;
}

bool	c_graph::__f_init_label(const char* str, int x, int y, int width,
				bool numeric, bool negative_nbr,
				t_single_callback callback)
{
	c_label*	label;

	if (numeric == true)
		label = new (std::nothrow) c_label_numeric(this->_v_ncurses, this->_v_event, this);
	else
		label = new (std::nothrow) c_label_alphanum(this->_v_ncurses, this->_v_event, this);
	if (label == NULL)
		return D_ERR_ALLOC;
	if (this->f_add_child(label) == false)
	{
		delete label;
		return false;
	}
	if (label->f_add_single_callback(D_ENTER, callback) == false)
		return false;
	if (numeric == true)
	{
		if (((c_label_numeric*)(label))->f_init_label(str, D_LABEL_BUFFER_SIZE, x, y, width) == false)
			return false;
	}
	else if (((c_label_alphanum*)(label))->f_init_label(str, D_LABEL_BUFFER_SIZE, x, y, width) == false)
		return false;
	if (numeric == true)
		((c_label_numeric*)(label))->f_set_negative_nbr(negative_nbr);
	label->f_set_not_focus_anymore_callback(&not_focus_anymore_label_callback);
	return true;
}

bool	c_graph::__f_init_button(const char* str, int x, int y, int width, int height,
				 c_button::t_callback callback, c_base_container* obj_linked)
{
	c_button*	button;

	button = new (std::nothrow) c_button(this->_v_ncurses, this->_v_event, this, E_NORMALUS_BUTTON, obj_linked);
	if (button == NULL)
		return D_ERR_ALLOC;
	if (this->f_add_child(button) == false)
	{
		delete button;
		return false;
	}
	button->f_set_button_callback(callback);
	return button->f_init(str, x, y, width, height);
}

bool	c_graph::__f_fill_graphic_to_test(void)
{
	bool			midel = false;
	int			i, j, size;
	c_graphic*		graphic = (c_graphic*)(this->f_get_child_by_index(D_GRAPHIC_INDEX));
	c_function_graphic*	function_graphic;

	if (graphic->f_add_function_graphic("main", '.', D_COLOR_PAIR_FCT_GRAPH_1) == false)
		return false;
	function_graphic = graphic->f_get_function_graphic_by_index(0);
	for (i = 0, j = 0, size = 100; i < size; ++i)
	{
		if (function_graphic->f_add_point(i, j) == false)
			return false;
		if (midel == false)
			++j;
		else
			--j;
		if (midel == false && j >= (size >> 1))
			midel = true;
	}

	if (graphic->f_add_function_graphic("sinus", '.', D_COLOR_PAIR_FCT_GRAPH_2) == false)
		return false;
	function_graphic = graphic->f_get_function_graphic_by_index(1);
	for (i = -200, size = 200; i < size; ++i)
	{
		if (function_graphic->f_add_point(i, sinf((((float)(i)) * 2.0f * M_PI) / 40.0f) * 20.0f - 50.0f) == false)
			return false;
	}

	if (graphic->f_add_function_graphic("exp", '.', D_COLOR_PAIR_FCT_GRAPH_3) == false)
		return false;
	function_graphic = graphic->f_get_function_graphic_by_index(2);
	for (i = -200, size = 200; i < size; ++i)
	{
		if (function_graphic->f_add_point(i, expf(((float)(i)) / 40.0f) * 20.0f - 10.0f) == false)
			return false;
	}

	if (graphic->f_add_function_graphic("invers", '.', D_COLOR_PAIR_FCT_GRAPH_4) == false)
		return false;
	function_graphic = graphic->f_get_function_graphic_by_index(3);
	for (i = -200, size = 200; i < size; ++i)
	{
		if (function_graphic->f_add_point(i, (1 / (((float)(i)) / 20.0f)) * 20.0f) == false)
			return false;
	}
	return true;
}
