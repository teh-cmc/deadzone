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

#include <c_error_manager.h>
#include <tools.h>

/* constructer deconstructer */

c_error_manager::c_error_manager(void) : __v_nb_curr_err(0)
{
	int	i;

	i = 0;
	while (i < D_NB_ERROR_MAX)
	{
		this->__v_error_vect[i] = E_NO_ERROR;
		++i;
	}
}

c_error_manager::~c_error_manager(void)
{

}

/* public function */

void	c_error_manager::f_add_error(e_error error)
{
	if (this->__v_nb_curr_err >= D_NB_ERROR_MAX)
		return ;
	this->__v_error_vect[this->__v_nb_curr_err] = error;
	++this->__v_nb_curr_err;
}

void	c_error_manager::f_print_all_errors(void)
{
	int	i;

	i = 0;
	while (i < this->__v_nb_curr_err)
	{
		this->__f_print_error(this->__v_error_vect[i]);
		++i;
	}
}

/* private function */

void	c_error_manager::__f_print_error(e_error error)
{
	switch	(error)
	{
		case	E_ERR_ALREADY_RUN:
			tools::f_print_err("the program is already run\n");
			return ;
		case	E_ERR_NCURSES_INIT:
			tools::f_print_err("fail ncurses init\n");
			return ;
		case	E_ERR_UI_INIT:
			tools::f_print_err("fail ui init\n");
			return ;
		case	E_ERR_NCURSES_CLOSE:
			tools::f_print_err("fail ncurses close\n");
			return ;
		default:
			return ;
	}
}
