/**
 * This class is a calltree item, that we can interact with.
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

#ifndef __CALLTREE_ITEM_CLASS_HEADER__
#define __CALLTREE_ITEM_CLASS_HEADER__

#include <QTreeWidgetItem>

class	QTreeWidget;

namespace	pH
{
	namespace	ph_tools
	{
		class	c_calltree_element;
	}
	class	c_calltree_item: public QTreeWidgetItem
	{
		public:
							c_calltree_item(c_calltree_item* father, const char* value);
							c_calltree_item(QTreeWidget* father, const char* value);
			virtual				~c_calltree_item(void);
			bool				f_load(ph_tools::c_calltree_element* element);
		protected:
		private:
			const char*			__v_value;
			std::vector<c_calltree_item*>	__v_childs;

			void				__f_kill_childs(void);
			bool				__f_load_element(ph_tools::c_calltree_element*);
	};
}

#endif
