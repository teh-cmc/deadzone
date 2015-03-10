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

#ifndef __D_CHILDREN_INDEXES_H__
#define __D_CHILDREN_INDEXES_H__

/* childrens indexes in main container */
	#define D_TOOLBAR_INDEX		0
	#define D_MIDEL_CONTAINER_INDEX	1
	/* childrens indexes in midel container */
		#define D_TAB_MANAGER_INDEX	0
		/* childrens indexes in tab manager */
			#define D_CHOICE_EXECUTABLE_TAB_INDEX		0
			/* childrens indexes in choice executable tab */
				#define D_CHOICE_ONE_PROFILER_MENU_INDEX	0
				#define D_CHOICE_SUB_OPTIONS_MENU_INDEX		1
				#define D_SELECT_TAB_WILL_GENERATE_INDEX	2
				#define D_EXECUTABLE_PATH_LABEL_INDEX		3
				#define D_EXECUTABLE_ARGUMENTS_LABEL_INDEX	4
				#define D_BROWSE_EXECUTABLE_BUTTON_INDEX	5
				#define D_LAUNCH_ANALYSE_BUTTON_INDEX		6
			#define D_CHOICE_EXECUTABLE_BUTTON_INDEX	1
			#define D_CALLTREE_TAB_INDEX			2	// /!\ this obj is init after program analyze only if is asked in select tab menu
			/* childrens indexes in calltree tab */
				#define D_CALLTREE_INDEX	0
			#define D_CALLTREE_BUTTON_INDEX			3	// /!\ this obj is init after program analyze only if is asked in select tab menu
			#define D_GRAPH_TAB_INDEX			4	// /!\ this obj is init after program analyze only if is asked in select tab menu
			/* childrens indexes in graph tab */
				#define D_GPAPH_INDEX	0
				/* childrens indexes in graph */
					#define D_GRAPHIC_INDEX			0
					#define D_MAX_Y_LABEL_INDEX		1
					#define D_Y_PRECISION_LABEL_INDEX	2
					#define D_BEG_Y_LABEL_INDEX		3
					#define D_BEG_X_LABEL_INDEX		4
					#define D_X_PRECISION_LABEL_INDEX	5
					#define D_MAX_X_LABEL_INDEX		6
					#define D_PREV_FUNCTION_BUTTON_INDEX	7
					#define D_NBR_FUNCTION_LABEL_INDEX	8
					#define D_NAME_FUNCTION_LABEL_INDEX	9
					#define D_NEXT_FUNCTION_BUTTON_INDEX	10
			#define D_GRAPH_BUTTON_INDEX			5	// /!\ this obj is init after program analyze only if is asked in select tab menu
		#define D_SEARCH_MODULE		1
		#define D_ERROR_ZONE		2
		#define D_FILTER_MODULE		3
		#define D_FILTER_ZONE		4
	#define D_STATUS_BAR_INDEX	2
	#define D_FILE_MENU_INDEX	3
	#define D_TOOLS_MENU_INDEX	4
	#define D_HELP_MENU_INDEX	5

#endif
