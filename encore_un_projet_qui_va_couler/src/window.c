/**
 * SDL window handling
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

#include <window.h>
#include <log.h>

/* ----------------------------------- */

WINDOWWin*
WINDOW_build(const gchar* title, guint16 w, guint16 h) {
    gint        pos = SDL_WINDOWPOS_UNDEFINED;
    WINDOWWin*  wd = NULL;

    if (!title) { M_LOG__ERROR("`title` cannot be null", 0); return NULL; }
    if (!(wd = (WINDOWWin*)g_malloc0(sizeof(*wd)))) {
        M_LOG__ERROR("Could not build WINDOWWin", 0);
        return NULL;
    }
    if (!(wd->w = SDL_CreateWindow(title, pos, pos, w, h, 0))) {
        M_LOG__ERROR(SDL_GetError(), 0);
        return WINDOW_destroy(wd);
    }
    if (!(wd->r = SDL_CreateRenderer(wd->w, -1, SDL_RENDERER_ACCELERATED))) {
        M_LOG__ERROR(SDL_GetError(), 0);
        return WINDOW_destroy(wd);
    }
    SDL_SetRenderDrawColor(wd->r, 127, 127, 127, 255);

    return wd;
}

WINDOWWin*
WINDOW_destroy(WINDOWWin* wd) {
    if (wd && wd->r) SDL_DestroyRenderer(wd->r);
    if (wd && wd->w) SDL_DestroyWindow(wd->w);
    g_free(wd);

    return NULL;
}