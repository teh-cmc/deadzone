/**
 * This section will contain the executable informations
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

#ifndef __EXEC_INFOS_CLASS_HEADER__
#define __EXEC_INFOS_CLASS_HEADER__

#include <QGroupBox>
#include <list>

class	QGridLayout;
class	QHBoxLayout;
class	QPushButton;
class	QLineEdit;
class	QFileDialog;

namespace	pH
{
	class	c_profiler;
	class	c_exec_infos: public QGroupBox
	{
		Q_OBJECT
		public:
						c_exec_infos(QWidget* father);
			virtual			~c_exec_infos(void);
			bool			f_init(void);
			void			f_get_exec_infos(std::string* exec_infos);
		protected:
		private:
			QPushButton*		__v_launch_button;
			QPushButton*		__v_browse_button;
			QLineEdit*		__v_exec_path;
			QLineEdit*		__v_exec_args;
			QHBoxLayout*		__v_exec_layout;
			QGridLayout*		__v_layout;
			QFileDialog*		__v_file_dialog;

			bool			__f_init_layout(void);
			bool			__f_init_exec_path(void);
			bool			__f_init_args(void);
			bool			__f_init_launch_button(void);
			bool			__f_init_file_dialog(void);
		private slots:
			void			__f_browse(void);
			void			__f_selected_file(void);
	};
}

#endif
