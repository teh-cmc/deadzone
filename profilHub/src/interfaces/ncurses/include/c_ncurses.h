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

#ifndef __C_NCURSES_H__
#define __C_NCURSES_H__

#include <c_event.h>
#include <c_ui.h>
#include <c_env.h>
#include <e_error.h>
#include <c_error_manager.h>

class	c_ncurses
{
	public:
					c_ncurses(void);
					~c_ncurses(void);

		bool			f_init(int argc, char** argv, char** env);
		int			f_close(int ret);
		void			f_stop_run(void);
		bool			f_run(void);
		bool			f_get_run(void);
		c_ui*			f_get_ui(void);
		c_env*			f_get_env(void);
		template <typename T>
		T			f_error(e_error error, T ret);
	private:
		c_env			__v_env;
		c_ui			__v_ui;
		bool			__v_ncurses_init;
		bool			__v_run;
		c_error_manager		__v_error_manager;
};

#endif
