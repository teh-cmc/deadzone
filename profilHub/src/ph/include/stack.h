/**
 * Meta stack API
 * Copyright (C) 2013  Clement Rey <cr.rey.clement@gmail.com>
 *
 * This file is part of profilHub.
 *
 * profilHub is free software: you can redistribute it and/or modify
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

#ifndef __STACK__
#define __STACK__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define D_SK_MAGIC_NODE			__sk_node
#define D_SK_MAGIC_NODE_DECLARATION	struct sk_node __sk_node

#define M_SK_CONTAINER(ptr, container_type)\
	((container_type*)((uint8_t*)ptr - offsetof(container_type, D_SK_MAGIC_NODE)))

#ifdef __cplusplus
extern "C" {
#endif

struct	sk_node
{
	struct sk_node*	below;
};

#ifdef __cplusplus
}
#endif

#define M_SK_PUSH(__ptr, __data, __ret)\
	do {\
		__ret = false;\
		if (!__ptr)\
		{\
			if (!(__ptr = malloc(sizeof(typeof(__data)))))\
				break;\
			*__ptr = __data;\
			__ptr->D_SK_MAGIC_NODE.below = NULL;\
			__ret = true;\
			break;\
		}\
		typeof(__data)*	__node = malloc(sizeof(typeof(__data)));\
		if (!__node) break;\
		*__node = __data;\
		__node->D_SK_MAGIC_NODE.below = __ptr->D_SK_MAGIC_NODE;\
		__ptr = __node;\
		__ret = true;\
	} while (0)

#define M_SK_DEL(__ptr)\
	do {\
		if (!__ptr) break;\
		typeof(*__ptr)*	__prev = M_SK_CONTAINER(&*__ptr->D_SK_MAGIC_NODE.below, typeof(*__ptr));\
		free(__ptr);\
		__ptr = __prev;\
	} while (0)

#define M_SK_POP(__ptr, __poped)\
	do {\
		if (!__ptr) break;\
		typeof(*__ptr)*	__prev = M_SK_CONTAINER(&*__ptr->D_SK_MAGIC_NODE.below, typeof(*__ptr));\
		__poped = __ptr;\
		__ptr = __prev;\
	} while (0)

#define M_SK_ERASE(__ptr)\
	while (__ptr)\
		M_SK_DEL_BACK(__ptr);

#endif
