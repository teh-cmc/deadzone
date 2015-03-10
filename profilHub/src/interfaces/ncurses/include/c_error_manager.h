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

#ifndef __C_ERROR_MANAGER_H__
#define __C_ERROR_MANAGER_H__

#include <e_error.h>

#define D_NB_ERROR_MAX	16

class	c_error_manager
{
	public:
			c_error_manager(void);
			~c_error_manager(void);

		void	f_add_error(e_error error);
		void	f_print_all_errors(void);
	private:
		void	__f_print_error(e_error error);

		e_error	__v_error_vect[D_NB_ERROR_MAX];
		int	__v_nb_curr_err;
};

#endif
