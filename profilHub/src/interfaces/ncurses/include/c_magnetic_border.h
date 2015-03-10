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

#ifndef __C_BORDER_FIX_H__
#define __C_BORDER_FIX_H__

class	c_magnetic_border
{
	public:
			c_magnetic_border(bool top = false, bool bot = false, bool left = false, bool right = false);
			~c_magnetic_border(void);

		void	f_set(bool top, bool bot, bool left, bool right);

		bool	v_top;
		bool	v_bot;
		bool	v_left;
		bool	v_right;
};

#endif
