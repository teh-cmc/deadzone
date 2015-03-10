/**
 * This is the main widget, used as the main container
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

#ifndef __CENTRAL_WIDGET_CLASS_HEADER__
#define __CENTRAL_WIDGET_CLASS_HEADER__

#include <QSplitter>

class	QGridLayout;

namespace	pH
{
	class	c_listing_area;
	class	c_main_content;
	class	c_central_widget: public QSplitter
	{
		public:
						c_central_widget(QWidget* father);
			virtual			~c_central_widget(void);
			bool			f_init(void);
		protected:
		private:
			c_listing_area*		__v_listing_area;
			c_main_content*		__v_main_content;
			QGridLayout*		__v_layout;

			bool			__f_init_layout(void);
			bool			__f_create_listing_area(void);
			bool			__f_init_main_content(void);
	};
}

#endif
