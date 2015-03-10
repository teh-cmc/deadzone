/**
 * This class will be used to know whether or not a tab has to be generated.
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

#ifndef __OUTPUT_OPTION_CLASS_HEADER__
#define __OUTPUT_OPTION_CLASS_HEADER__

#include <QCheckBox>

namespace	pH
{
	class	c_tab;
	class	c_output_option: public QCheckBox
	{
		Q_OBJECT
		public:
						c_output_option(QWidget* father, const char* value);
			virtual			~c_output_option(void);
			bool			f_init(std::list<c_tab*>* tabs);
			inline const char*	f_value(void) const { return this->__v_value; }
			inline bool		f_activated(void) const { return *this->__v_activated; }
		protected:
		private:
			const char*		__v_value;
			bool*			__v_activated;
		public slots:
			void			__f_activation(void);
	};
}

#endif
