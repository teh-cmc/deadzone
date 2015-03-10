/**
 * This is the class used to render the different tabs
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

#ifndef __TAB_DISPLAYER_CLASS_HEADER__
#define __TAB_DISPLAYER_CLASS_HEADER__

#include <QWidget>
#include <list>
#include <vector>

class	QGridLayout;
class	QHBoxLayout;

namespace	pH
{
	class	c_output_option;
	class	c_tab;
	class	c_window;
	class	c_tab_displayer: public QWidget
	{
		public:
						c_tab_displayer(QWidget* father);
			virtual			~c_tab_displayer(void);
			bool			f_init(void);
			void			f_load_tabs(std::vector<c_output_option*>* vector);
			void			f_close_tab(c_tab* tab);
			void			f_select_tab(c_tab* tab);
			void			f_change_tab_visibility(const char* id, bool value);
			std::list<c_tab*>*	f_tabs(void);
		protected:
		private:
			std::list<c_tab*>	__v_tabs;
			QGridLayout*		__v_layout;
			QHBoxLayout*		__v_tab_layout;
			c_tab*			__v_current_tab;

			bool			__f_create_single_tab(c_tab*);
			bool			__f_init_layout(void);
			void			__f_add_tab(c_tab*);
			void			__f_set_content(c_tab*);
			void			__f_delete_tabs(void);
	};
}

#endif
