/**
 * This is the Callgraph tab class
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

#ifndef __TAB_CALLGRAPH_CLASS_HEADER__
#define __TAB_CALLGRAPH_CLASS_HEADER__

#include <c_tab.h>

namespace	pH
{
	class	c_tab_callgraph: public c_tab
	{
		public:
					c_tab_callgraph(QWidget* parent);
			virtual		~c_tab_callgraph(void);
			virtual bool	f_init(void);
		protected:
		private:
	};
}

#endif
