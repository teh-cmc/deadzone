/**
 * This is the c_lister based class, meant to be inherited from
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

#ifndef __LISTER_CLASS_HEADER__
#define __LISTER_CLASS_HEADER__

#include <QFrame>

class	QVBoxLayout;

namespace	pH
{
	class	c_error_displayer;
	class	c_filter_displayer;
	class	c_search_bar;

	class	c_lister: public QFrame
	{
		Q_OBJECT
		public:
					c_lister(QWidget* father);
			virtual		~c_lister(void);
		protected:
			c_search_bar*	_v_search_bar;
			QVBoxLayout*	_v_layout;

			bool		_f_init(void);
		private:
			bool		__f_init_layout(void);
			bool		__f_init_search_bar(void);
	};
}

#endif
