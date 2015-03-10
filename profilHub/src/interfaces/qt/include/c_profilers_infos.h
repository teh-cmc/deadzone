/**
 * This section will contain the profiler informations
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

#ifndef __PROFILERS_INFOS_CLASS_HEADER__
#define __PROFILERS_INFOS_CLASS_HEADER__

#include <QGroupBox>
#include <stdint.h>
#include <vector>

class	QHBoxLayout;
class	QCheckBox;
class	QListWidget;
class	QListWidgetItem;
class	QButtonGroup;
class	QSignalMapper;

namespace	pH
{
	namespace	ph_tools
	{
		class	c_profiler;
		class	c_profiler_option;
	}
	class	c_profiler;

	class	c_profilers_infos: public QGroupBox
	{
		Q_OBJECT
		public:
								c_profilers_infos(QWidget* father);
			virtual					~c_profilers_infos(void);
			std::list<c_profiler*>*			f_profilers(void);
			bool					f_init(void);
		protected:
		private:
			std::list<c_profiler*>			__v_choices;
			std::list<QListWidgetItem*>		__v_options;
			QButtonGroup*				__v_button_group;
			QHBoxLayout*				__v_layout;
			QListWidget*				__v_profilers;
			QListWidget*				__v_profilers_options;
			QSignalMapper*				__v_signal_mapper;
			c_profiler*				__v_selected_profiler;

			bool					__f_init_layout(void);
			bool					__f_init_choices(void);
			bool					__f_add_choice(ph_tools::c_profiler*);
			bool					__f_init_scrollable_areas(void);
			bool					__f_destroy_vector_elements(std::vector<ph_tools::c_profiler*>*, uint32_t);
			void					__f_add_option(ph_tools::c_profiler_option*);
			void					__f_destroy_old_options(void);
			void					__f_destroy_choices(void);
		private slots:
			void					__f_display_profiler_options(void);
			void					__f_select_option(void);
	};
}

#endif
