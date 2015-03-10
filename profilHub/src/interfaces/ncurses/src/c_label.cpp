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

#include <c_label.h>
#include <d_color_ui.h>
#include <tools.h>
#include <c_event.h>
#include <d_event.h>
#include <d_mouse.h>

/* constructer destructer */

c_label::c_label(c_ncurses* ncurses,
		 c_event* event,
		 c_base_container* parent,
		 e_label_type label_type) : c_base_container(E_LABEL,
							     ncurses,
							     event,
							     parent,
							     true,
							     false,
							     true,
							     true),
					    _v_negative_nbr(true),
					    __v_buffer(NULL),
					    __v_default_buffer(NULL),
					    __v_size_buffer(0),
					    __v_default_buffer_use(false),
					    __v_label_type(label_type),
					    __v_i_am_focus(false),
					    __v_cursor_position(0),
					    __v_buffer_position(0),
					    __v_decal_buffer(0),
					    __v_not_focus_anymore_callback(NULL),
					    __v_real_time_callback(NULL)
{
	this->_v_window.f_get_magnetic_border()->f_set(false, false, false, false);
}

c_label::~c_label(void)
{
	tools::f_delete_aptr(this->__v_buffer);
	tools::f_delete_aptr(this->__v_default_buffer);
}

/* public function */

bool	c_label::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->_f_init_event_method() == false)
		return false;
	return true;
}

bool	c_label::f_treat_render(void)
{
	if (this->_f_draw_label() == ERR ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

int	c_label::f_treat_keyboard(int key)
{
	if (this->__f_clean_buffer_if_is_default_buffer() == false)
		return false;
	if (tools::f_printable_character(key))
	{
		if (this->__f_add_char_to_buffer(key) == false)
			return false;
		return 1;
	}
	return this->_f_treat_keyboard_method(key);
}

bool	c_label::f_treat_mouse(void)
{
	if (this->_f_click_on_me() == true)
	{
		if (this->_v_event->f_mouse_button_used(D_LEFT_BUTTON_CLICKED) == true)
			if (this->__f_manage_left_click() == false)
				return false;
	}
	return true;
}

bool	c_label::f_event_key_left(void)
{
	if ((this->__v_cursor_position + this->__v_decal_buffer) == tools::f_strlen(this->__v_buffer))
		if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), 0, this->__v_cursor_position, ' ') == false)
			M_ERROR_VOID("Error: tools::f_my_mvwaddnstr(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), 0, this->__v_cursor_position, ' ');
	if (this->__v_cursor_position > 0)
		--this->__v_cursor_position;
	else if (this->__v_decal_buffer > 0)
		--this->__v_decal_buffer;
	return true;
}

bool	c_label::f_event_key_right(void)
{
	if ((this->__v_cursor_position < tools::f_strlen(this->__v_buffer)) &&
	    (this->__v_cursor_position < (this->f_get_info_size('w') - 2)))
		++this->__v_cursor_position;
	else if (this->__v_cursor_position + this->__v_decal_buffer < tools::f_strlen(this->__v_buffer))
		++this->__v_decal_buffer;
	return true;
}

bool	c_label::f_event_backspace(void)
{
	unsigned int	tmp;
	unsigned int	len = tools::f_strlen(this->__v_buffer);

	if (this->__v_default_buffer_use == true || len == 0 || (this->__v_cursor_position == 0 && this->__v_decal_buffer == 0))
		return true;
	if ((this->__v_cursor_position != 0) && (this->__v_cursor_position + this->__v_decal_buffer) == len)
	{
		this->__v_buffer[len - 1] = 0;
		--this->__v_cursor_position;
		if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), 0, this->__v_cursor_position + 1, ' ') == false)
			M_ERROR_VOID("Error: tools::f_my_mvwaddnstr(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), 0, this->__v_cursor_position + 1, ' ');
	}
	else if (this->__v_cursor_position == 0 && this->__v_decal_buffer != 0)
	{
		tmp = (this->f_get_info_size('w') >> 1);
		if (this->__v_decal_buffer < tmp)
		{
			this->__v_cursor_position = this->__v_decal_buffer;
			this->__v_decal_buffer = 0;
		}
		else
		{
			this->__v_decal_buffer -= tmp;
			this->__v_cursor_position = tmp;
		}
	}
	else
	{
		this->__f_decal_left_buffer_pos_to_pos(this->__v_cursor_position + this->__v_decal_buffer, this->__v_cursor_position + this->__v_decal_buffer - 1);
		--this->__v_cursor_position;
		if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), 0, tools::f_strlen(this->__v_buffer), ' ') == false)
			M_ERROR_VOID("Error: tools::f_my_mvwaddnstr(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), 0, tools::f_strlen(this->__v_buffer), ' ');
	}
	if (this->__v_real_time_callback != NULL)
		return this->__v_real_time_callback(this->_v_ncurses, this);
	return true;
}

