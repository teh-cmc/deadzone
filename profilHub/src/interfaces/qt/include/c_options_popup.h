/**
 * BlaBla Description
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

#ifndef __OPTION_POPUP_CLASS_HEADER__
#define __OPTION_POPUP_CLASS_HEADER__

#include <QDialog>
#include <QLabel>
#include <QTabWidget>
#include <QListWidget>
#include <c_generalTab.h>


namespace	pH
{
	class	c_options_popup : public QDialog
	{
		typedef struct
		{
			c_generalTab*	gT;
		} t_environment_tabs;

		Q_OBJECT
		public :
				c_options_popup(QWidget* father = NULL);
			virtual	~c_options_popup(void);
			bool	f_init(void);
			
		public slots:
			void	s_clicked_option(void);
			void	s_accepted(void);
			void	s_rejected(void);
		protected :
		private :
			bool		__f_environmentOption(void);

            QLabel*             labelTitle;
            QFrame*             panel;
            QTabWidget*         tab;
            QListWidget*        listOption;
			t_environment_tabs	teb;
	};
}

#endif
