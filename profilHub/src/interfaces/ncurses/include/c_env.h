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

#ifndef __C_ENV_H__
#define __C_ENV_H__

#include <e_term.h>
#include <vector>
#include <sys/wait.h>
#include <pthread.h>

struct	s_manage_report
{
	pid_t		v_pid;
	pthread_t	v_tid;
	bool		v_action;

	s_manage_report(void) : v_pid(-1),
				v_action(false)
	{
		
	}
	~s_manage_report(void)
	{
		if (this->v_action == true)
		{
			kill(this->v_pid, SIGKILL);
			pthread_join(this->v_tid, 0);
		}
	}
};

class	c_env
{
	public:
					c_env(void);
					~c_env(void);

		bool			f_init(char** env);
		char**			f_get_env(void);
		s_manage_report*	f_get_manager_report(void);
		int			f_get_nb_color(void);
	private:
		bool			__f_set_term_type(void);
		bool			__f_set_nb_color(void);
		char**			__v_env;
		s_manage_report		__v_manager_report;

		e_term			__v_term_type;
		int			__v_nb_color;
};

#endif
