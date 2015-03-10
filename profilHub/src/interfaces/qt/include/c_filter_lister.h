/**
 * This is the area where every filters will be displayed
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

#ifndef __FILTER_LISTER_CLASS_HEADER__
#define __FILTER_LISTER_CLASS_HEADER__

#include <QListWidget>

class	QStackedLayout;

namespace	pH
{
	class	c_filter;
	class	c_warning_lister;
	class	c_filter_lister: public QListWidget
	{
		Q_OBJECT
		public:
						c_filter_lister(QWidget* father, c_warning_lister* warning_lister);
			virtual			~c_filter_lister(void);
			bool			f_init(void);
			bool			f_add_filter(const char* filter);
		public slots:
			void			f_remove_filter(void);
		protected:
		private:
			std::list<c_filter*>	__v_filter_list;
			c_warning_lister*	__v_warning_lister;

			void			__f_delete_filters(void);
			bool			__f_filter_already_exists(const char* title);
	};
}

#endif
