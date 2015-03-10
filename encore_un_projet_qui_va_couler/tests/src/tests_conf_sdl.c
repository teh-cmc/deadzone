/**
 * conf_sdl module unit tests
 * Copyright (C) 2014  Clement 'cmc' Rey <cr.rey.clement@gmail.com>
 *
 * This file is part of EUPQVC.
 *
 * EUPQVC is free software: you can redistribute it and/or modify
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

#include <glib.h>
#include <SDL.h>

#include <conf.h>
#include <conf_sdl.h>
#include <tests_conf.h>

/* ----------------------------------- */

#define __D_DUMMY_SDL_FILE "./tests/conf/dummy_sdl.ini"

/* ----------------------------------- */

void
TESTS_CONF_SDL_dummy_file(void) {
    g_assert(CONF_SDL_load(__D_DUMMY_SDL_FILE) == TRUE);

    g_assert(SDL_EventState(SDL_QUIT, SDL_QUERY) == SDL_ENABLE);
    g_assert(SDL_EventState(SDL_APP_TERMINATING, SDL_QUERY) == SDL_DISABLE);
}