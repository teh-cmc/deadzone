/**
 * Unit tests main
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

#include <tests_window.h>
#include <tests_conf.h>
#include <tests_conf_sdl.h>
#include <tests_pos.h>
#include <tests_entity.h>
#include <tests_object.h>
#include <tests_object_rect.h>

/* ----------------------------------- */

static
void
__add_window_tests(void) {
    g_test_add_func("/window/test_valid_lifecycle", TESTS_WINDOW_valid_lifecycle);
    g_test_add_func("/window/test_null_title", TESTS_WINDOW_null_title);
}

static
void
__add_conf_tests(void) {
    g_test_add_func("/conf/test_dummy_file", TESTS_CONF_dummy_file);
}

static
void
__add_conf_sdl_tests(void) {
    g_test_add_func("/conf_sdl/test_dummy_sdl_file", TESTS_CONF_SDL_dummy_file);
}

static
void
__add_pos_tests(void) {
    g_test_add_func("/pos/test_build_absolute", TESTS_POS_build_absolute);
    g_test_add_func("/pos/test_build_relative", TESTS_POS_build_relative);
    g_test_add_func("/pos/test_set_absolute", TESTS_POS_set_absolute);
    g_test_add_func("/pos/test_set_relative", TESTS_POS_set_relative);
    g_test_add_func("/pos/test_move", TESTS_POS_move);
}

static
void
__add_entity_tests(void) {
    g_test_add_func("/entity/test_build", TESTS_ENTITY_build);
}

static
void
__add_object_tests(void) {
    g_test_add_func("/object/test_build", TESTS_OBJECT_build);
}

static
void
__add_object_rect_tests(void) {
    g_test_add_func("/object_rect/test_build", TESTS_OBJECT_RECT_build);
}

/* ----------------------------------- */

gint
main(gint argc, gchar** argv) {
    g_test_init(&argc, &argv, NULL);
    g_assert(SDL_Init(SDL_INIT_VIDEO) >= 0);

    __add_window_tests();
    __add_conf_tests();
    __add_conf_sdl_tests();
    __add_pos_tests();
    __add_entity_tests();
    __add_object_tests();
    __add_object_rect_tests();

    SDL_Quit();
    return g_test_run();
}