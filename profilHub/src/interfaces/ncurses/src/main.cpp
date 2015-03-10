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

/*
	 ____                    ___       ___    __  __            __
	/\  _`\                /'___\  __ /\_ \  /\ \/\ \          /\ \
	\ \ \L\ \ _ __   ___  /\ \__/ /\_\\//\ \ \ \ \_\ \   __  __\ \ \____        ___      ___   __  __   _ __   ____     __     ____
	 \ \ ,__//\`'__\/ __`\\ \ ,__\\/\ \ \ \ \ \ \  _  \ /\ \/\ \\ \ '__`\     /' _ `\   /'___\/\ \/\ \ /\`'__\/',__\  /'__`\  /',__\
	  \ \ \/ \ \ \//\ \L\ \\ \ \_/ \ \ \ \_\ \_\ \ \ \ \\ \ \_\ \\ \ \L\ \    /\ \/\ \ /\ \__/\ \ \_\ \\ \ \//\__, `\/\  __/ /\__, `\
	   \ \_\  \ \_\\ \____/ \ \_\   \ \_\/\____\\ \_\ \_\\ \____/ \ \_,__/    \ \_\ \_\\ \____\\ \____/ \ \_\\/\____/\ \____\\/\____/
	    \/_/   \/_/ \/___/   \/_/    \/_/\/____/ \/_/\/_/ \/___/   \/___/      \/_/\/_/ \/____/ \/___/   \/_/ \/___/  \/____/ \/___/
*/

#include <c_ncurses.h>

int	main(int argc, char** argv, char** env)
{
	c_ncurses	ncurses;

	if (ncurses.f_init(argc, argv, env) == false)
		return ncurses.f_close(-1);
	if (ncurses.f_run() == false)
		return ncurses.f_close(-1);
	return ncurses.f_close(0);
}
