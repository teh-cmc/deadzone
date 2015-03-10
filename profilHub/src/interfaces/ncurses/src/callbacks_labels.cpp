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

#include <callbacks_labels.h>
#include <c_label_alphanum.h>
#include <c_filter_indicator.h>
#include <d_children_indexes.h>
#include <d_indicator.h>
#include <e_obj_type.h>
#include <c_ncurses.h>
#include <tools.h>
#include <c_graphic.h>
#include <c_label_numeric.h>
#include <c_function_graphic.h>
#include <d_graph.h>
#include <c_indicator.h>
#include <c_function_indicator.h>
#include <c_function_calltree.h>

/* filter label callback */

bool	filter_label_enter_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	c_base_container*	filter_zone;
	c_filter_indicator*	filter_indicator;
	c_label_alphanum*	my_label = (c_label_alphanum*)(my_obj);

	filter_zone = my_label->f_get_parent()->f_get_parent()->f_get_child_by_index(D_FILTER_ZONE);
	if (filter_zone == NULL)
		return M_ERROR_NO_ARGS(false, "Error: filter_zone = NULL\n");
	if (filter_zone->f_get_obj_type() != E_ZONE)
		return M_ERROR_NO_ARGS(false, "Error: bad index\n");
	if (check_bad_content_in_current_children(filter_zone, my_label->f_get_content()) == true)
		return true;
	filter_indicator = new (std::nothrow) c_filter_indicator(ncurses, ncurses->f_get_ui()->f_get_event(), filter_zone);
	if (filter_indicator == NULL)
		return D_ERR_ALLOC;
	if (filter_zone->f_add_child(filter_indicator) == false)
	{
		delete filter_indicator;
		return false;
	}
	if (filter_indicator->f_init_indicator(my_label->f_get_content(),
					       filter_zone->f_get_info_size('x') + 1,
					       filter_zone->f_get_info_size('y') + 1 + (filter_zone->f_child_count() - 1) * D_FILTER_INDICATOR_HEIGHT,
					       filter_zone->f_get_info_size('w') - 2, D_FILTER_INDICATOR_HEIGHT) == false)
		return false;
	return my_label->f_clean_buffer();
}

bool	check_bad_content_in_current_children(c_base_container* filter_zone, const char* content)
{
	const char*			curr_filter;
	unsigned int			i, size, len;
	std::vector<c_base_container*>* child_vect = filter_zone->f_get_child_vect();

	i = 0;
	size = child_vect->size();
	len = tools::f_strlen(content);
	if (len == 0)
		return true;
	while (i < size)
	{
		if ((*child_vect)[i]->f_get_obj_type() == E_INDICATOR)
		{
			curr_filter = ((c_filter_indicator*)((*child_vect)[i]))->f_get_filter();
			if (len == tools::f_strlen(curr_filter) && tools::f_strncmp(content, curr_filter, len) == 0)
				return true;
		}
		++i;
	}
	return false;
}

/* graph label callbacks */

bool	y_min_graph_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			y_min;
	c_label_numeric*	my_label;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));

	(void)ncurses;
	if (graphic == NULL)
		return M_ERROR_NO_ARGS(false, "Error: graphic = NULL\n");
	my_label = (c_label_numeric*)(my_obj);
	if (tools::f_strlen(my_label->f_get_content()) == 0)
		return true;
	y_min = tools::f_atoi(my_label->f_get_content());
	if (y_min >= graphic->f_get_y_max())
		return true;
	graphic->f_set_y_min(y_min);
	graphic->f_init_graphic_data();
	return my_label->f_init_default_buffer(my_label->f_get_content());
}

bool	y_precision_graph_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			y_precision;
	c_label_numeric*	my_label;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));

	(void)ncurses;
	if (graphic == NULL)
		return M_ERROR_NO_ARGS(false, "Error: graphic = NULL\n");
	my_label = (c_label_numeric*)(my_obj);
	y_precision = tools::f_atoi(my_label->f_get_content());
	if (y_precision <= 0)
		return true;
	graphic->f_set_y_precision(y_precision);
	return my_label->f_init_default_buffer(my_label->f_get_content());
}

