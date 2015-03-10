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

#ifndef __C_POPUP_READ_DIR_ACTION_H__
#define __C_POPUP_READ_DIR_ACTION_H__

#include <c_popup.h>
#include <e_read_dir_action.h>
#include <e_description_type.h>

class	c_menu_scroll;
class	c_base_container;
class	c_popup_read_dir_action : public c_popup
{
	public:
						c_popup_read_dir_action(c_ncurses* ncurses,
									c_event* event,
									c_base_container* parent,
									c_popup_manager* popup_manager);
						~c_popup_read_dir_action(void);

			bool			f_init_popup(e_read_dir_action action, const char* title,
							     int x, int y, int width, int height);
			bool			f_treat_render(void);
			int			f_treat_keyboard(int key);
			bool			f_treat_mouse(void);
			bool			f_event_enter(void);
			bool			f_event_see_hidden_files(void);
			bool			f_event_close(void);
			void			f_set_obj_linked(c_base_container* obj_linked);
		static	bool			sf_get_files_dir(const char* directory,
								 char*** names_display, char*** names_chdir, char*** descriptions, int* nb_file,
								 bool hiden_files = false,
								 e_description_type description_type = E_FILE_TYPE_DESCRIPTION);
		static	void			sf_clean_tab(char*** names, int nb_file);
	private:
			bool			__f_render_popup(void);
			bool			__f_init_my_obj(int x, int y, int width, int height);
			bool			__f_reset_curr_dir(void);
			bool			__f_init_keyboard_method(void);
			bool			__f_update_data_menu(bool hidden_files = false);
		static	bool			__sf_nb_files_in_dir(const char* directory, int* nb_file, bool hiden_files);
		static	bool			__sf_is_hidden_file(const char* file);
		static	bool			__sf_alloc_tabs(char*** names_display, char*** names_chdir, char*** descriptions, int nb_file);
		static	void			__sf_set_to_null_all_ptr(char*** names_display, char*** names_chdir, char*** descriptions, int nb_file);
		static	bool			__sf_fill_tabs(const char* directory,
							       char*** names_display, char*** names_chdir, char*** descriptions,
							       int nb_file, bool hiden_files, e_description_type description_type);
		static	bool			__sf_load_struct_stat(const char* name, struct stat* stat_info);
		static	bool			__sf_write_name_to_chdir(char*** names_chdir, int index, const char* name);
		static	bool			__sf_write_name_to_display(char*** names_display, int index, const char* name);
		static	bool			__sf_replace_bad_character_and_write_description(char*** names_display, char*** descriptions, int index,
												 struct dirent* dirent, struct stat* stat_info,
												 e_description_type description_type);
		static	bool			__sf_replace_no_valid_character(char* str);
		static	bool			__sf_set_description(char** description, struct dirent* dirent, struct stat* stat_info,
								     e_description_type description_type);
		static	bool			__sf_set_description_size(char** description, struct stat* stat_info);
		static	bool			__sf_set_description_file_type(char** description, struct dirent* dirent, struct stat* stat_info);
			bool			__f_manage_item_by_index(int index);
			bool			__f_action_by_mouse(void);
			bool			__f_open_ph_file(const char* item_name);
			bool			__f_treat_executable(const char* item_name);

			e_read_dir_action	__v_action;
			c_menu_scroll*		__v_menu_scroll;
			c_base_container*	__v_obj_linked;
			char*			__v_curr_dir;
			char**			__v_names_display;
			char**			__v_names_chdir;
			char**			__v_descriptions;
			int			__v_nb_file;
			bool			__v_hidden_file;
};

#endif