bool	c_label::f_event_escape(void)
{
	if (this->_v_event->f_add_container_focused(this->_v_parent) == false)
		return false;
	if (tools::f_strlen(this->__v_buffer) != 0 &&
	    tools::f_my_mvwaddch(this->_v_window.f_get_window(), 0, this->__v_cursor_position, ' ') == false)
		M_ERROR_VOID("Error: tools::f_my_mvwaddnstr(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), 0, this->__v_cursor_position, ' ');
	return this->f_not_focus_anymore();
}

bool	c_label::f_not_focus_anymore(void)
{
	this->__v_i_am_focus = false;
	if (tools::f_strlen(this->__v_buffer) != 0 &&
	    tools::f_my_mvwaddch(this->_v_window.f_get_window(), 0, this->__v_cursor_position, ' ') == false)
		M_ERROR_VOID("Error: tools::f_my_mvwaddnstr(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), 0, this->__v_cursor_position, ' ');
	if (tools::f_strlen(this->__v_buffer) == 0)
		this->f_push_default_buffer_in_buffer();
	if (this->__v_not_focus_anymore_callback != NULL)
		return this->__v_not_focus_anymore_callback(this->_v_ncurses, this);
	return true;
}

bool	c_label::f_set_label(const char* str)
{
	if (this->__v_label_type == E_LABEL_NUMERIC && this->__f_is_numeric_str(str) == false)
		return true;
	if (this->f_clean_buffer() == false)
		return false;
	this->__v_default_buffer_use = false;
	return this->f_add_str_to_label(str);
}

bool	c_label::f_add_str_to_label(const char* str)
{
	if (this->__v_label_type == E_LABEL_NUMERIC && this->__f_is_numeric_str(str) == false)
		return true;
	while (*str != 0)
	{
		if (this->__f_add_char_to_buffer(*str) == false)
			return false;
		++str;
	}
	return true;
}

const char*	c_label::f_get_content(void)
{
	if (this->__v_default_buffer_use == true)
		return NULL;
	return this->__v_buffer;
}

const char*	c_label::f_get_default_buffer(void)
{
	return this->__v_default_buffer;
}

bool	c_label::f_init_default_buffer(const char* default_buffer)
{
	int	len;

	if (default_buffer == NULL)
		return true;
	tools::f_delete_aptr(this->__v_default_buffer);
	len = tools::f_strlen(default_buffer);
	this->__v_default_buffer = new (std::nothrow) char[len + 1];
	if (this->__v_default_buffer == NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) char[%d]\n", len);
	tools::f_strcpy(this->__v_default_buffer, default_buffer);
	this->__v_default_buffer[len] = 0;
	return true;
}

void	c_label::f_push_default_buffer_in_buffer(void)
{
	if (this->__v_default_buffer != NULL)
	{
		tools::f_strcpy(this->__v_buffer, this->__v_default_buffer);
		this->__v_default_buffer[tools::f_strlen(this->__v_default_buffer)] = 0;
		this->__v_default_buffer_use = true;
	}
}

void	c_label::f_set_not_focus_anymore_callback(t_single_callback callback)
{
	this->__v_not_focus_anymore_callback = callback;
}

void	c_label::f_set_real_time_callback(t_single_callback callback)
{
	this->__v_real_time_callback = callback;
}

/* protected function */

bool	c_label::_f_draw_label(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_LABEL)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_LABEL));
	if (tools::f_my_mvwaddnstr(this->_v_window.f_get_window(), 5, 0, 0, this->__v_buffer + this->__v_decal_buffer, this->f_get_info_size('w') - 1) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, %p, %d)\n", this->_v_window.f_get_window(), 5, 0, 0, this->__v_buffer + this->__v_decal_buffer, this->f_get_info_size('w') - 1);
	if (this->__f_draw_cursor() == false)
		return false;
	return true;
}

bool	c_label::_f_init_default_buffer_and_size_buffer(const char* default_buffer, int* size_buffer)
{
	int	len;

	if (default_buffer != NULL)
	{
		len = tools::f_strlen(default_buffer);
		if (*size_buffer <= len)
			*size_buffer = len + 1;
		if (this->f_init_default_buffer(default_buffer) == false)
			return false;
	}
	return true;
}

bool	c_label::_f_init_buffer(int size_buffer)
{
	this->__v_size_buffer = size_buffer;
	this->__v_buffer = new (std::nothrow) char[size_buffer];
	if (this->__v_buffer== NULL)
		return M_ERROR(false, "Error: operator new (std::nothrow) char[%d]\n", size_buffer);
	this->f_push_default_buffer_in_buffer();
	return true;
}

bool	c_label::_f_init_event_method(void)
{
	if (this->_f_add_common_callback(KEY_LEFT, (t_common_callback)(&c_label::f_event_key_left)) == false ||
	    this->_f_add_common_callback(KEY_RIGHT, (t_common_callback)(&c_label::f_event_key_right)) == false ||
	    this->_f_add_common_callback(KEY_BACKSPACE, (t_common_callback)(&c_label::f_event_backspace)) == false ||
	    this->_f_add_common_callback(D_BACKSPACE, (t_common_callback)(&c_label::f_event_backspace)) == false ||
	    this->_f_add_common_callback(D_ESCAPE, (t_common_callback)(&c_label::f_event_escape)) == false)
		return false;
	return true;
}

