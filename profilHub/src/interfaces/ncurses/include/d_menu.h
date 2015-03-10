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

#ifndef __D_MENU_DATA_H__
#define __D_MENU_DATA_H__

#define D_MENU_NO_INIT		0
#define	D_MENU_DURING_INIT	1
#define	D_MENU_INITED		2
#define D_MENU_UPDATE		3

#define D_PROFILER_INFOS_NOHING	"no option for this profiler"

#define	D_CONTENT_FILE_MENU	{"Open",			"Save",				"Save as",			"Exit",				NULL}
#define	D_CONTENT_FILE_DESC	{"   o",			"   s",				"   shift + s",			"   q",				NULL}
#define D_PTR_FUNC_TAB_FILE	{&open_menu_file_callback,	&save_menu_file_callback,	&save_as_menu_file_callback,	&leave_menu_file_callback,	NULL}

#define	D_CONTENT_TOOLS_MENU	{"Option",			NULL}
#define	D_CONTENT_TOOLS_DESC	{"   shift + o",		NULL}
#define D_PTR_FUNC_TAB_TOOLS	{&options_tools_menu_callback,	NULL}

#define	D_CONTENT_HELP_MENU	{"Report bug",			"About profilHub",		NULL}
#define	D_CONTENT_HELP_DESC	{"   r",			"   a",				NULL}
#define D_PTR_FUNC_TAB_HELP	{&report_help_menu_callback,	&about_help_menu_callback,	NULL}

#endif
