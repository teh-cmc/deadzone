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

#include <c_popup_read_dir_action.h>
#include <e_popup_type.h>
#include <d_color_ui.h>
#include <tools.h>
#include <c_event.h>
#include <c_menu_scroll.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <e_description_type.h>
#include <d_file_description.h>
#include <d_event.h>
#include <d_mouse.h>
#include <c_base_container.h>
#include <c_label.h>

/* constructer destructer */

c_popup_read_dir_action::c_popup_read_dir_action(c_ncurses* ncurses,
						 c_event* event,
						 c_base_container* parent,
						 c_popup_manager* popup_manager) : c_popup(ncurses,
											   event,
											   parent,
											   popup_manager,
											   E_POPUP_READ_DIR_ACTION),
										   __v_menu_scroll(NULL),
										   __v_obj_linked(NULL),
										   __v_curr_dir(NULL),
										   __v_names_display(NULL),
										   __v_names_chdir(NULL),
										   __v_descriptions(NULL),
										   __v_nb_file(0),
										   __v_hidden_file(false)
{

}

c_popup_read_dir_action::~c_popup_read_dir_action(void)
{
	if (this->__v_curr_dir != NULL)
		free(this->__v_curr_dir);
	c_popup_read_dir_action::sf_clean_tab(&this->__v_names_display, this->__v_nb_file);
	c_popup_read_dir_action::sf_clean_tab(&this->__v_names_chdir, this->__v_nb_file);
	c_popup_read_dir_action::sf_clean_tab(&this->__v_descriptions, this->__v_nb_file);
}

/* public function */

