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

#include <c_menu_button.h>
#include <e_menu_type.h>
#include <c_ui.h>
#include <tools.h>
#include <c_button.h>
#include <c_ncurses.h>
#include <c_label_alphanum.h>
#include <launcher.h>
#include <d_children_indexes.h>
#include <c_menu_scroll.h>
#include <profilers.h>
#include <c_filter_indicator.h>
#include <d_indicator.h>
#include <c_graphic.h>
#include <c_label_numeric.h>
#include <d_children_indexes.h>
#include <c_function_graphic.h>
#include <d_graph.h>

/* callbacks buttons toolbar */

bool	file_toolbar_button_callback(c_ncurses* ncurses, c_button* button)
{
	(void)button;
	return c_menu_button::sf_treat_menu_from_button_callback(ncurses->f_get_ui(), E_FILE_MENU);
}

bool	tools_toolbar_button_callback(c_ncurses* ncurses, c_button* button)
{
	(void)button;
	return c_menu_button::sf_treat_menu_from_button_callback(ncurses->f_get_ui(), E_TOOLS_MENU);
}

bool	help_toolbar_button_callback(c_ncurses* ncurses, c_button* button)
{
	(void)button;
	return c_menu_button::sf_treat_menu_from_button_callback(ncurses->f_get_ui(), E_HELP_MENU);
}

/* callbacks buttons choice executable tab */

bool	browse_executable_button_callback(c_ncurses* ncurses, c_button* button)
{
	c_base_container*	label = button->f_get_parent()->f_get_child_by_index(D_EXECUTABLE_PATH_LABEL_INDEX);

	return ncurses->f_get_ui()->f_get_popup_manager()->f_add_popup_read_dir_action(E_READ_DIR_ACTION_BROWSE_EXECUTABLE, "Browse executable:      press 'h' to see hidden files", label);
}

bool	launch_executable_button_callback(c_ncurses* ncurses, c_button* button)
{
	c_label_alphanum*	path_executable = NULL;
	c_label_alphanum*	arguments_executable = NULL;
	c_menu_scroll*		sub_option_menu = NULL;
	char*			prog_args;

	path_executable = (c_label_alphanum*)(button->f_get_parent()->f_get_child_by_index(D_EXECUTABLE_PATH_LABEL_INDEX));
	if (path_executable->f_get_content() == NULL)
		return false;
	arguments_executable = (c_label_alphanum*)(button->f_get_parent()->f_get_child_by_index(D_EXECUTABLE_ARGUMENTS_LABEL_INDEX));
	sub_option_menu = (c_menu_scroll*)(button->f_get_parent()->f_get_child_by_index(D_CHOICE_SUB_OPTIONS_MENU_INDEX));
	if (sub_option_menu->f_get_first_item_selected_index() == -1)
		return false;
	if (fill_prog_args(&prog_args, path_executable, arguments_executable) == false)
	{
		delete [] prog_args;
		return false;
	}
	if (launch_analyze(prog_args, sub_option_menu) == false)
	{
		delete [] prog_args;
		return false;
	}
	delete [] prog_args;
	if (ncurses->f_get_ui()->f_get_init_ui()->f_init_secondary_item() == false ||
	    ncurses->f_get_ui()->f_clear_terminal() == false)
		return false;
	return true;
}

bool	launch_analyze(char* prog_args, c_menu_scroll* sub_option_menu)
{
	unsigned int	i, size, len;
	const char*	item_name;

	M_LAUNCHER(l, prog_args);
	i = 0;
	size = sub_option_menu->f_item_count();
	while (i < size)
	{
		if (sub_option_menu->f_get_item_value_by_index(i) == true)
		{
			item_name = sub_option_menu->f_item_name_by_index(i);
			len = tools::f_strlen(item_name);
			if (len == tools::f_strlen(D_VALGRIND_MEMCHECK) && tools::f_strncmp(item_name, D_VALGRIND_MEMCHECK, len) == 0)
				if (!launcher_add_task(&l, E_VALGRIND_MEMCHECK, NULL))
					return M_ERROR_NO_ARGS(false, "Error: could not create task\n");
		}
		++i;
	}
	if (!launcher_launch(&l))
		return M_ERROR_NO_ARGS(false, "Error: could not execute tasks\n");
	M_LAUNCHER_DESTROY(l);
	return true;
}

