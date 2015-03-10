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

#include <c_init_secondary_item.h>
#include <c_ui.h>
#include <c_tab_manager.h>
#include <tools.h>
#include <c_data_ui.h>
#include <d_children_indexes.h>
#include <d_tab.h>
#include <c_tab.h>
#include <c_calltree.h>
#include <c_ncurses.h>
#include <c_event.h>
#include <c_graph.h>
#include <c_menu_scroll.h>
#include <c_function_indicator.h>
#include <c_function_calltree.h>
#include <d_indicator.h>
#include <c_data.h>

/* constructer destructer */

c_init_secondary_item::c_init_secondary_item(c_ncurses* ncurses,
					     c_event* event,
					     c_data_ui* data_ui) : __v_event(event),
								   __v_data_ui(data_ui),
								   __v_ncurses(ncurses)
{

}

c_init_secondary_item::~c_init_secondary_item(void)
{

}

/* public function */

bool	c_init_secondary_item::f_init_calltree_tab(void)
{
	c_base_container*	obj;
	c_tab_manager*		tab_manager;

	obj = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX);
	if (obj == NULL)
		return M_ERROR(false, "Error: f_get_child_by_index(%d)", D_MIDEL_CONTAINER_INDEX);
	if (obj->f_get_obj_type() != E_CONTAINER)
		return M_ERROR_NO_ARGS(false, "Error: bad index");

	obj = obj->f_get_child_by_index(D_TAB_MANAGER_INDEX);
	if (obj == NULL)
		return M_ERROR(false, "Error: f_get_child_by_index(%d)", D_TAB_MANAGER_INDEX);
	if (obj->f_get_obj_type() != E_TAB_MANAGER)
		return M_ERROR_NO_ARGS(false, "Error: bad index");

	tab_manager = (c_tab_manager*)(obj);
	if (tab_manager->f_add_tab(D_CALLTREE_NAME_TAB, D_CALLTREE_NAME_BUTTON) == false ||
	    this->__f_fill_calltree_tab(tab_manager) == false)
		return false;
	return true;
}

bool	c_init_secondary_item::f_init_graph_tab(void)
{
	c_base_container*	obj;
	c_tab_manager*		tab_manager;

	obj = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX);
	if (obj == NULL)
		return M_ERROR(false, "Error: f_get_child_by_index(%d)", D_MIDEL_CONTAINER_INDEX);
	if (obj->f_get_obj_type() != E_CONTAINER)
		return M_ERROR_NO_ARGS(false, "Error: bad index");

	obj = obj->f_get_child_by_index(D_TAB_MANAGER_INDEX);
	if (obj == NULL)
		return M_ERROR(false, "Error: f_get_child_by_index(%d)", D_TAB_MANAGER_INDEX);
	if (obj->f_get_obj_type() != E_TAB_MANAGER)
		return M_ERROR_NO_ARGS(false, "Error: bad index");

	tab_manager = (c_tab_manager*)(obj);
	if (tab_manager->f_add_tab(D_GRAPH_NAME_TAB, D_GRAPH_NAME_BUTTON) == false ||
	    this->__f_fill_graph_tab(tab_manager) == false)
		return false;
	return true;
}

bool	c_init_secondary_item::f_init_tabs(void)
{
	int			i, size;
	unsigned		len;
	const char*		name_tab;
	c_menu_scroll*		menu = this->__f_get_select_tab_menu();
	std::vector<int>	v_index;

	if (menu == NULL)
		return M_ERROR_NO_ARGS(false, "Error: menu = NULL\n");
	if (this->__f_clean_workspace() == false)
		return false;
	i = 0;
	menu->f_get_items_selected_vector_index(&v_index);
	size = v_index.size();
	while (i < size)
	{
		name_tab = menu->f_item_name_by_index(v_index[i]);
		if (name_tab == NULL)
			return M_ERROR(false, "Error: menu->f_item_name_by_index(%d)\n", i);
		len = tools::f_strlen(name_tab);
		if (len == tools::f_strlen(D_CALLTREE_NAME_TAB) &&
		    tools::f_strncmp(name_tab, D_CALLTREE_NAME_TAB, len) == 0 &&
		    this->f_init_calltree_tab() == false)
			return false;
		if (len == tools::f_strlen(D_GRAPH_NAME_TAB) &&
		    tools::f_strncmp(name_tab, D_GRAPH_NAME_TAB, len) == 0 &&
		    this->f_init_graph_tab() == false)
			return false;
		++i;
	}
	return true;
}

