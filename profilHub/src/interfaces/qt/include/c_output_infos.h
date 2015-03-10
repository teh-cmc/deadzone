/**
 * This section is used to choose which tab has to be generated.
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

#ifndef __OUTPUT_INFOS_CLASS_HEADER__
#define __OUTPUT_INFOS_CLASS_HEADER__

#include <QGroupBox>

class	QVBoxLayout;

namespace	pH
{
	class	c_tab;
	class	c_output_option;
	class	c_output_infos: public QGroupBox
	{
		public:
								c_output_infos(QWidget* father);
			virtual					~c_output_infos(void);
			bool					f_init(std::list<c_tab*>* list);
			inline std::vector<c_output_option*>*	f_options(void) { return &this->__v_output_options; }
		protected:
		private:
			std::vector<c_output_option*>		__v_output_options;
			QVBoxLayout*				__v_layout;

			bool					__f_create_single_output_option(std::list<c_tab*>*, const char*);
			void					__f_destroy_output_options(void);
	};
}

#endif
