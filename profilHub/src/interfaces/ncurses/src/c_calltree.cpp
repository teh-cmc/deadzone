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

#include <c_calltree.h>
#include <tools.h>
#include <d_color_ui.h>

/* constructer destructer */

c_calltree::c_calltree(c_ncurses* ncurses,
		       c_event* event,
		       c_base_container* parent) : c_data(E_DATA_CALLTREE,
							  ncurses,
							  event,
							  parent),
						   __v_main_function(ncurses, event, this, NULL)
{

}

c_calltree::~c_calltree(void)
{

}

/* pubblic function */

bool	c_calltree::f_init_calltree(void)
{
//	scrollok(this->_v_window.f_get_window(), TRUE);
	if (this->__f_init_size_like_parent() == false ||
	    this->__v_main_function.f_init("main", 0, 0) == false)
		return false;

//	just for test

	this->__v_main_function.f_add_sub_function("fct_0");
		this->__v_main_function.f_get_sub_function_by_index(0)->f_add_sub_function("test_0");
		this->__v_main_function.f_get_sub_function_by_index(0)->f_add_sub_function("test_1");
		this->__v_main_function.f_get_sub_function_by_index(0)->f_add_sub_function("test_2");
	this->__v_main_function.f_add_sub_function("fct_1");
	this->__v_main_function.f_add_sub_function("fct_2");
		this->__v_main_function.f_get_sub_function_by_index(2)->f_add_sub_function("foo_1");
			this->__v_main_function.f_get_sub_function_by_index(2)->f_get_sub_function_by_index(0)->f_add_sub_function("hashtag_0");
				this->__v_main_function.f_get_sub_function_by_index(2)->f_get_sub_function_by_index(0)->f_get_sub_function_by_index(0)->f_add_sub_function("last_0");
			this->__v_main_function.f_get_sub_function_by_index(2)->f_get_sub_function_by_index(0)->f_add_sub_function("hashtag_1");
			this->__v_main_function.f_get_sub_function_by_index(2)->f_get_sub_function_by_index(0)->f_add_sub_function("hashtag_2");
		this->__v_main_function.f_get_sub_function_by_index(2)->f_add_sub_function("foo_2");
		this->__v_main_function.f_get_sub_function_by_index(2)->f_add_sub_function("foo_3");
		this->__v_main_function.f_get_sub_function_by_index(2)->f_add_sub_function("foo_4");
	this->__v_main_function.f_add_sub_function("fct_3");
		this->__v_main_function.f_get_sub_function_by_index(3)->f_add_sub_function("baar_0");
		this->__v_main_function.f_get_sub_function_by_index(3)->f_add_sub_function("baar_1");
		this->__v_main_function.f_get_sub_function_by_index(3)->f_add_sub_function("baar_2");
	this->__v_main_function.f_add_sub_function("fct_4");
			this->__v_main_function.f_get_sub_function_by_index(2)->f_get_sub_function_by_index(0)->f_add_sub_function("hashtag_3");
			this->__v_main_function.f_get_sub_function_by_index(2)->f_get_sub_function_by_index(0)->f_add_sub_function("hashtag_4");
	this->__v_main_function.f_add_sub_function("fct_5");
	return true;
}

bool	c_calltree::f_treat_render(void)
{
	if (this->__f_draw_calltree() == false ||
	    this->_v_window.f_render() == false ||
	    this->_f_render_child() == false)
		return false;
	return true;
}

int	c_calltree::f_treat_keyboard(int key)
{
	(void)key;
	return 0;
}

bool	c_calltree::f_treat_mouse(void)
{
	return this->_f_send_mouse_event_to_child();
}

c_function_calltree*	c_calltree::f_get_fct_by_multiple_index(const char* multiple_index)
{
	if (multiple_index == NULL || multiple_index[0] == 0 || multiple_index[0] != '0')
		return NULL;
	return this->__v_main_function.f_get_fct_by_multiple_index(multiple_index + 1);
}

/* private function */

bool	c_calltree::__f_init_size_like_parent(void)
{
	if (this->f_init(NULL,
			 this->_v_parent->f_get_info_size('x') + 1,
			 this->_v_parent->f_get_info_size('y') + 1,
			 this->_v_parent->f_get_info_size('w') - 2,
			 this->_v_parent->f_get_info_size('h') - 2) == false)
		return false;
	return true;
}

bool	c_calltree::__f_draw_calltree(void)
{
	if (this->_v_window.f_clean() == false)
		return M_ERROR_NO_ARGS(false, "Error: this->_v_window->f_clean()\n");
	if (wbkgd(this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_CALLTREE)) == ERR)
		return M_ERROR(false, "Error: wbkgd(%p, %d)\n", this->_v_window.f_get_window(), COLOR_PAIR(D_COLOR_PAIR_CALLTREE));
	return this->__v_main_function.f_display_branch();
}
