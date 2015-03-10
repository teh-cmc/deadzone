/**
 * This is the content of the calltree tab
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

#ifndef __TAB_CONTENT_CALLTREE_CLASS_HEADER__
#define __TAB_CONTENT_CALLTREE_CLASS_HEADER__

#include <c_tab_content.h>

class	QVBoxLayout;
class	QTreeWidget;

namespace	pH
{
	namespace	ph_tools
	{
		class	c_calltree;
		class	c_calltree_element;
	}
	class	c_calltree_item;
	class	c_tab_content_calltree: public c_tab_content
	{
		public:
						c_tab_content_calltree(QWidget* father);
			virtual			~c_tab_content_calltree(void);
			virtual bool		f_init(void);
			virtual bool		f_load(void);
		protected:
		private:
			ph_tools::c_calltree*	__v_calltree;
			c_calltree_item*	__v_program_item;
			QVBoxLayout*		__v_layout;
			QTreeWidget*		__v_tree;

			bool			__f_load_tree(ph_tools::c_calltree_element*);
			bool			__f_init_tree(void);
			bool			__f_init_calltree(void);
	};
}

#endif
