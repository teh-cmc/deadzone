/**
 * Menubar class for the profilHub Qt interface
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

#ifndef __TOOLBAR_CLASS_HEADER__
#define __TOOLBAR_CLASS_HEADER__

#include <QWidget>
#include <QMenuBar>


namespace	pH
{
	class	c_menubar : public QWidget
	{
		Q_OBJECT
		public :
					c_menubar(QWidget* father = NULL);
			virtual		~c_menubar(void);
			bool		f_init(void);
			QMenuBar*	f_getMenubar(void) const;

		public	slots:
			void	s_openFile(void);
			void	s_saveAsFile(void);
			void	s_exitApp(void);
			
			void	s_setting(void);
			void	s_bug_report(void);
			void	s_about(void);

		protected :

		private :
			bool		__f_fileMenu(QMenuBar* bar);
			bool		__f_helpMenu(QMenuBar* bar);
			bool		__f_toolMenu(QMenuBar* bar);
			QMenuBar*	__v_menubar;
	};
}

#endif

