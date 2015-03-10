/**
 * Qt application class used to create the main window
 * Copyright (C) 2013  Hugo Nedelec <hugo.nedelec@gmail.com>
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

#ifndef __APPLICATION_CLASS_HEADER__
#define __APPLICATION_CLASS_HEADER__

#include <QApplication>

namespace	pH
{
	class	c_window;
	class	c_application: public QApplication
	{
		public:
					c_application(int& nb_args, char** args);
			virtual		~c_application(void);
			bool		f_init(void);
		protected:
		private:
			c_window*	__v_window;
			bool		__f_init_window(void);
	};
}

#endif