bool	c_init_secondary_item::f_init_error_zone(void)
{
	if (this->__f_add_fct_indict_to_err_zone("0") == false ||
	    this->__f_add_fct_indict_to_err_zone("01") == false ||
	    this->__f_add_fct_indict_to_err_zone("02") == false ||
	    this->__f_add_fct_indict_to_err_zone("02000") == false ||
	    this->__f_add_fct_indict_to_err_zone("0200") == false ||
	    this->__f_add_fct_indict_to_err_zone("0201") == false ||
	    this->__f_add_fct_indict_to_err_zone("0202") == false ||
	    this->__f_add_fct_indict_to_err_zone("0203") == false)
		return false;
	return true;
}

/* private function */

bool	c_init_secondary_item::__f_fill_calltree_tab(c_tab_manager* tab_manager)
{
	c_calltree*	calltree;
	c_tab*		tab = (c_tab*)(tab_manager->f_get_child_by_index(D_CALLTREE_TAB_INDEX));

	if (tab == NULL)
		return M_ERROR(false, "Error: f_get_child_by_index(%d)\n", D_CALLTREE_TAB_INDEX);
	if (tab->f_get_obj_type() != E_TAB)
		return M_ERROR_NO_ARGS(false, "Error: bad index");
	calltree = new (std::nothrow) c_calltree(this->__v_ncurses, this->__v_event, tab);
	if (calltree == NULL)
		return D_ERR_ALLOC;
	if (tab->f_add_child(calltree) == false)
	{
		delete calltree;
		return false;
	}
	return calltree->f_init_calltree();
}

bool	c_init_secondary_item::__f_fill_graph_tab(c_tab_manager* tab_manager)
{
	c_graph*	graph;
	c_tab*		tab = (c_tab*)(tab_manager->f_get_child_by_index(D_GRAPH_TAB_INDEX));

	if (tab == NULL)
		return M_ERROR(false, "Error: f_get_child_by_index(%d)\n", D_GRAPH_TAB_INDEX);
	if (tab->f_get_obj_type() != E_TAB)
		return M_ERROR_NO_ARGS(false, "Error: bad index");
	graph = new (std::nothrow) c_graph(this->__v_ncurses, this->__v_event, tab);
	if (graph == NULL)
		return D_ERR_ALLOC;
	if (tab->f_add_child(graph) == false)
	{
		delete graph;
		return false;
	}
	return graph->f_init_graph();
}

c_menu_scroll*	c_init_secondary_item::__f_get_select_tab_menu(void)
{
	c_base_container*	obj;

	obj = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX);
	if (obj == NULL)
		return M_ERROR((c_menu_scroll*)(NULL), "Error: f_get_child_by_index(%d)", D_MIDEL_CONTAINER_INDEX);
	if (obj->f_get_obj_type() != E_CONTAINER)
		return M_ERROR_NO_ARGS((c_menu_scroll*)(NULL), "Error: bad index");

	obj = obj->f_get_child_by_index(D_TAB_MANAGER_INDEX);
	if (obj == NULL)
		return M_ERROR((c_menu_scroll*)(NULL), "Error: f_get_child_by_index(%d)", D_TAB_MANAGER_INDEX);
	if (obj->f_get_obj_type() != E_TAB_MANAGER)
		return M_ERROR_NO_ARGS((c_menu_scroll*)(NULL), "Error: bad index");

	obj = obj->f_get_child_by_index(D_CHOICE_EXECUTABLE_TAB_INDEX);
	if (obj == NULL)
		return M_ERROR((c_menu_scroll*)(NULL), "Error: f_get_child_by_index(%d)", D_CHOICE_EXECUTABLE_TAB_INDEX);
	if (obj->f_get_obj_type() != E_TAB)
		return M_ERROR_NO_ARGS((c_menu_scroll*)(NULL), "Error: bad index");

	obj = obj->f_get_child_by_index(D_SELECT_TAB_WILL_GENERATE_INDEX);
	if (obj == NULL)
		return M_ERROR((c_menu_scroll*)(NULL), "Error: f_get_child_by_index(%d)", D_SELECT_TAB_WILL_GENERATE_INDEX);
	if (obj->f_get_obj_type() != E_MENU)
		return M_ERROR_NO_ARGS((c_menu_scroll*)(NULL), "Error: bad index");
	return (c_menu_scroll*)(obj);
}

