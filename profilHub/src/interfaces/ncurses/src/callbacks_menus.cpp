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

#include <c_ncurses.h>
#include <tools.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <e_read_dir_action.h>
#include <fcntl.h>
#include <c_base_container.h>
#include <menu.h>
#include <c_menu_scroll.h>
#include <callbacks_menus.h>
#include <profilers.h>
#include <list>

/* callbacks file menu */

bool	open_menu_file_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	(void)my_obj;
	return ncurses->f_get_ui()->f_get_popup_manager()->f_add_popup_read_dir_action(E_READ_DIR_ACTION_OPEN_PH_FILE, "Open Ph file:      press 'h' to see hidden files");
}

bool	save_menu_file_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	(void)ncurses;
	(void)my_obj;
	return true;
}

bool	save_as_menu_file_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	(void)ncurses;
	(void)my_obj;
	return true;
}

bool	leave_menu_file_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	(void)my_obj;
	ncurses->f_stop_run();
	return true;
}

/* callbacks tools menu */

bool	options_tools_menu_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	(void)ncurses;
	(void)my_obj;
	return true;
}

/* callbacks help menu */

void*	open_web_window(void* arg)
{
	const char*		args[] = {"/usr/bin/xdg-open",
					  "https://github.com/reyclement/profilHub/issues/new",
					  0};
	int			fd = -1;
	int			fd1 = -1;
	int			fd2 = -1;
	bool			fail = false;
	c_env*			env = (c_env*)arg;
	s_manage_report*	manager = env->f_get_manager_report();

	manager->v_action = true;
	if (!(manager->v_pid = fork()))
	{
		if ((fd = open("/dev/null", O_RDWR)) == -1 ||
		    (fd1 = open("/dev/null", O_RDWR)) == -1 ||
		    (fd2 = open("/dev/null", O_RDWR)) == -1 ||
		     dup2(fd, 0) == -1 ||
		     dup2(fd1, 1) == -1||
		     dup2(fd2, 2) == -1)
			fail = true;
		if (fail == false && execve(*args, (char* const*)args, env->f_get_env()))
			fail = true;;
		close(fd);
		close(fd1);
		close(fd2);
		if (fail == true)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(manager->v_pid, NULL, 0);
	manager->v_action = false;
	return 0;
}

bool	report_help_menu_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	s_manage_report*	manager = ncurses->f_get_env()->f_get_manager_report();

	(void)my_obj;
	if (manager->v_action == true)
		return true;
	if (pthread_create(&manager->v_tid, NULL, &open_web_window, ncurses->f_get_env()) != 0)
		return false;
	return true;
}

bool	about_help_menu_callback(c_ncurses* ncurses, c_base_container* my_obj)
{
	(void)my_obj;
	return ncurses->f_get_ui()->f_get_popup_manager()->f_add_popup_text_zone("Toolbar menu:\n"
										 "\n"
										 "\tFile menu: F\n"
										 "\tTools menu: T\n"
										 "\tHelp menu: H\n"
										 "\n"
										 "Tabs:\n"
										 "\n"
										 "\tSwitch next tab: t\n"
										 "\tSwitch prev tab: T\n"
										 "\n"
										 "\tChoice executable tab:\n"
										 "\n"
										 "\t\tBrowse executable: B\n"
										 "\t\tLaunch analyze: L\n", "Keyboard Sorcuts:");
}

/* callbacks first tab menu */

bool	event_enter_names_profiler_menu(c_ncurses* ncurses, c_base_container* my_obj)
{
	if (display_little_cross((c_menu_scroll*)(my_obj)) == false ||
	    ncurses->f_get_ui()->f_get_init_ui()->f_update_profilers_infos_menu((c_menu_scroll*)(my_obj)) == false)
		return false;
	return true;
}

bool	display_little_cross(c_menu_scroll* my_menu)
{
	ITEM*	curr_item;

	if (my_menu->f_get_value_selectable() == true)
	{
		if (my_menu->f_get_multi_selection() == false && my_menu->f_set_value_all_item(false) == false)
				return false;
		curr_item = my_menu->f_current_item();
		if (curr_item == NULL)
			return M_ERROR_NO_ARGS(false, "Error: current item = NULL\n");
		if (my_menu->f_do_driver_action(E_SET_VALUE_DRIVER) == false)
			return false;
	}
	return true;
}