/* private function */

bool	c_label::__f_manage_left_click(void)
{
	this->__v_i_am_focus = true;
	if (this->_v_event->f_add_container_focused(this) == false ||
	    this->__f_clean_buffer_if_is_default_buffer() == false)
		return false;
	return true;
}

bool	c_label::__f_add_char_to_buffer(int key)
{
	int	len;

	if (this->__v_label_type == E_LABEL_NUMERIC && this->__f_is_numeric_char(key) == false)
		return true;
	len = tools::f_strlen(this->__v_buffer);
	if (len + 1 >= this->__v_size_buffer)
		return true;
	this->__f_insert_to_buffer(key, this->__v_cursor_position + this->__v_decal_buffer);
	if (this->__v_cursor_position == (this->f_get_info_size('w') - 2))
		++this->__v_decal_buffer;
	else
		++this->__v_cursor_position;
	len = tools::f_strlen(this->__v_buffer);
	if (this->__v_real_time_callback != NULL)
		return this->__v_real_time_callback(this->_v_ncurses, this);
	return true;
}

void	c_label::__f_insert_to_buffer(int key, int pos)
{
	int	i;

	i = tools::f_strlen(this->__v_buffer);
	while (i >= pos)
	{
		this->__v_buffer[i + 1] = this->__v_buffer[i];
		--i;
	}
	this->__v_buffer[i + 1] = key;
}

void	c_label::__f_decal_left_buffer_pos_to_pos(int pos_moved, int pos_dest)
{
	int	i, size;

	i = 0;
	size = tools::f_strlen(this->__v_buffer) - pos_moved;
	while (i <= size)
	{
		this->__v_buffer[pos_dest + i] = this->__v_buffer[pos_moved + i];
		++i;
	}
}

bool	c_label::__f_clean_buffer_if_is_default_buffer(void)
{
	if (this->__v_default_buffer_use == true)
		if (this->f_clean_buffer() == false)
			return false;
	return true;
}

bool	c_label::f_clean_buffer(void)
{
	this->__v_buffer[0] = 0;
	this->__v_cursor_position = 0;
	this->__v_default_buffer_use = false;
	if (this->__f_erase_text() == false)
		return false;
	return true;
}

bool	c_label::__f_erase_text(void)
{
	int	i, size;

	i = 0;
	size = getmaxx(this->_v_window.f_get_window()) - 1;
	while (i < size)
	{
		if (tools::f_my_mvwaddch(this->_v_window.f_get_window(), 0, i, ' ') == false)
			M_ERROR_VOID("Error: tools::f_my_mvwaddnstr(%p, %d, %d, '%c')\n", this->_v_window.f_get_window(), 0, i, ' ');
		++i;
	}
	return true;
}

bool	c_label::__f_draw_cursor(void)
{
	char	cursor_char;

	if (this->__v_i_am_focus == false)
		return true;
	cursor_char = this->__v_buffer[this->__v_decal_buffer + this->__v_cursor_position];
	if (cursor_char == 0)
	{
		cursor_char = '|';
		if (wattron(this->_v_window.f_get_window(), A_BLINK) == ERR)
			M_ERROR_VOID("Error: wattron(%p, %d)\n", this->_v_window.f_get_window(), A_BLINK);
	}
	else if (wattron(this->_v_window.f_get_window(), A_BLINK | A_REVERSE) == ERR)
		M_ERROR_VOID("Error: wattron(%p, %d)\n", this->_v_window.f_get_window(), A_BLINK | A_REVERSE);
	if (mvwprintw(this->_v_window.f_get_window(), 0, this->__v_cursor_position, "%c", cursor_char) == ERR)
		M_ERROR_VOID("Error: mvwprintw(%p, %d, %d, \"%s\", '%c')\n", this->_v_window.f_get_window(), 0, this->__v_cursor_position, "%c", cursor_char);
	if (cursor_char == '|')
	{
		if (wattroff(this->_v_window.f_get_window(), A_BLINK) == ERR)
			M_ERROR_VOID("Error: wattroff(%p, %d)\n", this->_v_window.f_get_window(), A_BLINK);
	}
	else if (wattroff(this->_v_window.f_get_window(), A_BLINK | A_REVERSE) == ERR)
		M_ERROR_VOID("Error: wattroff(%p, %d)\n", this->_v_window.f_get_window(), A_BLINK | A_REVERSE);
	return true;
}

bool	c_label::__f_is_numeric_str(const char* str)
{
	int	i, size;

	i = 0;
	size = tools::f_strlen(str);
	while (i < size)
	{
		if (this->__f_is_numeric_char(str[i]) == false)
			return false;
		++i;
	}
	return true;
}

bool	c_label::__f_is_numeric_char(int key)
{
	if (key == '-')
	{
		if (this->_v_negative_nbr == true)
			return true;
		else
			return false;
	}
	else if ((key < '0') || (key > '9'))
		return false;
	return true;
}