bool	c_init_secondary_item::__f_clean_workspace(void)
{
	this->__f_clean_indicator();
	return this->__f_clean_tab_manager();
}

c_tab_manager*	c_init_secondary_item::__f_get_tab_manager(void)
{
	c_base_container*	obj;

	obj = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX);
	if (obj == NULL)
		return M_ERROR((c_tab_manager*)(NULL), "Error: f_get_child_by_index(%d)", D_MIDEL_CONTAINER_INDEX);
	if (obj->f_get_obj_type() != E_CONTAINER)
		return M_ERROR_NO_ARGS((c_tab_manager*)(NULL), "Error: bad index");

	obj = obj->f_get_child_by_index(D_TAB_MANAGER_INDEX);
	if (obj == NULL)
		return M_ERROR((c_tab_manager*)(NULL), "Error: f_get_child_by_index(%d)", D_TAB_MANAGER_INDEX);
	if (obj->f_get_obj_type() != E_TAB_MANAGER)
		return M_ERROR_NO_ARGS((c_tab_manager*)(NULL), "Error: bad index");
	return (c_tab_manager*)(obj);
}

bool	c_init_secondary_item::__f_clean_tab_manager(void)
{
	int				size;
	c_tab_manager*			tab_manager = this->__f_get_tab_manager();
	std::vector<c_base_container*>*	child_vect = tab_manager->f_get_child_vect();

	if (tab_manager == NULL)
		return false;
	size = child_vect->size();
	if (size < 2)
		return M_ERROR_NO_ARGS(false, "Error: tab_manager have a wrong child number\n");
	else if (size > 2)
	{
		while (size > 2)
		{
			if (tab_manager->f_delete_child_by_index(2) == false)
				return false;
			size = child_vect->size();
		}
	}
	return true;
}

void	c_init_secondary_item::__f_clean_indicator(void)
{
	this->__f_clean_fct_indict();
	this->__f_clean_filter_indict();
}

void	c_init_secondary_item::__f_clean_fct_indict(void)
{
	c_base_container*	error_zone = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX)->f_get_child_by_index(D_ERROR_ZONE);

	error_zone->f_delete_all_child();
}

void	c_init_secondary_item::__f_clean_filter_indict(void)
{
	c_base_container*	filter_zone = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX)->f_get_child_by_index(D_FILTER_ZONE);

	filter_zone->f_delete_all_child();
}

bool	c_init_secondary_item::__f_init_one_fct_indict(c_base_container* parent,
						       c_function_calltree* fct_calltree,
						       int x, int y, int width, int height)
{
	c_function_indicator*	fct_indict;

	fct_indict = new (std::nothrow) c_function_indicator(this->__v_ncurses, this->__v_event, parent);
	if (fct_indict == NULL)
		return D_ERR_ALLOC;
	if (parent->f_add_child(fct_indict) == false)
	{
		delete fct_indict;
		return false;
	}
	return fct_indict->f_init_indicator(fct_calltree, x, y, width, height);
}

bool	c_init_secondary_item::__f_add_fct_indict_to_err_zone(const char* multiple_index)
{
	c_calltree*		calltree;
	c_base_container*	error_zone;

	error_zone = this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX)->f_get_child_by_index(D_ERROR_ZONE);
	calltree = (c_calltree*)(this->__v_data_ui->v_main_container.f_get_child_by_index(D_MIDEL_CONTAINER_INDEX)->f_get_child_by_index(D_TAB_MANAGER_INDEX)->f_get_child_by_index(D_CALLTREE_TAB_INDEX)->f_get_child_by_index(D_CALLTREE_INDEX));
	return this->__f_init_one_fct_indict(error_zone, calltree->f_get_fct_by_multiple_index(multiple_index),
					     error_zone->f_get_info_size('x') + 1,
					     error_zone->f_get_info_size('y') + 1 + error_zone->f_child_count() * D_FILTER_INDICATOR_HEIGHT,
					     error_zone->f_get_info_size('w') - 2,
					     D_FILTER_INDICATOR_HEIGHT);
}
