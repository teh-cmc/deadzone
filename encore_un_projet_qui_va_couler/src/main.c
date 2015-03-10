/**
 * Main
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

#include <conf.h>
#include <conf_sdl.h>
#include <log.h>
#include <window.h>

/* ----------------------------------- */

#define __D_MAIN_SUCCESS !TRUE
#define __D_MAIN_FAILURE !__D_MAIN_SUCCESS

/* ----------------------------------- */

gint
main(void) {
    WINDOWWin* wd = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        M_LOG__ERROR(SDL_GetError(), 0);
        return FALSE;
    }
    if (!CONF_SDL_load(D_CONF__PATH_SDL)) return __D_MAIN_FAILURE;

    if (!(wd = WINDOW_build("EUPQVC", 800, 600))){
        wd = WINDOW_destroy(wd);
        SDL_Quit();
        return __D_MAIN_FAILURE;
    }

    while (TRUE) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        SDL_RenderClear(wd->r);
        SDL_RenderPresent(wd->r);
    }

    wd = WINDOW_destroy(wd);
    SDL_Quit();
    return __D_MAIN_SUCCESS;
}