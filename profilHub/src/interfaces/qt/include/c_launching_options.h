/**
 * This section will contain the profiler level and the exec path + options
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

#ifndef __LAUNCHING_OPTIONS_CLASS_HEADER__
#define __LAUNCHING_OPTIONS_CLASS_HEADER__

#include <QSplitter>

class	QHBoxLayout;

struct	launcher;

namespace	pH
{
	class	c_profiler;
	class	c_tab;
	class	c_output_infos;
	class	c_profilers_infos;
	class	c_exec_infos;
	class	c_launching_options: public QSplitter
	{
		Q_OBJECT
		public:
						c_launching_options(QWidget* father);
			virtual			~c_launching_options(void);
			bool			f_init(std::list<c_tab*>* tabs);
		protected:
		private:
			c_profilers_infos*	__v_profilers_infos;
			c_exec_infos*		__v_exec_infos;
			c_output_infos*		__v_output_infos;
			QHBoxLayout*		__v_layout;

			bool			__f_init_layout(void);
			bool			__f_init_profilers_infos(void);
			bool			__f_init_exec_infos(void);
			bool			__f_init_output_infos(std::list<c_tab*>*);
			bool			__f_browse_profilers(launcher*);
			bool			__f_add_profiler_options(launcher*, c_profiler*);
		private slots:
			void			__f_launch(void);
	};
}

#endif
