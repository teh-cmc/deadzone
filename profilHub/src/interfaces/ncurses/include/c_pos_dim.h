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

#ifndef __C_POS_DIM_H__
#define __C_POS_DIM_H__

#include <c_pos.h>
#include <c_dim.h>

class	c_pos_dim
{
	public:
			c_pos_dim(void);
			~c_pos_dim(void);

		void	f_set(int x, int y, int w, int h);

		c_pos	v_pos;
		c_dim	v_dim;
};

#endif
