/**
 * This class inherits from QLabel, and is used to manage our own tab labels
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

#ifndef __TAB_LABEL_CLASS_HEADER__
#define __TAB_LABEL_CLASS_HEADER__

#include <QLabel>

namespace	pH
{
	class	c_tab;
	class	c_tab_label: public QLabel
	{
		public:
			c_tab*		v_tab;

					c_tab_label(QString title, QWidget* father);
			virtual		~c_tab_label(void);
			void		mousePressEvent(QMouseEvent*);
			void		show(void);
			void		hide(void);
		protected:
		private:
	};
}

#endif