bool	c_popup_read_dir_action::f_init_popup(e_read_dir_action action, const char* title,
					      int x, int y, int width, int height)
{
	this->__v_action = action;
	if (this->__f_init_my_obj(x, y, width, height) == false ||
	    this->f_init(title, x, y, width, height) == false ||
	    this->__f_init_keyboard_method() == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::f_treat_render(void)
{
	if (this->__f_render_popup() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_popup_read_dir_action::f_treat_keyboard(int key)
{
	int	ret;

	ret = this->_f_treat_keyboard_method(key);
	if (ret != 0)
		return ret;
	return this->_f_treat_event_popup_child(key);
}

bool	c_popup_read_dir_action::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
	{
		if (this->_v_event->f_mouse_button_used(D_LEFT_BUTTON_CLICKED) == true)
			if (this->__f_action_by_mouse() == false)
				return false;
	}
	else
		this->_f_close_popup();
	return true;
}

bool	c_popup_read_dir_action::f_event_enter(void)
{
	int	index;

	index = this->__v_menu_scroll->f_current_item_index();
	if (index == -1)
		return false;
	if (this->__f_manage_item_by_index(index) == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::f_event_see_hidden_files(void)
{
	this->__v_hidden_file = this->__v_hidden_file == true ? false : true;
	if (this->__f_update_data_menu(this->__v_hidden_file) == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::f_event_close(void)
{
	this->_f_close_popup();
	return true;
}

void	c_popup_read_dir_action::f_set_obj_linked(c_base_container* obj_linked)
{
	this->__v_obj_linked = obj_linked;
}

bool	c_popup_read_dir_action::sf_get_files_dir(const char* directory,
						  char*** names_display, char*** names_chdir, char*** descriptions, int* nb_file,
						  bool hiden_files, e_description_type description_type)
{
	if (c_popup_read_dir_action::__sf_nb_files_in_dir(directory, nb_file, hiden_files) == false ||
	    c_popup_read_dir_action::__sf_alloc_tabs(names_display, names_chdir, descriptions, *nb_file) == false)
		return false;
	c_popup_read_dir_action::__sf_set_to_null_all_ptr(names_display, names_chdir, descriptions, *nb_file);
	if (c_popup_read_dir_action::__sf_fill_tabs(directory, names_display, names_chdir, descriptions, *nb_file, hiden_files, description_type) == false)
	{
		c_popup_read_dir_action::sf_clean_tab(names_display, *nb_file);
		c_popup_read_dir_action::sf_clean_tab(names_chdir, *nb_file);
		c_popup_read_dir_action::sf_clean_tab(descriptions, *nb_file);
		return false;
	}
	return true;
}

void	c_popup_read_dir_action::sf_clean_tab(char*** tabs, int nb_file)
{
	int	i;

	if (*tabs == NULL)
		return ;
	i = 0;
	while (i < nb_file)
	{
		if ((*tabs)[i] != NULL)
		{
			delete [] (*tabs)[i];
			(*tabs)[i] = NULL;
		}
		++i;
	}
	delete [] *tabs;
	*tabs = NULL;
}

/* private function */

bool	c_popup_read_dir_action::__f_render_popup(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_POPUP)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_POPUP));
	if (tools::f_my_border(this->_v_window.f_get_window()) == ERR)
		return M_ERROR(false, "Error: tools::f_my_border(%p)\n", this->_v_window.f_get_window());
	if (this->_f_render_title() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::__f_init_my_obj(int x, int y, int width, int height)
{
	if (this->__f_reset_curr_dir() == false ||
	    c_popup_read_dir_action::sf_get_files_dir(this->__v_curr_dir, &this->__v_names_display, &this->__v_names_chdir, &this->__v_descriptions, &this->__v_nb_file, false) == false)
		return false;
	this->__v_menu_scroll = new (std::nothrow) c_menu_scroll(this->_v_ncurses, this->_v_event, this);
	if (this->__v_menu_scroll == NULL ||
	    this->__v_menu_scroll->f_init_menu(this->__v_names_display, this->__v_descriptions, x + 1, y + 1, width - 2, height - 5) == false ||
	    this->f_add_child(this->__v_menu_scroll) == false)
	{
		tools::f_delete_ptr(this->__v_menu_scroll);
		return false;
	}
	return true;
}

bool	c_popup_read_dir_action::__f_reset_curr_dir(void)
{
	if (this->__v_curr_dir != NULL)
		free(this->__v_curr_dir);
	this->__v_curr_dir = get_current_dir_name();
	if (this->__v_curr_dir == NULL)
		return M_ERROR_NO_ARGS(false, "Error: get_current_dir_name()\n");
	return true;
}

bool	c_popup_read_dir_action::__f_init_keyboard_method(void)
{
	if (this->_f_add_common_callback(D_ENTER, (t_common_callback)(&c_popup_read_dir_action::f_event_enter)) == false ||
	    this->_f_add_common_callback('h', (t_common_callback)(&c_popup_read_dir_action::f_event_see_hidden_files)) == false ||
	    this->_f_add_common_callback('o', (t_common_callback)(&c_popup_read_dir_action::f_event_close)) == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::__f_update_data_menu(bool hidden_files)
{
	c_popup_read_dir_action::sf_clean_tab(&this->__v_names_display, this->__v_nb_file);
	c_popup_read_dir_action::sf_clean_tab(&this->__v_names_chdir, this->__v_nb_file);
	c_popup_read_dir_action::sf_clean_tab(&this->__v_descriptions, this->__v_nb_file);
	if (this->__f_reset_curr_dir() == false ||
	    c_popup_read_dir_action::sf_get_files_dir(this->__v_curr_dir, &this->__v_names_display, &this->__v_names_chdir, &this->__v_descriptions, &this->__v_nb_file, hidden_files) == false ||
	    this->__v_menu_scroll->f_update_data_menu(this->__v_names_display, this->__v_descriptions) == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::__sf_nb_files_in_dir(const char* directory, int* nb_file, bool hiden_files)
{
	DIR*		dir = opendir(directory);
	struct dirent*	dirent = NULL;

	*nb_file = 0;
	if (dir == NULL)
		return M_ERROR(false, "Error: opendir(\"%s\")\n", directory);
	while ((dirent = readdir(dir)))
	{
		if (c_popup_read_dir_action::__sf_is_hidden_file(dirent->d_name) && hiden_files == false)
			continue;
		++(*nb_file);
	}
	if (errno == EBADF && dirent == NULL)
	{
		if (closedir(dir) == -1)
			return M_ERROR(false, "Error: closedir(%p)\n", dir);
		return false;
	}
	if (closedir(dir) == -1)
		return M_ERROR(false, "Error: closedir(%p)\n", dir);
	return true;
}

bool	c_popup_read_dir_action::__sf_is_hidden_file(const char* file)
{
	int	len = tools::f_strlen(file);

	if ((len == 1 && file[0] == '.') ||
	    (len == 2 && file[0] == '.' && file[1] == '.'))
		return false;
	if (file[0] == '.')
		return true;
	return false;
}

bool	c_popup_read_dir_action::__sf_alloc_tabs(char*** names_display, char*** names_chdir, char*** descriptions, int nb_file)
{
	*names_display = new (std::nothrow) char*[nb_file + 1];
	if (*names_display == NULL)
		return M_ERROR(false, "Error: operator new char*[%d]\n", nb_file + 1);
	*names_chdir = new (std::nothrow) char*[nb_file + 1];
	if (*names_chdir == NULL)
	{
		tools::f_delete_aptr(*names_display);
		return M_ERROR(false, "Error: operator new char*[%d]\n", nb_file + 1);
	}
	*descriptions = new (std::nothrow) char*[nb_file + 1];
	if (*descriptions == NULL)
	{
		tools::f_delete_aptr(*names_display);
		tools::f_delete_aptr(*names_chdir);
		return M_ERROR(false, "Error: operator new char*[%d]\n", nb_file + 1);
	}
	return true;
}

void	c_popup_read_dir_action::__sf_set_to_null_all_ptr(char*** names_display, char*** names_chdir, char*** descriptions, int nb_file)
{
	int	i;

	i = 0;
	++nb_file;
	while (i < nb_file)
	{
		(*names_display)[i] = NULL;
		(*names_chdir)[i] = NULL;
		(*descriptions)[i] = NULL;
		++i;
	}
}

bool	c_popup_read_dir_action::__sf_fill_tabs(const char* directory,
						char*** names_display, char*** names_chdir, char*** descriptions,
						int nb_file, bool hiden_files, e_description_type description_type)
{
	int		i = 0;
	DIR*		dir = opendir(directory);
	struct dirent*	dirent = NULL;
	struct stat	stat_info;

	if (dir == NULL)
		return M_ERROR(false, "Error: opendir(\"%s\")\n", directory);
	while ((dirent = readdir(dir)) && i < nb_file)
	{
		if (c_popup_read_dir_action::__sf_is_hidden_file(dirent->d_name) && hiden_files == false)
			continue;
		if (c_popup_read_dir_action::__sf_load_struct_stat(dirent->d_name, &stat_info) == false ||
		    c_popup_read_dir_action::__sf_write_name_to_chdir(names_chdir, i, dirent->d_name) == false ||
		    c_popup_read_dir_action::__sf_write_name_to_display(names_display, i, dirent->d_name) == false ||
		    c_popup_read_dir_action::__sf_replace_bad_character_and_write_description(names_display, descriptions, i,
											      dirent, &stat_info,
											      description_type) == false)
		{
			if (closedir(dir) == -1)
				return M_ERROR(false, "Error: closedir(%p)\n", dir);
			return false;
		}
		++i;
	}
	if (errno == EBADF && dirent == NULL)
	{
		if (closedir(dir) == -1)
			return M_ERROR(false, "Error: closedir(%p)\n", dir);
		return false;
	}
	if (closedir(dir) == -1)
		return M_ERROR(false, "Error: closedir(%p)\n", dir);
	return true;
}

bool	c_popup_read_dir_action::__sf_load_struct_stat(const char* name, struct stat* stat_info)
{
	if (stat(name, stat_info) == -1)
		return M_ERROR(false, "Error: stat(\"%s\", %p)\n", name, stat_info);
	return true;
}

bool	c_popup_read_dir_action::__sf_write_name_to_chdir(char*** names_chdir, int index, const char* name)
{
	(*names_chdir)[index] = tools::f_strdup(name);
	if ((*names_chdir)[index] == NULL)
		return M_ERROR(false, "Error: tools::f_strdup(\"%s\")\n", name);
	return true;
}

bool	c_popup_read_dir_action::__sf_write_name_to_display(char*** names_display, int index, const char* name)
{
	(*names_display)[index] = tools::f_strdup(name);
	if ((*names_display)[index] == NULL)
	{
		(*names_display)[index] = tools::f_strdup(D_ERROR_NAMES);
		if ((*names_display)[index] == NULL)
			return M_ERROR(false, "Error: tools::f_strdup(\"%s\")\n", D_ERROR_NAMES);
	}
	return true;
}

bool	c_popup_read_dir_action::__sf_replace_bad_character_and_write_description(char*** names_display, char*** descriptions, int index,
										  struct dirent* dirent, struct stat* stat_info,
										  e_description_type description_type)
{
	c_popup_read_dir_action::__sf_replace_no_valid_character((*names_display)[index]);
	if (c_popup_read_dir_action::__sf_set_description((*descriptions) + index, dirent, stat_info, description_type) == false)
		return false;
	c_popup_read_dir_action::__sf_replace_no_valid_character((*descriptions)[index]);
	return true;
}

bool	c_popup_read_dir_action::__sf_replace_no_valid_character(char* str)
{
	int	i;
	bool	fail = false;

	i = 0;
	while (str[i] != 0)
	{
		if (tools::f_printable_character(str[i]) == false)
		{
			str[i] = D_REPLACER_CHARACTER;
			if (fail == false)
				fail = true;
		}
		++i;
	}
	return fail;
}

bool	c_popup_read_dir_action::__sf_set_description(char** description, struct dirent* dirent, struct stat* stat_info,
						      e_description_type description_type)
{
	switch	(description_type)
	{
		case	E_SIZE_FILE_DESCRIPTION:
			if (c_popup_read_dir_action::__sf_set_description_size(description, stat_info) == false)
				return false;
			return true;
		case	E_FILE_TYPE_DESCRIPTION:
			if (c_popup_read_dir_action::__sf_set_description_file_type(description, dirent, stat_info) == false)
				return false;
			return true;
		default:
			return false;
	}
	return true;
}

bool	c_popup_read_dir_action::__sf_set_description_size(char** description, struct stat* stat_info)
{
	*description = tools::f_itoa(stat_info->st_size);
	if (*description == NULL)
	{
		*description = tools::f_strdup(D_ERROR_DESCRIPTION);
		if (*description == NULL)
			return M_ERROR(false, "Error: tools::f_strdup(\"%s\")\n", D_ERROR_DESCRIPTION);
	}
	return true;
}

bool	c_popup_read_dir_action::__sf_set_description_file_type(char** description, struct dirent* dirent, struct stat* stat_info)
{
	int	len;

	*description = NULL;
	if (stat_info->st_mode & S_IXUSR)
		*description = tools::f_strdup(D_EXECUTABLE_DESCRIPTION);
	else if (dirent->d_type == DT_REG)
	{
		len = tools::f_strlen(dirent->d_name);
		if (tools::f_strncmp(dirent->d_name + len - 3, ".ph", 3) == 0 ||
		    tools::f_strncmp(dirent->d_name + len - 3, ".PH", 3) == 0)
		{
			*description = tools::f_strdup(D_PH_FILE_DESCRIPTION);
		}
		else
			*description = tools::f_strdup(D_FILE_DESCRIPTION);
	}
	if (dirent->d_type == DT_DIR)
	{
		if (*description != NULL)
			delete [] *description;
		*description = tools::f_strdup(D_DIRECTORY_DESCRIPTION);
	}
	if (*description == NULL)
	{
		*description = tools::f_strdup(D_ERROR_DESCRIPTION);
		if (*description == NULL)
			return M_ERROR(false, "Error: tools::f_strdup(\"%s\")\n", D_ERROR_DESCRIPTION);
	}
	return true;
}

bool	c_popup_read_dir_action::__f_manage_item_by_index(int index)
{
	unsigned int	len;
	const char*	description;

	description = this->__v_menu_scroll->f_item_description_by_index(index);
	if (description == NULL)
		return false;
	len = tools::f_strlen(description);
	if (tools::f_strlen(D_DIRECTORY_DESCRIPTION) == len &&
	    tools::f_strncmp(description, D_DIRECTORY_DESCRIPTION, len) == 0)
	{
		if (this->__v_names_chdir[index] == NULL)
			return M_ERROR(false, "Error: this->__v_names_chdir[%d] = NULL\n", index);
		if (chdir(this->__v_names_chdir[index]) == -1)
			return M_ERROR(false, "Error: chdir(\"%s\")\n", this->__v_names_chdir[index]);
		if (this->__f_update_data_menu(this->__v_hidden_file) == false)
			return false;
	}
	else if (tools::f_strlen(D_PH_FILE_DESCRIPTION) == len &&
		 tools::f_strncmp(description, D_PH_FILE_DESCRIPTION, len) == 0 &&
		 this->__v_action == E_READ_DIR_ACTION_OPEN_PH_FILE)
	{
		if (this->__f_open_ph_file(this->__v_names_chdir[index]) == false)
			return false;
	}
	else if (tools::f_strlen(D_EXECUTABLE_DESCRIPTION) == len &&
		 tools::f_strncmp(description, D_EXECUTABLE_DESCRIPTION, len) == 0 &&
		 this->__v_action == E_READ_DIR_ACTION_BROWSE_EXECUTABLE)
	{
		if (this->__f_treat_executable(this->__v_names_chdir[index]) == false)
			return false;
	}
	return true;
}

bool	c_popup_read_dir_action::__f_action_by_mouse(void)
{
	int	index = this->__v_menu_scroll->f_get_index_where_clicked(this->_v_event->f_mouse_y());

	if (this->__f_manage_item_by_index(index) == false)
		return false;
	return true;
}

bool	c_popup_read_dir_action::__f_open_ph_file(const char* item_name)
{
	if (item_name == NULL)
		return M_ERROR_NO_ARGS(false, "Error: item_name = NULL\n");
	return true;
}

bool	c_popup_read_dir_action::__f_treat_executable(const char* item_name)
{
	if (item_name == NULL)
		return M_ERROR_NO_ARGS(false, "Error: item_name = NULL\n");
	if (this->__v_obj_linked != NULL && this->__v_obj_linked->f_get_obj_type() == E_LABEL)
	{
		if (((c_label*)(this->__v_obj_linked))->f_set_label(this->__v_curr_dir) == false)
			return false;
		((c_label*)(this->__v_obj_linked))->f_add_str_to_label("/");
		((c_label*)(this->__v_obj_linked))->f_add_str_to_label(item_name);
		this->_f_close_popup();
	}
	return true;
}
