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

#ifndef __C_FUNCTION_GRAPHIC_H__
#define __C_FUNCTION_GRAPHIC_H__

#include <vector>

class	c_graphic;
class	c_function_graphic
{
	public:
		typedef struct	s_pair
		{
			s_pair(int x, int y) : v_x(x), v_y(y) {}
			int	v_x;
			int	v_y;
		}	t_pair;
	public:
					c_function_graphic(c_graphic* graphic, char motif, int color_pair);
					~c_function_graphic(void);

		bool			f_init(const char* name);
		bool			f_add_point(int x, int y);
		const char*		f_get_name(void);
		std::vector<t_pair>*	f_get_point_vect(void);
		char			f_get_motif(void);
		int			f_get_color_pair(void);
	private:
		bool			__f_find_pair(int x);

		c_graphic*		__v_graphic;
		char*			__v_name;
		char			__v_motif;
		int			__v_color_pair;
		std::vector<t_pair>	__v_point_vect;
};

#endif
