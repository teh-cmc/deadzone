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

#ifndef __E_DRIVER_ACTION_H__
#define __E_DRIVER_ACTION_H__

enum	e_driver_action
{
	E_NOTHING_DRIVER,
	E_DOWN_DRIVER = REQ_DOWN_ITEM,
	E_UP_DRIVER = REQ_UP_ITEM,
	E_FIRST_DRIVER = REQ_FIRST_ITEM,
	E_LAST_DRIVER = REQ_LAST_ITEM,
	E_NEXT_PAGE_DRIVER = REQ_SCR_DPAGE,
	E_PREV_PAGE_DRIVER = REQ_SCR_UPAGE,
	E_SET_VALUE_DRIVER =  REQ_TOGGLE_ITEM
};

#endif
