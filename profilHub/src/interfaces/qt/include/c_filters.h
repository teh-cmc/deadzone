/**
 * This is the area where the filters will be displayed
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

#ifndef __FILTERS_CLASS_HEADER__
#define __FILTERS_CLASS_HEADER__

#include <c_lister.h>

namespace	pH
{
	class	c_filter_lister;
	class	c_warning_lister;
	class	c_filters: public c_lister
	{
		Q_OBJECT
		public:
						c_filters(QWidget* father);
			virtual			~c_filters(void);
			bool			f_init(c_warning_lister* warning_lister);
		public slots:
			void			f_add_filter(void);
		protected:
		private:
			c_filter_lister*	__v_filter_lister;

			bool			__f_init_filter_lister(c_warning_lister* warning_lister);
	};
}

#endif
