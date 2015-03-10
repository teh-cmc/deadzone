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

#ifdef	D_DEBUG_ON

#include <stdio.h>

FILE*	g_file_debug = NULL;

#endif

#include <c_ncurses.h>
#include <e_error.h>
#include <tools.h>
#include <d_term.h>

/* constructer desctructer */

c_ncurses::c_ncurses(void) : __v_ui(this),
			     __v_ncurses_init(false),
			     __v_run(false)
{

}

c_ncurses::~c_ncurses(void)
{

}

/* public function */

bool	c_ncurses::f_init(int argc, char** argv, char** env)
{
	(void)argc;
	(void)argv;
	if (this->__v_run == true)
		return this->f_error(E_ERR_ALREADY_RUN, false);
	if (initscr() == NULL)
		return this->f_error(E_ERR_NCURSES_INIT, false);
	this->__v_ncurses_init = true;
	if (start_color() == ERR ||
	    curs_set(0) == ERR ||
	    cbreak() == ERR ||
	    noecho() == ERR ||
	    nodelay(stdscr, FALSE) == ERR)
		return this->f_error(E_ERR_NCURSES_INIT, false);
	if (this->__v_env.f_init(env) == false ||
	    this->__v_ui.f_init() == false)
		return this->f_error(E_ERR_UI_INIT, false);
	this->__v_run = true;
	if (this->__v_ui.f_init_first_container_focused() == false)
		return false;
	return true;
}

int	c_ncurses::f_close(int ret)
{
	this->__v_ui.f_close();
	if (this->__v_ncurses_init == true && endwin() == ERR)
		return this->f_error(E_ERR_NCURSES_CLOSE, -1);
#ifdef	D_DEBUG_ON
	if (g_file_debug != NULL && fclose(g_file_debug) != 0)
		return M_ERROR_NO_ARGS(-1, "Error: fclose()\n");
#endif
	this->__v_error_manager.f_print_all_errors();
	return ret;
}

void	c_ncurses::f_stop_run(void)
{
	this->__v_run = false;
}

bool	c_ncurses::f_run(void)
{
	while (this->__v_run == true)
	{
		if (refresh() == ERR)
			M_ERROR_VOID_NO_ARGS("Error: refresh()\n");
		if (this->__v_ui.f_treat() == false)
		{}
	}
	return true;
}

bool	c_ncurses::f_get_run(void)
{
	return this->__v_run;
}

c_ui*	c_ncurses::f_get_ui(void)
{
	return &this->__v_ui;
}

c_env*	c_ncurses::f_get_env(void)
{
	return &this->__v_env;
}

template <typename T>
T	c_ncurses::f_error(e_error error, T ret)
{
	this->__v_error_manager.f_add_error(error);
	return ret;
}