bool	y_max_graph_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			y_max;
	c_label_numeric*	my_label;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));

	(void)ncurses;
	if (graphic == NULL)
		return M_ERROR_NO_ARGS(false, "Error: graphic = NULL\n");
	my_label = (c_label_numeric*)(my_obj);
	if (tools::f_strlen(my_label->f_get_content()) == 0)
		return true;
	y_max = tools::f_atoi(my_label->f_get_content());
	if (y_max <= graphic->f_get_y_min())
		return true;
	graphic->f_set_y_max(y_max);
	graphic->f_init_graphic_data();
	return my_label->f_init_default_buffer(my_label->f_get_content());
}

bool	x_min_graph_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			x_min;
	c_label_numeric*	my_label;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));

	(void)ncurses;
	if (graphic == NULL)
		return M_ERROR_NO_ARGS(false, "Error: graphic = NULL\n");
	my_label = (c_label_numeric*)(my_obj);
	if (tools::f_strlen(my_label->f_get_content()) == 0)
		return true;
	x_min = tools::f_atoi(my_label->f_get_content());
	if (x_min >= graphic->f_get_x_max())
		return true;
	graphic->f_set_x_min(x_min);
	graphic->f_init_graphic_data();
	return my_label->f_init_default_buffer(my_label->f_get_content());
}

bool	x_precision_graph_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			x_precision;
	c_label_numeric*	my_label;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));

	(void)ncurses;
	if (graphic == NULL)
		return M_ERROR_NO_ARGS(false, "Error: graphic = NULL\n");
	my_label = (c_label_numeric*)(my_obj);
	x_precision = tools::f_atoi(my_label->f_get_content());
	if (x_precision <= 0)
		return true;
	graphic->f_set_x_precision(x_precision);
	return my_label->f_init_default_buffer(my_label->f_get_content());
}

bool	x_max_graph_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			x_max;
	c_label_numeric*	my_label;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));

	(void)ncurses;
	if (graphic == NULL)
		return M_ERROR_NO_ARGS(false, "Error: graphic = NULL\n");
	my_label = (c_label_numeric*)(my_obj);
	if (tools::f_strlen(my_label->f_get_content()) == 0)
		return true;
	x_max = tools::f_atoi(my_label->f_get_content());
	if (x_max <= graphic->f_get_x_min())
		return true;
	graphic->f_set_x_max(x_max);
	graphic->f_init_graphic_data();
	return my_label->f_init_default_buffer(my_label->f_get_content());
}

bool	not_focus_anymore_label_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	c_label*	my_label = (c_label*)(my_obj);

	(void)ncurses;
	if (my_label->f_clean_buffer() == false)
		return false;
	my_label->f_push_default_buffer_in_buffer();
	return true;
}

bool	select_nbr_function_graphic(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			nbr;
	c_label_numeric*	my_label = (c_label_numeric*)(my_obj);
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));
	c_label_alphanum*	name_fct;

	(void)ncurses;
	if (tools::f_strlen(my_label->f_get_content()) == 0)
		return true;
	nbr = tools::f_atoi(my_label->f_get_content());
	if (nbr < -1 || nbr >= graphic->f_function_graphic_count())
		return true;
	if (my_label->f_init_default_buffer(my_label->f_get_content()) == false)
		return false;
	my_label->f_push_default_buffer_in_buffer();
	name_fct = (c_label_alphanum*)(my_label->f_get_parent()->f_get_child_by_index(D_NAME_FUNCTION_LABEL_INDEX));
	if (nbr == -1)
	{
		if (name_fct->f_init_default_buffer(D_CURR_NAME_FUNCTION) == false)
			return false;
	}
	else if (name_fct->f_init_default_buffer(graphic->f_get_function_graphic_by_index(nbr)->f_get_name()) == false)
		return false;
	if (name_fct->f_clean_buffer() == false)
		return false;
	name_fct->f_push_default_buffer_in_buffer();
	return true;
}

