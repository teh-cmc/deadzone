/**
 * Config files handling
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

#ifndef CONF_H
#define CONF_H

/* ----------------------------------- */

#include <glib.h>

/* ----------------------------------- */

typedef struct s_conf__ini_value {
    gchar*  group;
    gchar*  key;
    gchar*  value;
} CONFIniValue;

/* ----------------------------------- */

#define D_CONF__PATH_SDL "./conf/sdl.ini"

#define M_CONF__GROUP(__conf) (((CONFIniValue*)__conf->data)->group)
#define M_CONF__KEY(__conf) (((CONFIniValue*)__conf->data)->key)
#define M_CONF__VALUE(__conf) (((CONFIniValue*)__conf->data)->value)

#define M_CONF__STR2BOOL(__str) (g_strcmp0(__str, "true") ? FALSE : TRUE)

/* ----------------------------------- */

GSList*
CONF_build(const gchar* path);

GSList*
CONF_destroy(GSList* values);

/* ----------------------------------- */

#endif