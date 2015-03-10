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

#include <c_init_ui.h>
#include <c_ncurses.h>
#include <c_event.h>
#include <c_container.h>
#include <tools.h>
#include <c_toolbar.h>
#include <c_state_bar.h>
#include <c_tab_manager.h>
#include <c_tab.h>
#include <callbacks_tabs.h>
#include <c_data_ui.h>
#include <d_menu.h>
#include <c_label_alphanum.h>
#include <c_button.h>
#include <c_menu_scroll.h>
#include <d_event.h>
#include <callbacks_menus.h>
#include <c_zone.h>
#include <c_menu_button.h>
#include <d_children_indexes.h>
#include <c_profiler_menu.h>
#include <c_profiler_infos_menu.h>
#include <d_tab.h>
#include <callbacks_labels.h>

/* constructer destructer */

c_init_ui::c_init_ui(c_ncurses* ncurses,
		     c_event* event,
		     c_data_ui* data_ui) : __v_event(event),
					   __v_ncurses(ncurses),
					   __v_data_ui(data_ui),
					   __v_init_secondary_item(ncurses,
								   event,
								   data_ui)
{

}

c_init_ui::~c_init_ui(void)
{

}

/* public function */

bool	c_init_ui::f_init_interface(void)
{
	if (this->__f_init_toolbar(&this->__v_data_ui->v_main_container) == false ||
	    this->__f_init_midel_container(&this->__v_data_ui->v_main_container) == false ||
	    this->__f_init_state_bar(&this->__v_data_ui->v_main_container) == false ||
	    this->__f_init_toolbar_menus() == false)
		return false;
	return true;
}

bool	c_init_ui::f_update_profilers_infos_menu(c_menu_scroll* profilers_menu)
{
	int							nb_options;
	int							selected_item_index;
	c_menu_scroll*						profilers_infos_menu;
	std::vector<pH::ph_tools::c_profiler*>			v_profiler;

	if (pH::ph_tools::c_profilers::sf_get_choices(&v_profiler) == false)
		return M_ERROR(false, "Error: pH::ph_tools::c_profilers::sf_get_choices(%p)\n", &v_profiler);
	if (v_profiler.size() == 0)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return M_ERROR_NO_ARGS(false, "Error: there is nothing managed profilers\n");
	}

	selected_item_index = profilers_menu->f_get_first_item_selected_index();

	nb_options = v_profiler[selected_item_index]->f_options()->size();
	if (this->__f_alloc_tab_infos(nb_options > 0 ? nb_options + 1 : 2) == false)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return false;
	}

	if (this->__f_fill_tab_profiler_options(v_profiler[selected_item_index]->f_options()) == false)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return false;
	}

	profilers_infos_menu = (c_menu_scroll*)(profilers_menu->f_get_parent()->f_get_child_by_index(D_CHOICE_SUB_OPTIONS_MENU_INDEX));
	if (profilers_menu == NULL)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return M_ERROR_NO_ARGS(false, "profilers_infos_menu = NULL\n");
	}
	if (profilers_infos_menu->f_update_data_menu(this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos, this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos) == false)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return false;
	}
	pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
	return true;
}

bool	c_init_ui::f_init_secondary_item(void)
{
	if (this->__v_init_secondary_item.f_init_tabs() == false ||
	    this->__v_init_secondary_item.f_init_error_zone() == false)
		return false;
	return true;
}

/* private function */

