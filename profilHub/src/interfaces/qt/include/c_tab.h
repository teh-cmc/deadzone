/**
 * Tabs base class, meant to be inherited from
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

#ifndef __TAB_CLASS_HEADER__
#define __TAB_CLASS_HEADER__

#include <c_tab_header.h>

namespace	pH
{
	class	c_tab_header;
	class	c_tab_content;
	class	c_tab
	{
		public:
					c_tab(QWidget* parent = NULL);
			virtual		~c_tab(void);
			virtual bool	f_init(void) = 0;
			void		show(void);
			void		hide(void);
			bool		f_here(void);
			void		f_here(bool here);
			const char*	f_value(void);
			bool*		f_activated(void);
			c_tab_header*	f_tab_header(void);
			c_tab_content*	f_tab_content(void);
		protected:
			const char*	_v_value;
			c_tab_header*	_v_tab_header;
			c_tab_content*	_v_tab_content;
			QWidget*	_v_father;

			bool		_f_init_header(const char* label_title, const char* image_path, e_tab_header_state state);
			bool		_f_init_content(c_tab_content* tab_content);
		private:
			bool		__v_here;
			bool		__v_activated;
	};
}

#endif
