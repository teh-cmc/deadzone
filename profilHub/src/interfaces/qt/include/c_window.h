/**
 * Main window for the profilHub Qt interface
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

#ifndef __WINDOW_CLASS_HEADER__
#define __WINDOW_CLASS_HEADER__

#include <QMainWindow>

namespace	pH
{
	class	c_tab;
	class	c_tab_displayer;
	class	c_central_widget;
	class	c_window: public QMainWindow
	{
		public:
						c_window(void);
			virtual			~c_window(void);
			bool			f_init(void);
		protected:
		private:
			c_central_widget*	__v_central_widget;

			void			__f_init_window_properties(void);
			void			__f_cleanup_window(void);
			bool			__f_init_menubar(void);
			bool			__f_init_central_widget(void);
	};
}

#endif
