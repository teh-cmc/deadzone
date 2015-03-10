/**
 * conf module unit tests
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

#include <conf.h>
#include <tests_conf.h>

/* ----------------------------------- */

#define __D_DUMMY_FILE "./tests/conf/dummy.ini"

/* ----------------------------------- */

void
TESTS_CONF_dummy_file(void) {
    CONFIniValue    dum1 = {
        .group = "Dummy group",
        .key = "DUMMY_KEY_1",
        .value = "dummy_value_1"
    };
    CONFIniValue    dum2 = {
        .group = "Dummy group",
        .key = "DUMMY_KEY_2",
        .value = "dummy_value_2"
    };
    CONFIniValue*   dummies[] = { &dum1, &dum2 };

    GSList* conf = CONF_build(__D_DUMMY_FILE);
    g_assert(conf != NULL);

    for (int i = 0; conf; conf = conf->next, ++i) {
        g_assert(g_strcmp0(M_CONF__GROUP(conf), dummies[i]->group) == 0);
        g_assert(g_strcmp0(M_CONF__KEY(conf), dummies[i]->key) == 0);
        g_assert(g_strcmp0(M_CONF__VALUE(conf), dummies[i]->value) == 0);
    }

    g_assert(CONF_destroy(conf) == NULL);
}