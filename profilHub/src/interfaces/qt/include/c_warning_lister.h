/**
 * This is the section displaying the errors, by file/line
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

#ifndef __WARNING_LISTER_CLASS_HEADER__
#define __WARNING_LISTER_CLASS_HEADER__

#include <QListWidget>

namespace	pH
{
	class	c_warning;
	class	c_warning_lister: public QListWidget
	{
		Q_OBJECT
		public:
						c_warning_lister(QWidget* father);
			virtual			~c_warning_lister(void);
			bool			f_init(void);
			bool			f_add_warning(const char* warning);
			void			f_search(const char* search);
			void			f_filter(const char* filter);
			void			f_unfilter(const char* filter);
		public slots:
			void			f_remove_warning(void); /* May change lately when it will link to a function/file */
		protected:
		private:
			std::list<c_warning*>	__v_warnings;

			void			__f_delete_warnings(void);
	};
}

#endif
