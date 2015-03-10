
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

#include <c_text_zone.h>
#include <d_color_ui.h>
#include <tools.h>
#include <e_obj_type.h>

/* consttructer destructer */

c_text_zone::c_text_zone(c_ncurses* ncurses,
			 c_event* event,
			 c_base_container* parent) : c_base_container(E_TEXT_ZONE,
								      ncurses,
								      event,
								      parent,
								      true,
								      true,
								      true,
								      true),
						     __v_allocated(false),
						     __v_text(NULL)
{

}

c_text_zone::~c_text_zone(void)
{
	if (this->__v_allocated == true)
		tools::f_delete_aptr(this->__v_text);
}

/* public function */

bool	c_text_zone::f_init(const char* title, int x, int y, int width, int height)
{
	(void)title;
	if (this->_v_window.f_init(x, y, width, height) == false ||
	    this->__f_init_event_methode() == false)
		return false;
	return true;
}

bool	c_text_zone::f_treat_render(void)
{
	if (this->__f_draw_text_zone() == false ||
	    this->_v_window.f_render() == false)
		return false;
	return true;
}

int	c_text_zone::f_treat_keyboard(int key)
{
	(void)key;
	return true;
}

bool	c_text_zone::f_treat_mouse(void)
{
	return true;
}

bool	c_text_zone::f_fill_text_by_alloc(const char* str)
{
	if (this->__v_allocated == true)
		tools::f_delete_aptr(this->__v_text);
	else
		this->__v_allocated = true;
	this->__v_text = tools::f_strdup(str);
	if (this->__v_text == NULL)
		return M_ERROR(false, "Error: strdup(%s)\n", str);
	return true;
}

void	c_text_zone::f_fill_text_by_reference(char* str)
{
	if (this->__v_allocated == true)
	{
		tools::f_delete_aptr(this->__v_text);
		this->__v_allocated = false;
	}
	this->__v_text = str;
}

/* private function */

bool	c_text_zone::__f_draw_text_zone(void)
{
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TEXT_ZONE)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_TEXT_ZONE));
	if (this->__v_text != NULL &&
	    tools::f_my_mvwaddnstr(this->_v_window.f_get_window(), 1, 0, 0, this->__v_text, this->f_get_info_size('w') * this->f_get_info_size('h')) == false)
		return M_ERROR(false, "Error: tools::f_my_mvwaddnstr(%p, %d, %d, %d, \"%s\", %d)\n", this->_v_window.f_get_window(), 1, 0, 0, this->__v_text, this->f_get_info_size('w') * this->f_get_info_size('h'));
	return true;
}

bool	c_text_zone::__f_init_event_methode(void)
{
	return true;
}
