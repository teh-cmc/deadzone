/**
 * API to handle the use of valgrind and its various tools
 * - parameters stuff -
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

#ifndef __VALGRIND_PARAMETERS__
#define __VALGRIND_PARAMETERS__

#include <stdlib.h>
#include <string.h>
#include <errors.h>
#include <stdint.h>
#include <strstuff.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * GENERAL PARAMETERS
**/

#define D_VALGRIND_GENERAL_PARAMETERS	15

extern const char*	g_valgrind_general_parameters[D_VALGRIND_GENERAL_PARAMETERS];

/* trace children too (immutable) */
#define D_VALGRIND_P_TRACE_CHILDREN		0
/* children are naturally silent (immutable) */
#define D_VALGRIND_P_CHILD_SILENT_AFTER_FORK	1
/* enable gdbserver (immutable) */
#define D_VALGRIND_P_VGDB			2
/* track open descriptors */
#define D_VALGRIND_P_TRACK_FDS			3
/* timestamp everything */
#define D_VALGRIND_P_TIME_STAMP			4
/* fd to print uninteresting things (immutable) */
#define D_VALGRIND_P_LOG_FD			5
/* output to XML (immutable) */
#define D_VALGRIND_P_XML			6
/* descriptor to redirect XML output to (depends on D_VALGRIND_P_XML) */
#define D_VALGRIND_P_XML_FD			7
/* demangle C++ names (immutable) */
#define D_VALGRIND_P_DEMANGLE			8
/* maximum number of entries in stack traces (immutable) */
#define D_VALGRIND_P_NUM_CALLERS		9
/* give up after a certain amount of errors (immutable) */
#define D_VALGRIND_P_ERROR_LIMIT		10
/* trace even before main() (immutable) */
#define D_VALGRIND_P_SHOW_BELOW_MAIN		11
/* show complete path instead of just names (immutable) */
#define D_VALGRIND_P_FULLPATH_AFTER		12
/* get more infos about variables causing issues (immutable) */
#define D_VALGRIND_P_READ_VAR_INFOS		13
/* free libc at exit to avoid reporting fake leaks (immutable) */
#define D_VALGRIND_P_RUN_LIBC_FREERES		14

/**
 * MEMCHECK PARAMETERS
**/

#define D_VALGRIND_MEMCHECK_PARAMETERS	8

extern const char*	g_valgrind_memcheck_parameters[D_VALGRIND_MEMCHECK_PARAMETERS];

/* describe each memleak (immutable) */
#define D_VALGRIND_P_LEAK_CHECK			0
/* also show possibly lost blocks (immutable) */
#define D_VALGRIND_P_SHOW_POSSIBLY_LOST		1
/* precision used to merge leaks (immutable) */
#define D_VALGRIND_P_LEAK_RESOLUTION		2
/* show still reachable blocks */
#define D_VALGRIND_P_SHOW_REACHABLE		3
/* report uses of undefined values (immutable) */
#define D_VALGRIND_P_UNDEF_VALUE_ERRORS		4
/* track origins of undefined values (depends on D_VALGRIND_P_UNDEF_VALUE_ERRORS) */
#define D_VALGRIND_P_TRACK_ORIGINS		5
/* in short, be kind with illegal addresses (immutable) */
#define D_VALGRIND_P_PARTIAL_LOADS_OK		6
/* fix GCC 2.96 stack pointer bugs */
#define D_VALGRIND_P_WORKAROUND_GCC296_BUGS	7

/**
 * TOOLS IDENTIFIERS
**/

#define M_VALGRIND_TOOL_PARAMETER_OFFSET(p)\
	(p[1] + 7)

#define D_VALGRIND_TOOL_MEMCHECK	1000

/**
 * DEFAULT PARAMETERS DEFINITION MACROS
**/

#define M_VALGRIND_MEMCHECK_DEFAULT_PARAMETERS(__params_name, __target)\
	char**	__params_name = NULL;\
	do {\
		uintmax_t	__i = 0;\
		M_STRSTUFF_STRING_CUT(__target_cut, __target, " ");\
		if (!*__target_cut)\
			break;\
		if (!(__params_name = calloc(sizeof(*__params_name), 27 + string_array_size(__target_cut))))\
			break;\
		__params_name[0] = (char*)D_VALGRIND_TOOL_MEMCHECK;\
		if (!(__params_name[1] = strdup("--tool=memcheck")) ||\
		    !(__params_name[2] = strdup("--trace-children=no")) ||\
		    !(__params_name[3] = strdup("--child-silent-after-fork=yes")) ||\
		    !(__params_name[4] = strdup("--vgdb=no")) ||\
		    !(__params_name[5] = strdup("--track-fds=yes")) ||\
		    !(__params_name[6] = strdup("--time-stamp=no")) ||\
		    !(__params_name[7] = strdup("--log-fd=-1")) ||\
		    !(__params_name[8] = strdup("--xml=yes")) ||\
		    !(__params_name[9] = strdup("--xml-fd=1")) ||\
		    !(__params_name[10] = strdup("--demangle=yes")) ||\
		    !(__params_name[11] = strdup("--num-callers=50")) ||\
		    !(__params_name[12] = strdup("--error-limit=no")) ||\
		    !(__params_name[13] = strdup("--show-below-main=no")) ||\
		    !(__params_name[14] = strdup("--fullpath-after=")) ||\
		    !(__params_name[15] = strdup("--read-var-info=yes")) ||\
		    !(__params_name[16] = strdup("--run-libc-freeres=yes")) ||\
		    !(__params_name[17] = strdup("--leak-check=full")) ||\
		    !(__params_name[18] = strdup("--show-possibly-lost=yes")) ||\
		    !(__params_name[19] = strdup("--leak-resolution=high")) ||\
		    !(__params_name[20] = strdup("--show-reachable=yes")) ||\
		    !(__params_name[21] = strdup("--undef-value-errors=yes")) ||\
		    !(__params_name[22] = strdup("--track-origins=yes")) ||\
		    !(__params_name[23] = strdup("--partial-loads-ok=no")) ||\
		    !(__params_name[24] = strdup("--workaround-gcc296-bugs=no")))\
		{\
			M_VALGRIND_ANNIHILATE_PARAMETERS(__params_name);\
			break;\
		}\
		while (__target_cut[__i])\
		{\
			if (!(__params_name[25 + __i] = strdup(__target_cut[__i])))\
			{\
				M_VALGRIND_ANNIHILATE_PARAMETERS(__params_name);\
				break;\
			}\
			++__i;\
		}\
	} while (0)

#define M_VALGRIND_ANNIHILATE_PARAMETERS(__params_name)\
	do {\
		uintmax_t	__i = 1;\
		while (__params_name[__i])\
			free(__params_name[__i++]);\
		free(__params_name);\
		__params_name = NULL;\
	} while (0)

bool	valgrind_change_general_parameter(char** parameters, uint32_t ptype, int32_t value);
bool	valgrind_change_tool_parameter(char** parameters, uint32_t ptype, int32_t value);
bool	valgrind_valid_parameters(char* const* parameters);

#ifdef __cplusplus
}
#endif

#endif
