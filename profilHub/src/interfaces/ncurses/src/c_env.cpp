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

#include <c_env.h>
#include <stdlib.h>
#include <d_term.h>
#include <tools.h>

/* constructer destructer */

c_env::c_env(void)
{

}

c_env::~c_env(void)
{

}

/* public function */

bool	c_env::f_init(char** env)
{
	this->__v_env = env;
	if (this->__f_set_term_type() == false ||
	    this->__f_set_nb_color() == false)
		return false;
	return true;
}

char**	c_env::f_get_env(void)
{
	return this->__v_env;
}

s_manage_report*	c_env::f_get_manager_report(void)
{
	return &this->__v_manager_report;
}

int	c_env::f_get_nb_color(void)
{
	return this->__v_nb_color;
}

/* private function */

bool	c_env::__f_set_term_type(void)
{
	const char*	term = getenv("COLORTERM");

	if (term == NULL)
		this->__v_term_type = E_XTERM;
	else
	{
		unsigned int	len = tools::f_strlen(term);

		if (len == tools::f_strlen(D_GNOME_TERM) &&
		    tools::f_strcmp(term, D_GNOME_TERM) == 0)
			this->__v_term_type = E_GNOME_TERM;
		else
			this->__v_term_type = E_AN_OTHER_TERM;
	}
	return true;
}

bool	c_env::__f_set_nb_color(void)
{
	unsigned int	len;
	const char*	term = getenv("TERM");

	if (term == NULL)
		return false;
	len = tools::f_strlen(term);
	if (len == tools::f_strlen(D_XTERM_256_COLOR) &&
	    tools::f_strcmp(term, D_XTERM_256_COLOR) == 0)
		this->__v_nb_color = D_256_COLOR;
	else
		this->__v_nb_color = D_8_COLOR;
	return true;
}
