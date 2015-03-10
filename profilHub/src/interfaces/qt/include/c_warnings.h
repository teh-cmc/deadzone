/**
 * This is the area where the warnings are displayed
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

#ifndef __WARNINGS_CLASS_HEADER__
#define __WARNINGS_CLASS_HEADER__

#include <c_lister.h>

namespace	pH
{
	class	c_warning_lister;
	class	c_warnings: public c_lister
	{
		Q_OBJECT
		public:
						c_warnings(QWidget* father);
			virtual			~c_warnings(void);
			bool			f_init(void);
			c_warning_lister*	f_warning_lister(void);
		public slots:
			void			f_search(void);
		protected:
		private:
			c_warning_lister*	__v_warning_lister;

			bool			__f_init_warning_lister(void);
	};
}

#endif
