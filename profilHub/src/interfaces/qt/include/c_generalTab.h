/**
 * General Tab of Option Popup
 * Copyright (C) 2013  Jean-Baptiste Noblot <jb.noblot@gmail.com>
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

#ifndef __GENERAL_TAB_CLASS_HEADER__
#define __GENERAL_TAB_CLASS_HEADER__

#include <QWidget>
#include <QString>

namespace	pH
{
	class	c_generalTab : public QWidget
	{
		Q_OBJECT
		public:
				c_generalTab(QWidget* father = NULL);
				~c_generalTab(void);
			bool	f_init(void);
		QString selectedLang;
		public slots:
			void	s_handleSelectionChanged(int index);
		protected:
		private:
	};
}

#endif