bool	select_name_function_graphic(c_ncurses* ncurses, c_base_container* my_obj)
{
	int			index;
	const char*		str;
	c_graphic*		graphic = (c_graphic*)(my_obj->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));
	c_label_alphanum*	my_label = (c_label_alphanum*)(my_obj);
	c_label_numeric*	nbr_fct;

	(void)ncurses;
	str = my_label->f_get_content();
	if (graphic->f_find_name_function(str) == false)
		return true;
	index = graphic->f_get_index_by_name_function(str);
	if (index == -1)
		return true;
	if (my_label->f_init_default_buffer(str) == false)
		return false;
	my_label->f_push_default_buffer_in_buffer();
	nbr_fct = (c_label_numeric*)(my_obj->f_get_parent()->f_get_child_by_index(D_NBR_FUNCTION_LABEL_INDEX));
	str = tools::f_itoa(index);
	if (str == NULL)
		return M_ERROR(false, "Error: tools::f_itoa(%d)\n", index);
	if (nbr_fct->f_clean_buffer() == false ||
	    nbr_fct->f_init_default_buffer(str) == false)
	{
		delete [] str;
		return false;
	}
	delete [] str;
	nbr_fct->f_push_default_buffer_in_buffer();
	return true;
}

/* search module callback */

bool	search_module_real_time_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	const char*				str;
	c_base_container*			error_zone;
	std::vector<c_function_indicator*>	fct_indict_vect;

	(void)ncurses;
	str = ((c_label_numeric*)(my_obj))->f_get_content();
	error_zone = my_obj->f_get_parent()->f_get_parent()->f_get_child_by_index(D_ERROR_ZONE);
	if (str == NULL)
		return true;
	if (tools::f_strlen(str) == 0)
	{
		error_zone->f_set_render_active_all_child(true);
		return replace_error_zone_children_by_render_active_on(error_zone->f_get_child_vect());
	}
	if (find_fct_indict_match_str(error_zone, &fct_indict_vect, str) == false)
		return false;
	if (update_error_zone(error_zone, &fct_indict_vect) == false)
	{
		fct_indict_vect.clear();
		return false;
	}
	fct_indict_vect.clear();
	return true;
}

bool	find_fct_indict_match_str(c_base_container* error_zone, std::vector<c_function_indicator*>* fct_indict_vect, const char* str)
{
	unsigned int			len;
	int				i, size;
	const char*			fct_name;
	c_base_container*		curr_child;
	std::vector<c_base_container*>*	child_vect = error_zone->f_get_child_vect();

	i = 0;
	size = child_vect->size();
	len = tools::f_strlen(str);
	while (i < size)
	{
		curr_child = (*child_vect)[i];
		if (curr_child->f_get_obj_type() == E_INDICATOR &&
		    ((c_indicator*)(curr_child))->f_get_indicator_type() == E_FUNCTION_INDICATOR)
		{
			fct_name = ((c_function_indicator*)(curr_child))->f_get_fct()->f_get_info()->v_name;
			if (tools::f_strlen(fct_name) >= len &&
			    strstr(fct_name, str) != NULL &&
			    tools::f_push_in_container(fct_indict_vect, ((c_function_indicator*)(curr_child)), E_PUSH_BACK_INSERTION) == false)
				return false;
		}
		++i;
	}
	return true;
}

bool	update_error_zone(c_base_container* error_zone, std::vector<c_function_indicator*>* fct_indict_vect)
{
	int				i, size;
	std::vector<c_base_container*>*	child_vect = error_zone->f_get_child_vect();

	i = 0;
	size = child_vect->size();
	while (i < size)
	{
		if (fct_indict_vect->size() > 0 && (*child_vect)[i] == (*fct_indict_vect)[0])
		{
			fct_indict_vect->erase(fct_indict_vect->begin());
			(*child_vect)[i]->f_render_active_on();
		}
		else
			(*child_vect)[i]->f_render_active_off();
		++i;
	}
	return replace_error_zone_children_by_render_active_on(child_vect);
}

bool	replace_error_zone_children_by_render_active_on(std::vector<c_base_container*>* child_vect)
{
	int			i, j, good_y, size;
	c_base_container*	curr_child;

	i = 0;
	j = 0;
	size = child_vect->size();
	while (i < size)
	{
		curr_child = (*child_vect)[i];
		if (curr_child->f_get_render_active() == true)
		{
			good_y = curr_child->f_get_parent()->f_get_info_size('y') + 1 + j * D_FILTER_INDICATOR_HEIGHT;
			if (curr_child->f_get_info_size('y') != good_y &&
			    tools::f_my_mvwin(curr_child->f_get_window()->f_get_window(),
					      good_y,
					      curr_child->f_get_info_size('x')) == false)
				return false;
			++j;
		}
		++i;
	}
	return true;
}