bool	c_init_ui::__f_init_toolbar(c_base_container* parent)
{
	WINDOW*		win = parent->f_get_window()->f_get_window();
	c_toolbar*	toolbar = new (std::nothrow) c_toolbar(this->__v_ncurses, this->__v_event, parent);

	if (toolbar == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_toolbar(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(toolbar, NULL,
				       getbegx(win),
				       getbegy(win),
				       getmaxx(win),
				       getbegx(win) + 1, true) == false)
		return false;
	if (toolbar->f_add_button(" File     ", E_TOOLBAR_FILE_BUTTON, &file_toolbar_button_callback) == false ||
	    toolbar->f_add_button(" Tools     ", E_TOOLBAR_TOOLS_BUTTON, &tools_toolbar_button_callback) == false ||
	    toolbar->f_add_button(" Help     ", E_TOOLBAR_HELP_BUTTON, &help_toolbar_button_callback) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_midel_container(c_base_container* parent)
{
	WINDOW*		win = parent->f_get_window()->f_get_window();
	c_container*	midel_container = new (std::nothrow) c_container(this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container);

	if (midel_container == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_container(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(midel_container, NULL,
				       getbegx(win),
				       getbegy(win) + 1,
				       getmaxx(win),
				       getmaxy(win)) == false ||
	    this->__f_fill_midel_container(midel_container) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_state_bar(c_base_container* parent)
{
	WINDOW*		win = parent->f_get_window()->f_get_window();
	c_state_bar*	state_bar = new (std::nothrow) c_state_bar(this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container);

	if (state_bar == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_state_bar(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container);
	if (this->__f_add_object_in_ui(state_bar, NULL,
				       getbegx(win),
				       getmaxy(win) - 1,
				       getmaxx(win),
				       getmaxy(win)) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_fill_midel_container(c_base_container* midel_container)
{
	if (this->__f_init_tab_manager(midel_container) == false ||
	    this->__f_init_search_module(midel_container) == false ||
	    this->__f_init_error_zone(midel_container) == false ||
	    this->__f_init_filter_module(midel_container) == false ||
	    this->__f_init_filter_zone(midel_container) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_tab_manager(c_base_container* parent)
{
	WINDOW*			win = parent->f_get_window()->f_get_window();
	c_base_container*	tab_manager = new (std::nothrow) c_tab_manager(this->__v_ncurses, this->__v_event, parent);

	if (tab_manager == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_tab_manager(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(tab_manager, "Tabs manager",
				       getbegx(win),
				       getbegy(win),
				       getmaxx(win) - (getmaxx(win) >> 2),
				       getmaxy(win)) == false ||
	    this->__f_fill_tab_manager((c_tab_manager*)(tab_manager)) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_fill_tab_manager(c_tab_manager* tab_manager)
{
	if (tab_manager->f_add_tab(D_CHOICE_EXECUTABLE_NAME_TAB, D_CHOICE_EXECUTABLE_NAME_BUTTON) == false)
		return false;
	tab_manager->f_set_tab_active_by_index(0);
	if (this->__f_fill_first_tab(tab_manager->f_get_tab_by_index(0)) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_fill_first_tab(c_tab* tab)
{
	if (this->__f_init_menu_first_tab(tab) == false ||
	    this->__f_init_label_first_tab(tab) == false ||
	    this->__f_init_button_first_tab(tab) == false)
		return false;
	tab->f_add_single_callback('b', &browse_executable_tab_callback);
	tab->f_add_single_callback('l', &launch_executable_tab_callback);
	return true;
}

bool	c_init_ui::__f_init_menu_first_tab(c_tab* tab)
{
	const char*	name_init[] = {" ", NULL};
	const char*	description_init[] = {" ", NULL};

	if (this->__f_init_content_menu_first_tab() == false)
		return false;
	if (this->__f_add_menu_in_tab(tab, "Choice one prolfiler",
				      this->__v_data_ui->v_profiler_menu.v_name_profilers, this->__v_data_ui->v_profiler_menu.v_description_profilers,
				      tab->f_get_info_size('x') + 1,
				      tab->f_get_info_size('y') + 1,
				      (tab->f_get_info_size('w') - 2) / 3,
				      10,
				      true, false) == false ||
	    this->__f_add_menu_in_tab(tab, "Choice sub options",
				      (char**)(name_init), (char**)(description_init),
				      tab->f_get_info_size('x') + tab->f_get_info_size('w') / 3,
				      tab->f_get_info_size('y') + 1,
				      (tab->f_get_info_size('w') - 2) / 3,
				      10,
				      true, true) == false ||
	    this->__f_add_menu_in_tab(tab, "Select tab will generate",
				      this->__v_data_ui->v_select_tab_menu.v_name_tab, this->__v_data_ui->v_select_tab_menu.v_description_tab,
				      tab->f_get_info_size('x') + (tab->f_get_info_size('w') / 3) * 2,
				      tab->f_get_info_size('y') + 1,
				      (tab->f_get_info_size('w') - 2) / 3,
				      10,
				      true, true) == false ||
	    this->__f_set_somes_menu_options(tab) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_content_menu_first_tab(void)
{
	if (this->__f_init_profiler_menu() == false ||
	    this->__f_init_select_tab_menu() == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_profiler_menu(void)
{
	int					nb_profiler;
	std::vector<pH::ph_tools::c_profiler*>	v_profiler;

	if (pH::ph_tools::c_profilers::sf_get_choices(&v_profiler) == false)
		return M_ERROR(false, "Error: pH::ph_tools::c_profilers::sf_get_choices(%p)\n", &v_profiler);
	nb_profiler = v_profiler.size();
	if (nb_profiler == 0)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return M_ERROR_NO_ARGS(false, "Error: there is nothing managed profilers\n");
	}
	if (this->__f_alloc_tab(nb_profiler + 1) == false)
	{
		pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
		return false;
	}
	if (this->__f_fill_tab_profilers(&v_profiler) == false)
		return false;
	pH::ph_tools::c_profilers::sf_destroy_vector(&v_profiler);
	return true;
}

bool	c_init_ui::__f_init_select_tab_menu(void)
{
	int		i, size;
	const char*	name_tab[] = {D_CALLTREE_NAME_TAB, D_GRAPH_NAME_TAB, NULL};
	const char*	description_tab[] = {"", "", NULL};

	size = tools::f_nb_element(name_tab) + 1;
	this->__v_data_ui->v_select_tab_menu.v_name_tab = new (std::nothrow) char*[size];
	if (this->__v_data_ui->v_select_tab_menu.v_name_tab == NULL)
		return D_ERR_ALLOC;
	this->__v_data_ui->v_select_tab_menu.v_description_tab = new (std::nothrow) char*[size];
	if (this->__v_data_ui->v_select_tab_menu.v_description_tab == NULL)
		return D_ERR_ALLOC;
	i = 0;
	while (i < size)
	{
		this->__v_data_ui->v_select_tab_menu.v_name_tab[i] = NULL;
		this->__v_data_ui->v_select_tab_menu.v_description_tab[i] = NULL;
		++i;
	}
	i = 0;
	--size;
	while (i < size)
	{
		this->__v_data_ui->v_select_tab_menu.v_name_tab[i] = tools::f_strdup(name_tab[i]);
		if (this->__v_data_ui->v_select_tab_menu.v_name_tab[i] == NULL)
			return M_ERROR_NO_ARGS(false, "Error: strdup\n");
		this->__v_data_ui->v_select_tab_menu.v_description_tab[i] = tools::f_strdup(description_tab[i]);
		if (this->__v_data_ui->v_select_tab_menu.v_description_tab[i] == NULL)
			return M_ERROR_NO_ARGS(false, "Error: strdup\n");
		++i;
	}
	return true;
}

bool	c_init_ui::__f_alloc_tab(int nb_profiler)
{
	int	i;

	this->__v_data_ui->v_profiler_menu.v_name_profilers = new (std::nothrow) char*[nb_profiler];
	if (this->__v_data_ui->v_profiler_menu.v_name_profilers == NULL)
		return D_ERR_ALLOC;
	this->__v_data_ui->v_profiler_menu.v_nb_profiler = nb_profiler;
	this->__v_data_ui->v_profiler_menu.v_description_profilers = new (std::nothrow) char*[nb_profiler];
	if (this->__v_data_ui->v_profiler_menu.v_description_profilers == NULL)
		return D_ERR_ALLOC;
	i = 0;
	while (i < nb_profiler)
	{
		this->__v_data_ui->v_profiler_menu.v_name_profilers[i] = NULL;
		this->__v_data_ui->v_profiler_menu.v_description_profilers[i] = NULL;
		++i;
	}
	return true;
}

bool	c_init_ui::__f_alloc_tab_infos(int nb_profiler)
{
	int	i;

	tools::f_delete_tab_aptr(this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos, this->__v_data_ui->v_profiler_infos_menu.v_nb_profiler_infos);
	tools::f_delete_tab_aptr(this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos, this->__v_data_ui->v_profiler_infos_menu.v_nb_profiler_infos);
	this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos = new (std::nothrow) char*[nb_profiler];
	if (this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos == NULL)
		return D_ERR_ALLOC;
	this->__v_data_ui->v_profiler_infos_menu.v_nb_profiler_infos = nb_profiler;
	this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos = new (std::nothrow) char*[nb_profiler];
	if (this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos == NULL)
		return D_ERR_ALLOC;
	i = 0;
	while (i < nb_profiler)
	{
		this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos[i] = NULL;
		this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[i] = NULL;
		++i;
	}
	return true;
}

bool	c_init_ui::__f_fill_tab_profilers(std::vector<pH::ph_tools::c_profiler*>* v_profiler)
{
	int	i, size;

	i = 0;
	size = v_profiler->size();
	while (i < size)
	{
		this->__v_data_ui->v_profiler_menu.v_name_profilers[i] = tools::f_strdup((*v_profiler)[i]->f_value());
		if (this->__v_data_ui->v_profiler_menu.v_name_profilers[i] == NULL)
			return D_ERR_ALLOC;
		this->__v_data_ui->v_profiler_menu.v_description_profilers[i] = new (std::nothrow) char[1];
		if (this->__v_data_ui->v_profiler_menu.v_description_profilers[i] == NULL)
			return D_ERR_ALLOC;
		this->__v_data_ui->v_profiler_menu.v_description_profilers[i][0] = 0;
		++i;
	}
	return true;
}

bool	c_init_ui::__f_fill_tab_profiler_options(std::vector<pH::ph_tools::c_profiler_option*>* v_profiler_option)
{
	int	i, size;

	if (v_profiler_option->empty() == true)
	{
		this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos[0] = tools::f_strdup(D_PROFILER_INFOS_NOHING);
		if (this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos[0] == NULL)
			return D_ERR_ALLOC;
		this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[0] = new (std::nothrow) char[1];
		if (this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[0] == NULL)
			return D_ERR_ALLOC;
		this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[0][0] = 0;
		return true;
	}
	i = 0;
	size = v_profiler_option->size();
	while (i < size)
	{
		this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos[i] = tools::f_strdup((*v_profiler_option)[i]->f_string());
		if (this->__v_data_ui->v_profiler_infos_menu.v_name_profilers_infos[i] == NULL)
			return D_ERR_ALLOC;
		this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[i] = new (std::nothrow) char[1];
		if (this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[i] == NULL)
			return D_ERR_ALLOC;
		this->__v_data_ui->v_profiler_infos_menu.v_description_profilers_infos[i][0] = 0;
		++i;
	}
	return true;
}

bool	c_init_ui::__f_init_label_first_tab(c_tab* tab)
{
	c_label_alphanum*	label;

	label = new (std::nothrow) c_label_alphanum(this->__v_ncurses, this->__v_event, tab);
	if (label == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_label_alphanum(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, tab);
	if (this->__f_add_label_alphanum_in_ui(label, "Executable path",
					       D_LABEL_BUFFER_SIZE,
					       tab->f_get_info_size('x') + 1,
					       tab->f_get_info_size('y') + 15,
					       (tab->f_get_info_size('w') >> 2) * 3) == false)
		return false;
	label = new (std::nothrow) c_label_alphanum(this->__v_ncurses, this->__v_event, tab);
	if (label == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_label_alphanum(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, tab);
	if (this->__f_add_label_alphanum_in_ui(label, "Executable arguments",
					       D_LABEL_BUFFER_SIZE,
					       tab->f_get_info_size('x') + 1,
					       tab->f_get_info_size('y') + 20,
					       (tab->f_get_info_size('w') >> 2) * 3) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_button_first_tab(c_tab* tab)
{
	c_button*	button;
	const char*	button_name[] = {" Browse executable " , " Launch analyse "};

	button = new (std::nothrow) c_button(this->__v_ncurses, this->__v_event, tab, E_BROWSE_EXECUTABLE_BUTTON);
	if (button == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_button(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, tab);
	if (this->__f_add_button_in_ui(button, button_name[0],
				       tab->f_get_info_size('x') + 1,
				       tab->f_get_info_size('y') + 17,
				       tools::f_strlen(button_name[0]),
				       1) == false)
		return false;
	button->f_set_button_callback(&browse_executable_button_callback);
	button = new (std::nothrow) c_button(this->__v_ncurses, this->__v_event, tab, E_LAUNCH_EXECUTABLE_BUTTON);
	if (button == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_button(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, tab);
	if (this->__f_add_button_in_ui(button, button_name[1],
				       tab->f_get_info_size('x') + 1,
				       tab->f_get_info_size('y') + 22,
				       tools::f_strlen(button_name[1]),
				       1) == false)
		return false;
	button->f_set_button_callback(&launch_executable_button_callback);
	return true;
}

bool	c_init_ui::__f_add_menu_in_tab(c_tab* tab, const char* title,
				       char** names, char** descriptions,
				       int x, int y, int width, int height,
				       bool value_selectable, bool multi_selection)
{
	c_menu_scroll*	profiler_menu;

	profiler_menu = new (std::nothrow) c_menu_scroll(this->__v_ncurses, this->__v_event, (c_base_container*)(tab), value_selectable, multi_selection);
	if (profiler_menu == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_menu_scroll(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, tab);
	if (tab->f_add_child(profiler_menu) == false)
	{
		delete profiler_menu;
		return false;
	}
	if (profiler_menu->f_init_menu(names, descriptions, x, y, width, height, title) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_set_somes_menu_options(c_tab* tab)
{
	c_base_container*	child;

	child = tab->f_get_child_by_index(D_CHOICE_ONE_PROFILER_MENU_INDEX);
	if (child == NULL)
		return M_ERROR_NO_ARGS(false, "Error: child = NULL\n");
	child->f_get_window()->f_set_data_resize(true, false, true);
	if (child->f_add_single_callback(D_ENTER, &event_enter_names_profiler_menu) == false ||
	    event_enter_names_profiler_menu(this->__v_ncurses, (c_menu_scroll*)(child)) == false)
		return false;
	child = tab->f_get_child_by_index(D_CHOICE_SUB_OPTIONS_MENU_INDEX);
	if (child == NULL)
		return M_ERROR_NO_ARGS(false, "Error: child = NULL\n");
	child->f_get_window()->f_set_data_resize(true, false, true);
	((c_menu_scroll*)(child))->f_set_value_all_item(true);
	child = tab->f_get_child_by_index(D_SELECT_TAB_WILL_GENERATE_INDEX);
	if (child == NULL)
		return M_ERROR_NO_ARGS(false, "Error: child = NULL\n");
	child->f_get_window()->f_set_data_resize(true, false, true);
	return ((c_menu_scroll*)(child))->f_set_value_all_item(true);
}

bool	c_init_ui::__f_init_search_module(c_base_container* parent)
{
	WINDOW*			win = parent->f_get_window()->f_get_window();
	c_base_container*	search_module = new (std::nothrow) c_zone(this->__v_ncurses, this->__v_event, parent);
	c_label_alphanum*	label;

	if (search_module == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_zone(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(search_module, "Search module",
				       getmaxx(win) - (getmaxx(win) >> 2),
				       getbegy(win),
				       getmaxx(win),
				       5) == false)
			return false;
	label = new (std::nothrow) c_label_alphanum(this->__v_ncurses, this->__v_event, search_module);
	if (label == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_label_alphanum(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, search_module);
	if (this->__f_add_label_alphanum_in_ui(label, "Type text here",
					       D_LABEL_BUFFER_SIZE,
					       getbegx(search_module->f_get_window()->f_get_window()) + 1,
					       getbegy(search_module->f_get_window()->f_get_window()) + 1,
					       getmaxx(search_module->f_get_window()->f_get_window()) - 2) == false)
		return false;
	label->f_set_real_time_callback(&search_module_real_time_callback);
	return true;
}

bool	c_init_ui::__f_init_error_zone(c_base_container* parent)
{
	WINDOW*			win = parent->f_get_window()->f_get_window();
	c_base_container*	error_zone = new (std::nothrow) c_zone(this->__v_ncurses, this->__v_event, parent);

	if (error_zone == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_zone(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(error_zone, "Error zone",
				       getmaxx(win) - (getmaxx(win) >> 2),
				       getbegy(win) + 4,
				       getmaxx(win),
				       getmaxy(win) >> 1) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_filter_module(c_base_container* parent)
{
	c_label_alphanum*	label;
	WINDOW*			win = parent->f_get_window()->f_get_window();
	c_base_container*	filter_module = new (std::nothrow) c_zone(this->__v_ncurses, this->__v_event, parent);

	if (filter_module == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_zone(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(filter_module, "Filter module",
				       getmaxx(win) - (getmaxx(win) >> 2),
				       getmaxy(win) >> 1,
				       getmaxx(win),
				       (getmaxy(win) >> 1) + 4) == false)
		return false;
	label = new (std::nothrow) c_label_alphanum(this->__v_ncurses, this->__v_event, filter_module);
	if (label == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_label_alphanum(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, filter_module);
	if (this->__f_add_label_alphanum_in_ui(label, "Type text here",
					       D_LABEL_BUFFER_SIZE,
					       getbegx(filter_module->f_get_window()->f_get_window()) + 1,
					       getbegy(filter_module->f_get_window()->f_get_window()) + 1,
					       getmaxx(filter_module->f_get_window()->f_get_window()) - 2) == false ||
	    label->f_add_single_callback(D_ENTER, &filter_label_enter_callback) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_filter_zone(c_base_container* parent)
{
	WINDOW*			win = parent->f_get_window()->f_get_window();
	c_base_container*	filter_zone = new (std::nothrow) c_zone(this->__v_ncurses, this->__v_event, parent);

	if (filter_zone == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) c_zone(%p, %p, %p)\n", this->__v_ncurses, this->__v_event, parent);
	if (this->__f_add_object_in_ui(filter_zone, "Filter zone",
				       getmaxx(win) - (getmaxx(win) >> 2),
				       (getmaxy(win) >> 1) + 4,
				       getmaxx(win),
				       getmaxy(win)) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_toolbar_menus(void)
{
	c_button*		button;
	c_base_container*	toolbar;
	c_menu_button*		menu_button;

	toolbar = ((c_toolbar*)(this->__f_get_child_by_type(E_TOOLBAR, &this->__v_data_ui->v_main_container)));
	if (toolbar == NULL)
		return M_ERROR_NO_ARGS(false, "Error: toolbar = NULL\n");


	button = ((c_toolbar*)(toolbar))->f_get_button_by_type(E_TOOLBAR_FILE_BUTTON);
	if (button == NULL)
		return M_ERROR_NO_ARGS(false, "Error: button = NULL\n");
	menu_button = new (std::nothrow) c_menu_button(this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container, button, E_FILE_MENU);
	if (menu_button == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_menu_button(%p, %p, %p, %p, %d)\n", this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container, button, E_FILE_MENU);
	if (this->__f_add_menu_button_in_ui(menu_button) == false)
		return false;


	button = ((c_toolbar*)(toolbar))->f_get_button_by_type(E_TOOLBAR_TOOLS_BUTTON);
	if (button == NULL)
		return M_ERROR_NO_ARGS(false, "Error: button = NULL\n");
	menu_button = new (std::nothrow) c_menu_button(this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container, button, E_TOOLS_MENU);
	if (menu_button == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_menu_button(%p, %p, %p, %p, %d)\n", this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container, button, E_TOOLS_MENU);
	if (this->__f_add_menu_button_in_ui(menu_button) == false)
		return false;


	button = ((c_toolbar*)(toolbar))->f_get_button_by_type(E_TOOLBAR_HELP_BUTTON);
	if (button == NULL)
		return M_ERROR_NO_ARGS(false, "Error: button = NULL\n");
	menu_button = new (std::nothrow) c_menu_button(this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container, button, E_HELP_MENU);
	if (menu_button == NULL)
		return M_ERROR(false, "Error: new (std::nothrow) c_menu_button(%p, %p, %p, %p, %d)\n", this->__v_ncurses, this->__v_event, &this->__v_data_ui->v_main_container, button, E_HELP_MENU);
	if (this->__f_add_menu_button_in_ui(menu_button) == false)
		return false;
	return true;
}

c_base_container*	c_init_ui::__f_get_child_by_type(e_obj_type obj_type, c_base_container* container)
{
	int 				i, size;
	std::vector<c_base_container*>*	child_vect = container ? this->__v_data_ui->v_main_container.f_get_child_vect() : container->f_get_child_vect();

	i = 0;
	size = child_vect->size();
	while (i < size)
	{
		if ((*child_vect)[i]->f_get_obj_type() == obj_type)
			return (*child_vect)[i];
		++i;
	}
	return NULL;
}

bool	c_init_ui::__f_add_object_in_ui(c_base_container* obj,
					const char* title,
					int ax, int ay, int bx, int by,
					bool event_focused,
					e_insertion_child insertion)
{
	if (obj->f_get_obj_type() == E_MENU ||
	    obj->f_get_obj_type() == E_LABEL ||
	    obj->f_init(title, ax, ay, bx - ax, by - ay) == false ||
	    obj->f_get_parent()->f_add_child(obj, insertion) == false)
	{
		tools::f_delete_ptr(obj);
		return false;
	}
	if (event_focused == true &&
	    this->__v_event->f_add_container_focused(obj) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_add_label_alphanum_in_ui(c_label_alphanum* label, const char* default_buffer, int size_buffer, int x, int y, int width)
{
	if (label->f_init_label(default_buffer, size_buffer, x, y, width) == false ||
	    label->f_get_parent()->f_add_child(label) == false)
	{
		tools::f_delete_ptr(label);
		return false;
	}
	return true;
}

bool	c_init_ui::__f_add_button_in_ui(c_button* button, const char* title, int x, int y, int width, int height)
{
	if (button->f_init(title, x, y, width, height) == false ||
	    button->f_get_parent()->f_add_child(button) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_add_menu_button_in_ui(c_menu_button* menu)
{
	if (this->__f_init_menu(menu) == false ||
	    menu->f_get_parent()->f_add_child(menu) == false)
	{
		tools::f_delete_ptr(menu);
		return false;
	}
	if (this->__v_event->f_add_container_focused(menu, E_PUSH_FRONT_INSERTION) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_menu(c_menu* menu)
{
	e_menu_type	menu_type = menu->f_get_menu_type();

	switch	(menu_type)
	{
		case	E_FILE_MENU:	return this->__f_init_file_menu_button((c_menu_button*)(menu));
		case	E_TOOLS_MENU:	return this->__f_init_tools_menu_button((c_menu_button*)(menu));
		case	E_HELP_MENU:	return this->__f_init_help_menu_button((c_menu_button*)(menu));
		default:		return M_ERROR(false, "Error: menu type = %d, unknow value\n", menu_type);
	}
}

bool	c_init_ui::__f_init_file_menu_button(c_menu_button* menu)
{
	const char*			items[] = D_CONTENT_FILE_MENU;
	const char*			description[] = D_CONTENT_FILE_DESC;
	c_menu::t_single_callback	ptr_func_tab[] = D_PTR_FUNC_TAB_FILE;

	if (menu->f_init_menu(items, description, ptr_func_tab, "File menu") == false ||
	    menu->f_add_single_callback('o', &open_menu_file_callback) == false ||
	    menu->f_add_single_callback('s', &save_menu_file_callback) == false ||
	    menu->f_add_single_callback('S', &save_as_menu_file_callback) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_tools_menu_button(c_menu_button* menu)
{
	const char*			items[] = D_CONTENT_TOOLS_MENU;
	const char*			description[] = D_CONTENT_TOOLS_DESC;
	c_menu::t_single_callback	ptr_func_tab[] = D_PTR_FUNC_TAB_TOOLS;

	if (menu->f_init_menu(items, description, ptr_func_tab, "Tools menu") == false ||
	    menu->f_add_single_callback('O', &options_tools_menu_callback) == false)
		return false;
	return true;
}

bool	c_init_ui::__f_init_help_menu_button(c_menu_button* menu)
{
	const char*			items[] = D_CONTENT_HELP_MENU;
	const char*			description[] = D_CONTENT_HELP_DESC;
	c_menu::t_single_callback	ptr_func_tab[] = D_PTR_FUNC_TAB_HELP;

	if (menu->f_init_menu(items, description, ptr_func_tab, "Help menu") == false ||
	    menu->f_add_single_callback('r', &report_help_menu_callback) == false ||
	    menu->f_add_single_callback('a', &about_help_menu_callback) == false)
		return false;
	return true;
}