bool	fill_prog_args(char** prog_args, c_label_alphanum* path_executable, c_label_alphanum* arguments_executable)
{
	const char*	arg_content = arguments_executable->f_get_content();
	int		size = tools::f_strlen(path_executable->f_get_content()) + ((arg_content != NULL) ? (1 + tools::f_strlen(arg_content)) : 0) + 1;

	*prog_args = new (std::nothrow) char[size];
	if (*prog_args == NULL)
		return D_ERR_ALLOC;
	(*prog_args)[0] = 0;
	tools::f_strncat(*prog_args, path_executable->f_get_content(), tools::f_strlen(path_executable->f_get_content()));
	if (arg_content != NULL)
	{
		tools::f_strncat(*prog_args, " ", 1);
		tools::f_strncat(*prog_args, arg_content, tools::f_strlen(arg_content));
	}
	(*prog_args)[size - 1] = 0;
	return true;
}

/* callback button close filter indicator */

bool	close_filter_indicator_button_callback(c_ncurses* ncurses, c_button* button)
{
	c_base_container*	filter_zone = button->f_get_parent()->f_get_parent();

	(void)ncurses;
	if (filter_zone == NULL)
		return M_ERROR_NO_ARGS(false, "Error: filter_zone = NULL\n");
	if (filter_zone->f_delete_child_by_ptr(button->f_get_parent()) == false ||
	    update_all_filter_position(filter_zone) == false)
		return false;
	return true;
}

bool	update_all_filter_position(c_base_container* filter_zone)
{
	int				i, size, good_y;
	std::vector<c_base_container*>*	child_vect = filter_zone->f_get_child_vect();;

	i = 0;
	size = child_vect->size();
	while (i < size)
	{
		good_y = filter_zone->f_get_info_size('y') + i * D_FILTER_INDICATOR_HEIGHT + 1;
		if ((*child_vect)[i]->f_get_info_size('y') != good_y &&
		    (*child_vect)[i]->f_move((*child_vect)[i]->f_get_info_size('x'), good_y) == false)
			return false;
		++i;
	}
	return true;
}

/* callback button graph */

bool	prev_function_graphic(c_ncurses* ncurses, c_button* button)
{
	(void)ncurses;
	return switch_fct(-1, button);
}

bool	next_function_graphic(c_ncurses* ncurses, c_button* button)
{
	(void)ncurses;
	return switch_fct(1, button);
}

bool	switch_fct(int offset, c_button* button)
{
	int			nbr;
	char*			str;
	c_graphic*		graphic = (c_graphic*)(button->f_get_parent()->f_get_child_by_index(D_GRAPHIC_INDEX));
	c_label_numeric*	nbr_fct = (c_label_numeric*)(button->f_get_parent()->f_get_child_by_index(D_NBR_FUNCTION_LABEL_INDEX));
	c_label_alphanum*	name_fct = (c_label_alphanum*)(button->f_get_parent()->f_get_child_by_index(D_NAME_FUNCTION_LABEL_INDEX));

	nbr = tools::f_atoi(nbr_fct->f_get_default_buffer());
	nbr += offset;
	if (nbr < -1 || nbr >= graphic->f_function_graphic_count())
		return true;
	else if (nbr == -1)
	{
		if (nbr_fct->f_init_default_buffer(D_CURR_NBR_FUNCTION) == false ||
		    name_fct->f_init_default_buffer(D_CURR_NAME_FUNCTION) == false)
			return false;
	}
	else
	{
		str = tools::f_itoa(nbr);
		if (str == NULL)
			return M_ERROR(false, "Error: tools::f_itoa(%d)\n", nbr);
		if (nbr_fct->f_init_default_buffer(str) == false ||
		    name_fct->f_init_default_buffer(graphic->f_get_function_graphic_by_index(nbr)->f_get_name()) == false)
		{
			delete [] str;
			return false;
		}
		delete [] str;
	}
	if (nbr_fct->f_clean_buffer() == false ||
	    name_fct->f_clean_buffer() == false)
		return false;
	nbr_fct->f_push_default_buffer_in_buffer();
	name_fct->f_push_default_buffer_in_buffer();
	return true;
}
