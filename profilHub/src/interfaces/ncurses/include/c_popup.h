/**
 * Copyright (C) 2013 Jean Hasdenteufel <jeanhasdenteufel@gmail.com>
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

#ifndef __C_POPUP_H__
#define __C_POPUP_H__

#include <c_base_container.h>
#include <e_popup_type.h>

class	c_popup_manager;
class	c_popup : public c_base_container
{
	public:
		virtual				~c_popup(void);

			bool			f_init(const char* title, int x, int y, int width, int height);
		virtual	bool			f_treat_render(void) = 0;
		virtual	int			f_treat_keyboard(int key) = 0;
		virtual	bool			f_treat_mouse(void) = 0;
			bool			f_event_escape(void);
			bool			f_get_close(void);
	protected:
						c_popup(c_ncurses* ncurses,
							c_event* event,
							c_base_container* parent,
							c_popup_manager* popup_manager,
							e_popup_type popup_type);

			int			_f_treat_event_popup_child(int key);
			void			_f_close_popup(void);

			e_popup_type		_v_popup_type;
	private:
			bool			__f_init_event_method(void);

			c_popup_manager*	__v_popup_manager;
			bool			__v_close;
};

#endif
