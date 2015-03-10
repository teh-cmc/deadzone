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

#include <stdio.h>
#include <execinfo.h>
#include <gprintf.h>
#ifdef APPLE
    #include "TargetConditionals.h"
#endif

#include <log.h>

/* ----------------------------------- */

static inline
void
__stacktrace(void) {
#ifdef _WIN64
#elif _WIN32
#elif __APPLE__
    #if TARGET_IPHONE_SIMULATOR
    #elif TARGET_OS_IPHONE
    #elif TARGET_OS_MAC
    #else
    #endif
#elif __linux
    void*       fps[100];
    gchar**     funcs;
    int         stack_size;

    stack_size = backtrace(fps, 100);
    funcs = backtrace_symbols (fps, stack_size);

    g_printf("\nStacktrace:\n");
    for (gint i = 0; i < stack_size; i++)
        g_printf("%s\n", funcs[i]);
    g_free (funcs);
#elif __unix
#elif __posix
#endif
}

/* ----------------------------------- */

static inline
void
__log(const gchar* file, gint line, const gchar* func, LOGLEVEL level,
      const gchar* format, va_list args) {
    if (level > LOGLEVEL_PUB_ERROR) {
        g_fprintf(stderr, "\033[0;37m%s, line \033[0;33m%i: \033[1;37m%s()\n\t",
                  file, line, func);
    } else if (level > LOGLEVEL_WARNING) {
        g_fprintf(stderr, "\033[0;31m");
    } else if (level > LOGLEVEL_INFO) {
        g_fprintf(stderr, "\033[0;33m");
    } else {
        g_fprintf(stderr, "\033[0;37m");
    }
    g_vfprintf(stderr, format, args);
    g_fprintf(stderr, "\033[0;37m\n");
#ifdef DEBUG
    if (level > LOGLEVEL_PUB_ERROR) __stacktrace();
#endif
}

/* ----------------------------------- */

inline
void
LOG_log(const gchar* file, gint line, const gchar* func,
        LOGLEVEL level, const gchar* format, ...) {
    va_list ap;

#ifdef DEBUG
    level = (level == (LOGLEVEL_PUB_ERROR ? LOGLEVEL_ERROR : level));
#endif
    va_start(ap, format);
    __log(file, line, func, level, format, ap);
    va_end(ap);
}