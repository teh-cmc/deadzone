/**
 * This is the main content of profilHub, here the c_tab_displayer
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

#ifndef __MAIN_CONTENT_CLASS_HEADER__
#define __MAIN_CONTENT_CLASS_HEADER__

#include <QSplitter>

class	QGridLayout;

namespace	pH
{
	class	c_launching_options;
	class	c_tab_displayer;
	class	c_main_content: public QSplitter
	{
		public:
			c_tab_displayer*	v_tab_displayer;

						c_main_content(QWidget* father);
			virtual			~c_main_content(void);
			bool			f_init(void);
		protected:
		private:
			c_launching_options*	__v_launching_options;
			QGridLayout*		__v_layout;

			bool			__f_init_layout(void);
			bool			__f_init_tab_displayer(void);
			bool			__f_init_launching_options(void);
	};
}

#endif
