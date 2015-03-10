/**
 * This is a search area
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

#ifndef __SEARCH_AREA_CLASS_HEADER__
#define __SEARCH_AREA_CLASS_HEADER__

#include <QLineEdit>

class	QKeyEvent;

namespace	pH
{
	class	c_search_area: public QLineEdit
	{
		Q_OBJECT
		public:
					c_search_area(QWidget* father);
			virtual		~c_search_area(void);
			void		keyPressEvent(QKeyEvent* key_event);
			bool		f_init(void);
		signals:
			void		submit(void);
			void		key_pressed(void);
			void		key_suppressed(void);
		protected:
		private:
	};
}

#endif
