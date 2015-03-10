/**
 * This is the search bar, containing the search_area and the search_button
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

#ifndef __SEARCH_BAR_CLASS_HEADER__
#define __SEARCH_BAR_CLASS_HEADER__

#include <QHBoxLayout>
#include <QFrame>

namespace	pH
{
	class	c_img;
	class	c_search_area;
	class	c_search_bar: public QFrame
	{
		Q_OBJECT
		public:
						c_search_bar(QWidget* father);
			virtual			~c_search_bar(void);
			bool			f_init(void);
			c_img*			f_button(void);
			c_search_area*		f_text(void);
		protected:
		private:
			c_search_area*		__v_search_area;
			c_img*			__v_search_button;
			QHBoxLayout*		__v_layout;

			bool			__f_init_search_area(void);
			bool			__f_init_search_button(void);
			bool			__f_init_layout(void);
	};
}

#endif
