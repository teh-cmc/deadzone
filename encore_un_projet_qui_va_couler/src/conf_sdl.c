/**
 * SDL conf
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

#include <SDL.h>

#include <conf.h>
#include <conf_sdl.h>
#include <log.h>

/* ----------------------------------- */

typedef struct __s_conf_sdl__mapped_event {
    const gchar*    name;
    SDL_EventType   value;
} __MappedEvent;

/* ----------------------------------- */

#define __M_KV_MAP(__X) { #__X, __X }

/* ----------------------------------- */

static const __MappedEvent local_events[] = {
    __M_KV_MAP(SDL_QUIT),
    __M_KV_MAP(SDL_APP_TERMINATING),
    __M_KV_MAP(SDL_APP_LOWMEMORY),
    __M_KV_MAP(SDL_APP_WILLENTERBACKGROUND),
    __M_KV_MAP(SDL_APP_DIDENTERBACKGROUND),
    __M_KV_MAP(SDL_APP_WILLENTERFOREGROUND),
    __M_KV_MAP(SDL_APP_DIDENTERFOREGROUND),
    __M_KV_MAP(SDL_WINDOWEVENT),
    __M_KV_MAP(SDL_SYSWMEVENT),
    __M_KV_MAP(SDL_KEYDOWN),
    __M_KV_MAP(SDL_KEYUP),
    __M_KV_MAP(SDL_TEXTEDITING),
    __M_KV_MAP(SDL_TEXTINPUT),
    __M_KV_MAP(SDL_MOUSEMOTION),
    __M_KV_MAP(SDL_MOUSEBUTTONDOWN),
    __M_KV_MAP(SDL_MOUSEBUTTONUP),
    __M_KV_MAP(SDL_MOUSEWHEEL),
    __M_KV_MAP(SDL_JOYAXISMOTION),
    __M_KV_MAP(SDL_JOYBALLMOTION),
    __M_KV_MAP(SDL_JOYHATMOTION),
    __M_KV_MAP(SDL_JOYBUTTONDOWN),
    __M_KV_MAP(SDL_JOYBUTTONUP),
    __M_KV_MAP(SDL_JOYDEVICEADDED),
    __M_KV_MAP(SDL_JOYDEVICEREMOVED),
    __M_KV_MAP(SDL_CONTROLLERAXISMOTION),
    __M_KV_MAP(SDL_CONTROLLERBUTTONDOWN),
    __M_KV_MAP(SDL_CONTROLLERBUTTONUP),
    __M_KV_MAP(SDL_CONTROLLERDEVICEADDED),
    __M_KV_MAP(SDL_CONTROLLERDEVICEREMOVED),
    __M_KV_MAP(SDL_CONTROLLERDEVICEREMAPPED),
    __M_KV_MAP(SDL_FINGERDOWN),
    __M_KV_MAP(SDL_FINGERUP),
    __M_KV_MAP(SDL_FINGERMOTION),
    __M_KV_MAP(SDL_DOLLARGESTURE),
    __M_KV_MAP(SDL_DOLLARRECORD),
    __M_KV_MAP(SDL_MULTIGESTURE),
    __M_KV_MAP(SDL_CLIPBOARDUPDATE),
    __M_KV_MAP(SDL_DROPFILE),
    __M_KV_MAP(SDL_RENDER_TARGETS_RESET),
    // __M_KV_MAP(SDL_RENDER_DEVICE_RESET),
    __M_KV_MAP(SDL_USEREVENT),
    __M_KV_MAP(SDL_LASTEVENT),
    { .name = NULL, .value = SDL_LASTEVENT }
};

/* ----------------------------------- */

static inline
int
__event_name_to_value(const gchar* name) {
    for (gint i = 0; local_events[i].name; ++i) {
        if (!g_strcmp0(name, local_events[i].name)) return local_events[i].value;
    }
    M_LOG__PUB_ERROR("Could not find event %s", name);
    return -1;
}

static inline
gboolean
__load_events(GSList* conf) {
    gint    event;
    guint8  state;

    for (gint i = 0; conf; conf = conf->next, ++i) {
        if (!g_strcmp0(M_CONF__GROUP(conf), "Discarded events") &&
            (event = __event_name_to_value(M_CONF__KEY(conf))) != -1) {
            state = (M_CONF__STR2BOOL(M_CONF__VALUE(conf)) ? SDL_ENABLE : SDL_DISABLE);
            SDL_EventState(event, state);
            M_LOG__INFO("Setting %s (%d) to %d", M_CONF__KEY(conf), event, state);
        }
    }
    return TRUE;
}

/* ----------------------------------- */

gboolean
CONF_SDL_load(const gchar* path) {
    GSList*     conf = NULL;

    if (!(conf = CONF_build(path))) return FALSE;

    if (!__load_events(conf)) {
        conf = CONF_destroy(conf);
        return FALSE;
    }

    conf = CONF_destroy(conf);

    return TRUE;
}