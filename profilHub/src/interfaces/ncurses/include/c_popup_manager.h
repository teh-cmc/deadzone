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

#ifndef __C_POPUP_MANAGER_H__
#define __C_POPUP_MANAGER_H__

#include <e_popup_type.h>
#include <vector>
#include <stdarg.h>
#include <e_read_dir_action.h>

class	c_event;
class	c_popup;
class	c_ncurses;
class	c_text_zone;
class	c_function_calltree;
class	c_base_container;
class	c_popup_manager
{
	public:
						c_popup_manager(c_ncurses* ncurses, c_event* event);
						~c_popup_manager(void);

			bool			f_there_is_a_popup(void);
			bool			f_treat_render(void);
			bool			f_treat_keyboard(int key);
			bool			f_treat_mouse(void);
			bool			f_add_popup_err_msg(const char* err_msg, ...);
			template <typename T>
			T			f_add_popup_err_msg(T ret, const char* err_msg, va_list* vargs);
			bool			f_add_popup_read_dir_action(e_read_dir_action action, const char* title, c_base_container* obj_linked = NULL);
			bool			f_add_popup_info_function(c_function_calltree* function);
			bool			f_add_popup_text_zone(const char* text, const char* title);
			bool			f_manage_resize(void);
	private:	
			c_popup*		__f_factory_popup(e_popup_type popup_type);
			void			__f_erase_popups_finish(void);
			int			__f_compute_size_popup(char axe);
			int			__f_decal_next_popup(void);
			c_text_zone*		__f_init_text_zone(const char* text, c_base_container* parent,
								   int x, int y, int w, int h);

			c_ncurses*		__v_ncurses;
			c_event*		__v_event;
			std::vector<c_popup*>	__v_popup_vect;
};

#endif
