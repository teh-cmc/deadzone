/**
 * This is the warning class widget
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

#ifndef __WARNING_CLASS_HEADER__
#define __WARNING_CLASS_HEADER__

#include <QLabel>

class	QListWidgetItem;

namespace	pH
{
	class	c_warning: public QLabel
	{
		public:
						c_warning(QWidget* father, QListWidgetItem* widget_item, const char* title);
			virtual			~c_warning(void);
			bool			f_init(void);
			bool			f_here(void);
			bool			f_search(const char* search);
			bool			f_filter(const char* filter);
			bool			f_unfilter(const char* filter);
			QListWidgetItem*	f_widget_item(void);
		protected:
		private:
			bool			__v_here;
			QListWidgetItem*	__v_widget_item;
	};
}

#endif
