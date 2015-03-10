/**
 * This is the right part of profilHub, where the listing are displayed
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

#ifndef __LISTING_AREA_CLASS_HEADER__
#define __LISTING_AREA_CLASS_HEADER__

#include <QSplitter>

class	QVBoxLayout;

namespace	pH
{
	class	c_warnings;
	class	c_filters;
	class	c_listing_area: public QSplitter
	{
		public:
					c_listing_area(QWidget* father);
			virtual		~c_listing_area(void);
			bool		f_init(void);
		protected:
		private:
			QVBoxLayout*	__v_layout;
			c_warnings*	__v_warnings;
			c_filters*	__v_filters;

			bool		__f_init_layout(void);
			bool		__f_init_warnings(void);
			bool		__f_init_filters(void);
	};
}

#endif
