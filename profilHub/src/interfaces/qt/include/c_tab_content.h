/**
 * This is the tab_content base class, meant to be inherited from
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

#ifndef __TAB_CONTENT_CLASS_HEADER__
#define __TAB_CONTENT_CLASS_HEADER__

#include <QTextBrowser>

namespace	pH
{
	class	c_tab_content: public QTextBrowser /* May change lately */
	{
		public:
					c_tab_content(QWidget* father);
			virtual		~c_tab_content(void);
			virtual bool	f_init(void) = 0;
			virtual bool	f_load(void) { return true; }
		protected:
		private:
	};
}

#endif
