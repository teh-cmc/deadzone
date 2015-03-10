/**
 * Log stuff
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

#ifndef LOG_H
#define LOG_H

/* ----------------------------------- */

#include <glib.h>

/* ----------------------------------- */

typedef enum e_log__level {
    LOGLEVEL_INFO,
    LOGLEVEL_WARNING,
    LOGLEVEL_PUB_ERROR,
    LOGLEVEL_ERROR
} LOGLEVEL;

/* ----------------------------------- */

#define M_LOG__INFO(__msg, __args...) \
    LOG_log(__FILE__, __LINE__, __func__, LOGLEVEL_INFO, __msg, __args)

#define M_LOG__WARNING(__msg, __args...) \
    LOG_log(__FILE__, __LINE__, __func__, LOGLEVEL_WARNING, __msg, __args)

#define M_LOG__PUB_ERROR(__msg, __args...) \
    LOG_log(__FILE__, __LINE__, __func__, LOGLEVEL_PUB_ERROR, __msg, __args)

#define M_LOG__ERROR(__msg, __args...) \
    LOG_log(__FILE__, __LINE__, __func__, LOGLEVEL_ERROR, __msg, __args)

/* ----------------------------------- */

void
LOG_log(const gchar* file, gint line, const gchar* func,
        LOGLEVEL level, const gchar* format, ...);

#endif