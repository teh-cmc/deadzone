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

#ifndef __C_LABEL_H__
#define __C_LABEL_H__

#include <c_base_container.h>
#include <e_label_type.h>
#include <d_label.h>

class	c_label : public c_base_container
{
	public:
					~c_label(void);

		bool			f_init(const char* title, int x, int y, int width, int height);
		bool			f_treat_render(void);
		int			f_treat_keyboard(int key);
		bool			f_treat_mouse(void);
		bool			f_event_key_left(void);
		bool			f_event_key_right(void);
		bool			f_event_backspace(void);
		bool			f_event_escape(void);
		bool			f_not_focus_anymore(void);
		bool			f_set_label(const char* str);
		bool			f_add_str_to_label(const char* str);
		const char*		f_get_content(void);
		const char*		f_get_default_buffer(void);
		bool			f_clean_buffer(void);
		bool			f_init_default_buffer(const char* default_buffer);
		void			f_push_default_buffer_in_buffer(void);
		void			f_set_not_focus_anymore_callback(t_single_callback callback);
		void			f_set_real_time_callback(t_single_callback callback);
	protected:
					c_label(c_ncurses* ncurses,
						c_event* event,
						c_base_container* parent,
						e_label_type label_type);

		bool			_f_draw_label(void);
		bool			_f_init_default_buffer_and_size_buffer(const char* default_buffer, int* size_buffer);
		bool			_f_init_buffer(int size_buffer);
		bool			_f_init_event_method(void);

		bool			_v_negative_nbr;
	private:
		bool			__f_manage_left_click(void);
		bool			__f_add_char_to_buffer(int key);
		void			__f_insert_to_buffer(int key, int pos);
		void			__f_decal_left_buffer_pos_to_pos(int pos_moved, int pos_dest);
		bool			__f_clean_buffer_if_is_default_buffer(void);
		bool			__f_erase_text(void);
		bool			__f_draw_cursor(void);
		bool			__f_is_numeric_str(const char* str);
		bool			__f_is_numeric_char(int key);

		char*			__v_buffer;
		char*			__v_default_buffer;
		int			__v_size_buffer;
		bool			__v_default_buffer_use;
		e_label_type		__v_label_type;
		bool			__v_i_am_focus;
		unsigned int		__v_cursor_position;
		int			__v_buffer_position;
		unsigned int		__v_decal_buffer;
		t_single_callback	__v_not_focus_anymore_callback;
		t_single_callback	__v_real_time_callback;
};

#endif
