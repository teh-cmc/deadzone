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

#ifndef __C_INIT_SECONDARY_IREM_H__
#define __C_INIT_SECONDARY_IREM_H__

class	c_ui;
class	c_event;
class	c_graph;
class	c_ncurses;
class	c_data_ui;
class	c_menu_scroll;
class	c_tab_manager;
class	c_base_container;
class	c_function_calltree;
class	c_init_secondary_item
{
	public:
				c_init_secondary_item(c_ncurses* ncurses,
						      c_event* event,
						      c_data_ui* data_ui);
				~c_init_secondary_item(void);

		bool		f_init_calltree_tab(void);
		bool		f_init_graph_tab(void);
		bool		f_init_tabs(void);
		bool		f_init_error_zone(void);
	private:
		bool		__f_fill_calltree_tab(c_tab_manager* tab_manager);
		bool		__f_fill_graph_tab(c_tab_manager* tab_manager);
		bool		__f_fill_graph(c_graph* graph);
		c_menu_scroll*	__f_get_select_tab_menu(void);
		bool		__f_clean_workspace(void);
		bool		__f_clean_tab_manager(void);
		c_tab_manager*	__f_get_tab_manager(void);
		void		__f_clean_indicator(void);
		void		__f_clean_fct_indict(void);
		void		__f_clean_filter_indict(void);
		bool		__f_init_one_fct_indict(c_base_container* parent,
							c_function_calltree* fct_calltree,
							int x, int y, int width, int height);
		bool		__f_add_fct_indict_to_err_zone(const char* multiple_index);

		c_event*	__v_event;
		c_data_ui*	__v_data_ui;
		c_ncurses*	__v_ncurses;
};

#endif
