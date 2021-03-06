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

#ifndef __ERROR_DISPLAYER_CLASS_HEADER__
#define __ERROR_DISPLAYER_CLASS_HEADER__

#include <QTextBrowser>

namespace	pH
{
	class	c_error_displayer: public QTextBrowser
	{
		public:
					c_error_displayer(QWidget* father);
			virtual		~c_error_displayer(void);
			bool		f_init(void);
		protected:
		private:
	};
}

#endif
