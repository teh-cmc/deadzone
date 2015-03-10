/**
 * This class inherits from QRadioButton, and contains the profiler options
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

#ifndef __PROFILER_CLASS_HEADER__
#define __PROFILER_CLASS_HEADER__

#include <QRadioButton>

class	QListWidgetItem;

namespace	pH
{
	namespace	ph_tools
	{
		class	c_profiler;
	}

	class	c_profiler: public QRadioButton
	{
		Q_OBJECT
		public:
						c_profiler(ph_tools::c_profiler* profiler,
							   QListWidgetItem* item,
							   QWidget* father);
			virtual			~c_profiler(void);
			bool			f_toggled(void);
			ph_tools::c_profiler*	f_profiler(void);
			QListWidgetItem*	f_widget_item(void);
		signals:
			void			activated(void);
		protected:
		private:
			ph_tools::c_profiler*	__v_profiler;
			QListWidgetItem*	__v_item;
			bool			__v_toggled;
		private slots:
			void			__f_check_activation(void);
	};
}

#endif
