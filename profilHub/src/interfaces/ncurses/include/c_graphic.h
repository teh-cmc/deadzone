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

#ifndef __C_GRAPHIC_H__
#define __C_GRAPHIC_H__

#include <c_base_container.h>
#include <vector>

class	c_function_graphic;
class	c_graphic : public c_base_container
{
	public:
							c_graphic(c_ncurses* ncurses, c_event* event, c_base_container* parent);
							~c_graphic(void);

		bool					f_init(const char* title, int x, int y, int width, int height);
		bool					f_init_definition_domaine(int x_min, int x_max, int y_min, int y_max);
		bool					f_init_display_precision(int x_precision, int y_precision);
		void					f_init_graphic_data(void);
		bool					f_treat_render(void);
		int					f_treat_keyboard(int key);
		bool					f_treat_mouse(void);
		void					f_set_x_min(int x_min);
		int					f_get_x_min(void);
		void					f_set_x_max(int x_max);
		int					f_get_x_max(void);
		void					f_set_y_min(int y_min);
		int					f_get_y_min(void);
		void					f_set_y_max(int y_max);
		int					f_get_y_max(void);
		void					f_set_x_precision(int x_precision);
		void					f_set_y_precision(int y_precision);
		bool					f_add_function_graphic(const char* name, char motif, int color_pair);
		int					f_function_graphic_count(void);
		c_function_graphic*			f_get_function_graphic_by_index(unsigned int index);
		bool					f_find_name_function(const char* name);
		int					f_get_index_by_name_function(const char* name);
	private:
		bool					__f_check_definition_domaine(int x_min, int x_max, int y_min, int y_max);
		bool					__f_init_event_methode(void);
		bool					__f_draw_graphic(void);
		bool					__f_draw_main_axes(int x_decal, int y_decal);
		bool					__f_draw_abscisses_axes(int decal);
		bool					__f_draw_ordonnees_axes(int decal);
		bool					__f_draw_abscisses(int pos);
		bool					__f_draw_ordonnees(int pos);
		bool					__f_draw_cross_axes(void);
		bool					__f_draw_precision_axes(void);
		bool					__f_draw_precision_on_main_axes(void);
		bool					__f_draw_sub_axes(void);
		bool					__f_draw_precision_abscisses(void);
		bool					__f_draw_precision_ordonnees(void);
		bool					__f_draw_function_graphic(void);
		bool					__f_draw_all_functions(void);
		bool					__f_draw_one_function(c_function_graphic* function_graphic);
		bool					__f_draw_point(int x, int y, char motif, int color_pair);

		int					__v_init;
		int					__v_x_min;
		int					__v_x_max;
		int					__v_y_min;
		int					__v_y_max;
		int					__v_x_precision;
		int					__v_y_precision;
		float					__v_width_ratio;
		float					__v_height_ratio;
		int					__v_pos_abscisse;
		int					__v_pos_ordonnee;
		std::vector<c_function_graphic*>	__v_function_graphic_vect;
};

#endif
