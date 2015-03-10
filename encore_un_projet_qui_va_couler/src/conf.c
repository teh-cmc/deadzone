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

#include <conf.h>
#include <log.h>

/* ----------------------------------- */

static
GKeyFile*
__load_file(const gchar* path) {
    GKeyFile*       file = NULL;
    GError*         err = NULL;

    if (!(file = g_key_file_new())) {
        M_LOG__PUB_ERROR("Could not create conf file", 0);
        return NULL;
    }
    if (!g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, &err)) {
        M_LOG__PUB_ERROR("Could not load %s: %s", path, err->message);
        g_error_free(err);
        g_key_file_free(file);
        return NULL;
    }
    return file;
}

static
gchar**
__load_groups(GKeyFile* file) {
    gchar** groups = NULL;

    if (!(groups = g_key_file_get_groups(file, NULL))) {
         M_LOG__PUB_ERROR("Could not get groups from conf file", 0);
         return NULL;
    }
    return groups;
}

static
gchar**
__load_keys(GKeyFile* file, const gchar* group_name) {
    gchar** keys = NULL;
    GError* err = NULL;

    if (!(keys = g_key_file_get_keys(file, group_name, NULL, &err))) {
        M_LOG__PUB_ERROR("Could not load keys for group %s: %s",
                         group_name, err->message);
        g_error_free(err);
        return NULL;
    }
    return keys;
}

static
gchar*
__load_value(GKeyFile* file, const gchar* group_name, const gchar* key_name) {
    gchar* value = NULL;
    GError* err = NULL;

    if (!(value = g_key_file_get_value(file, group_name, key_name, &err))) {
        M_LOG__PUB_ERROR("Could not load value for key %s: %s",
                         key_name, err->message);
        g_error_free(err);
        return NULL;
    }
    return value;
}

static
CONFIniValue*
__build_ini_value(const gchar* group, const gchar* key, const gchar* value) {
    CONFIniValue*   ret = NULL;

    if (!(ret = g_malloc0(sizeof(*ret)))) {
        M_LOG__PUB_ERROR("Could not allocate CONFIniValue", 0);
        return NULL;
    }
    ret->group  = g_strdup(group);
    ret->key    = g_strdup(key);
    ret->value  = g_strdup(value);
    if (!ret->group || !ret->key || !ret->value) {
        g_free(ret->group);
        g_free(ret->key);
        g_free(ret->value);
        M_LOG__PUB_ERROR("Could not initialize CONFIniValue", 0);
        return NULL;
    }
    return ret;
}

static
void
__destroy_ini_value(gpointer ini_value) {
    g_free(((CONFIniValue*)ini_value)->group);
    g_free(((CONFIniValue*)ini_value)->key);
    g_free(((CONFIniValue*)ini_value)->value);
}

/* ----------------------------------- */

GSList*
CONF_destroy(GSList* conf) {
    g_slist_free_full(conf, __destroy_ini_value);
    return NULL;
}

GSList*
CONF_build(const gchar* path) {
    GKeyFile*       file = NULL;
    gchar**         groups = NULL;
    gchar**         keys = NULL;
    gchar*          value = NULL;
    CONFIniValue*   ini = NULL;
    GSList*         conf = NULL;

    if (!(file = __load_file(path))) return NULL;
    if (!(groups = __load_groups(file))) return NULL;

    for (gint i = 0; groups[i]; ++i) {
        if ((keys = __load_keys(file, groups[i]))) {
            for (gint j = 0; keys[j]; ++j) {
                if ((value = __load_value(file, groups[i], keys[j]))) {
                    if ((ini = __build_ini_value(groups[i], keys[j], value))) {
                        conf = g_slist_append(conf, ini);
                    }
                    g_free(value);
                }
            }
            g_strfreev(keys);
        }
    }
    g_strfreev(groups);
    g_key_file_free(file);
    return conf;
}