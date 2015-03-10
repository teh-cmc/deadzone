/**
 * Meta doubly linked list API
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

#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define D_LL_MAGIC_NODE			__ll_node
#define D_LL_MAGIC_NODE_DECLARATION	struct ll_node __ll_node

#define M_LL_CONTAINER(ptr, container_type)\
	((container_type*)((uint8_t*)ptr - offsetof(container_type, D_LL_MAGIC_NODE)))

#ifdef __cplusplus
extern "C" {
#endif

struct	ll_node
{
	struct ll_node*	next;
	struct ll_node*	prev;
};

#ifdef __cplusplus
}
#endif

#define M_LL_PUSH_FRONT(__ptr, __data, __ret)\
	do {\
		__ret = false;\
		if (!__ptr)\
		{\
			if (!(__ptr = malloc(sizeof(typeof(__data)))))\
				break;\
			*__ptr = __data;\
			__ptr->D_LL_MAGIC_NODE.prev = &__ptr->D_LL_MAGIC_NODE;\
			__ptr->D_LL_MAGIC_NODE.next = &__ptr->D_LL_MAGIC_NODE;\
			__ret = true;\
			break;\
		}\
		typeof(__data)*	__node = malloc(sizeof(typeof(__data)));\
		if (!__node) break;\
		__ptr->D_LL_MAGIC_NODE.prev->next = &__node->D_LL_MAGIC_NODE;\
		*__node = __data;\
		__node->D_LL_MAGIC_NODE.prev = __ptr->D_LL_MAGIC_NODE.prev;\
		__node->D_LL_MAGIC_NODE.next = &__ptr->D_LL_MAGIC_NODE;\
		__ptr->D_LL_MAGIC_NODE.prev = &__node->D_LL_MAGIC_NODE;\
		__ptr = __node;\
		__ret = true;\
	} while (0)

#define M_LL_PUSH_BACK(__ptr, __data, __ret)\
	do {\
		__ret = false;\
		if (!__ptr)\
		{\
			if (!(__ptr = malloc(sizeof(typeof(__data)))))\
				break;\
			*__ptr = __data;\
			__ptr->D_LL_MAGIC_NODE.prev = &__ptr->D_LL_MAGIC_NODE;\
			__ptr->D_LL_MAGIC_NODE.next = &__ptr->D_LL_MAGIC_NODE;\
			__ret = true;\
			break;\
		}\
		typeof(__data)*	__node = malloc(sizeof(typeof(__data)));\
		if (!__node) break;\
		__ptr->D_LL_MAGIC_NODE.prev->next = &__node->D_LL_MAGIC_NODE;\
		*__node = __data;\
		__node->D_LL_MAGIC_NODE.prev = __ptr->D_LL_MAGIC_NODE.prev;\
		__node->D_LL_MAGIC_NODE.next = &__ptr->D_LL_MAGIC_NODE;\
		__ptr->D_LL_MAGIC_NODE.prev = &__node->D_LL_MAGIC_NODE;\
		__ret = true;\
	} while (0)

#define M_LL_DEL_BACK(__ptr)\
	do {\
		if (!__ptr) break;\
		typeof(*__ptr)*	__prev = M_LL_CONTAINER(&*__ptr->D_LL_MAGIC_NODE.prev, typeof(*__ptr));\
		__ptr->D_LL_MAGIC_NODE.prev = __prev->D_LL_MAGIC_NODE.prev;\
		__ptr->D_LL_MAGIC_NODE.prev->next = &__ptr->D_LL_MAGIC_NODE;\
		if (__prev == __ptr) __ptr = NULL;\
		free(__prev);\
	} while (0)

#define M_LL_DEL_FRONT(__ptr)\
	do {\
		if (!__ptr) break;\
		__ptr = M_LL_CONTAINER(&*__ptr->D_LL_MAGIC_NODE.next, typeof(*__ptr));\
		M_LL_DEL_BACK(__ptr);\
	} while (0)

#define M_LL_POP_BACK(__ptr, poped)\
	do {\
		if (!__ptr) break;\
		poped = M_LL_CONTAINER(&*__ptr->D_LL_MAGIC_NODE.prev, typeof(*__ptr));\
		__ptr->D_LL_MAGIC_NODE.prev = poped->D_LL_MAGIC_NODE.prev;\
		__ptr->D_LL_MAGIC_NODE.prev->next = &__ptr->D_LL_MAGIC_NODE;\
		if (poped == __ptr) __ptr = NULL;\
	} while (0)

#define M_LL_POP_FRONT(__ptr, poped)\
	do {\
		if (!__ptr) break;\
		__ptr = M_LL_CONTAINER(&*__ptr->D_LL_MAGIC_NODE.next, typeof(*__ptr));\
		M_LL_POP_BACK(__ptr, poped);\
	} while (0)

#define M_LL_ERASE(__ptr)\
	do {\
		if (!__ptr) break;\
		typeof(*__ptr)*	__cur = NULL;\
		typeof(*__ptr)*	__end = __ptr;\
		do\
		{\
			__cur = __ptr;\
			__ptr = M_LL_CONTAINER(&*__ptr->D_LL_MAGIC_NODE.next, typeof(*__ptr));\
			free(__cur);\
		} while (__ptr != __end);\
		__ptr = NULL;\
	} while (0)

#define M_LL_FOR_EACH(__ptr, __data_ptr)\
	do {\
		if (!__ptr) break;\
		const struct ll_node*	__end = &__ptr->D_LL_MAGIC_NODE;\
		bool			__stop = true;\
		for (__data_ptr = __ptr; __stop;\
		     __data_ptr = M_LL_CONTAINER(&*__data_ptr->D_LL_MAGIC_NODE.next, typeof(*__data_ptr)),\
		     __stop = !(&__data_ptr->D_LL_MAGIC_NODE == __end))\
			do {\

#define M_LL_FOR_EACH_R(__ptr, __data_ptr)\
	do {\
		if (!__ptr) break;\
		const struct ll_node*	__end = &__ptr->D_LL_MAGIC_NODE;\
		bool			__stop = true;\
		for (__data_ptr = __ptr; __stop;\
		     __data_ptr = M_LL_CONTAINER(&*__data_ptr->D_LL_MAGIC_NODE.prev, typeof(*__data_ptr)),\
		     __stop = !(&__data_ptr->D_LL_MAGIC_NODE == __end))\
			do {\

#define M_LL_EACH_FOR\
		} while (0);\
	} while (0)

#endif
