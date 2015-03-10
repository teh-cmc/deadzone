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

#ifndef __C_GRAPH_H__
#define __C_GRAPH_H__

#include <c_base_container.h>
#include <c_button.h>

class	c_event;
class	c_ncurses;
class	c_graph : public c_base_container
{
	public:
			c_graph(c_ncurses* ncurses,
				c_event* event,
				c_base_container* parent);
			~c_graph(void);

		bool	f_init_graph(void);
		bool	f_treat_render(void);
		int	f_treat_keyboard(int key);
		bool	f_treat_mouse(void);
	private:
		bool	f_init(const char* title, int x, int y, int width, int height);
		bool	__f_render_graph(void);
		bool	__f_draw_graph(void);
		bool	__f_init_event_methode(void);
		bool	__f_init_my_child(void);
		bool	__f_init_graphic(void);
		bool	__f_init_ordonnees_labels(void);
		bool	__f_init_abscisses_labels(void);
		bool	__f_init_graphic_interface(void);
		bool	__f_init_label(const char* str, int x, int y, int width,
				       bool numeric, bool negative_nbr,
				       t_single_callback callback);
		bool	__f_init_button(const char* str, int x, int y, int width, int height,
					c_button::t_callback callback, c_base_container* obj_linked);
		bool	__f_fill_graphic_to_test(void);
};

#endif
