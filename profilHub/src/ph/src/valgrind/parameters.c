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

#include <valgrind/parameters.h>

const char*	g_valgrind_general_parameters[D_VALGRIND_GENERAL_PARAMETERS] =
				   {
				/*I*/"--trace-children=no",
				/*I*/"--child-silent-after-fork=yes",
				/*I*/"--vgdb=no",
				     "--track-fds",
				     "--time-stamp",
				/*I*/"--log-fd=-1",
				/*I*/"--xml",
				/*D*/"--xml-fd",
				/*I*/"--demangle=yes",
				/*I*/"--num-callers=50",
				/*I*/"--error-limit=no",
				/*I*/"--show-below-main=no",
				/*I*/"--fullpath-after=",
				/*I*/"--read-var-info=yes",
				/*I*/"--run-libc-freeres=yes"
				   };

const char*	g_valgrind_memcheck_parameters[D_VALGRIND_MEMCHECK_PARAMETERS] =
				   {
				/*I*/"--leak-check=full",
				/*I*/"--show-possibly-lost=yes",
				/*I*/"--leak-resolution=high",
				     "--show-reachable",
				/*I*/"--undef-value-errors=yes",
				/*D*/"--track-origins=yes",
				/*I*/"--partial-loads-ok=no",
				     "--workaround-gcc296-bugs"
				   };

static inline
bool
__change_general_parameter_yes_no(char** parameters, uint32_t ptype, int32_t value)
{
	char	tmp[256];

	if (!parameters || !parameters[ptype + 2])
		return M_ERROR_BOOL(false, "parameter is pointing to NULL\n", 0);
	if (value < 0 || value > 1)
		return M_ERROR_BOOL(false, "invalid value\n", 0);
	free(parameters[ptype + 2]);
	if (value && snprintf(tmp, sizeof(tmp), "%s=yes",
	    g_valgrind_general_parameters[ptype]) < 0)
		return M_ERROR_BOOL(false, "snprintf failure\n", 0);
	else if (!value && snprintf(tmp, sizeof(tmp), "%s=no",
		 g_valgrind_general_parameters[ptype]) < 0)
		return M_ERROR_BOOL(false, "snprintf failure\n", 0);
	if (!(parameters[ptype + 2] = strndup(tmp, sizeof(tmp))))
		return M_ERROR_BOOL(false, "strndup failure\n", 0);
	return true;
}

static inline
bool
__change_tool_parameter_yes_no(char** parameters, uint32_t ptype, int32_t value)
{
	char		tmp[256];
	const char**	parray = NULL;

	switch ((uintptr_t)*parameters)
	{
		case D_VALGRIND_TOOL_MEMCHECK:
			parray = g_valgrind_memcheck_parameters;
			break;
		default:
			return M_ERROR_BOOL(false, "no such parameters array\n", 0);
	}
	if (!parameters || !parameters[ptype + D_VALGRIND_GENERAL_PARAMETERS + 2])
		return M_ERROR_BOOL(false, "parameter is pointing to NULL\n", 0);
	if (value < 0 || value > 1)
		return M_ERROR_BOOL(false, "invalid value\n", 0);
	free(parameters[ptype + D_VALGRIND_GENERAL_PARAMETERS + 2]);
	if (value && snprintf(tmp, sizeof(tmp), "%s=yes", parray[ptype]) < 0)
		return M_ERROR_BOOL(false, "snprintf failure\n", 0);
	else if (!value && snprintf(tmp, sizeof(tmp), "%s=no", parray[ptype]) < 0)
		return M_ERROR_BOOL(false, "snprintf failure\n", 0);
	if (!(parameters[ptype + D_VALGRIND_GENERAL_PARAMETERS + 2] = strndup(tmp, sizeof(tmp))))
		return M_ERROR_BOOL(false, "strndup failure\n", 0);
	return true;
}

static inline
bool
__change_memcheck_parameter(char** parameters, uint32_t ptype, int32_t value)
{
	switch (ptype)
	{
		case D_VALGRIND_P_WORKAROUND_GCC296_BUGS:
		case D_VALGRIND_P_SHOW_REACHABLE:
			return __change_tool_parameter_yes_no(parameters, ptype, value);
		case D_VALGRIND_P_LEAK_CHECK:
		case D_VALGRIND_P_SHOW_POSSIBLY_LOST:
		case D_VALGRIND_P_LEAK_RESOLUTION:
		case D_VALGRIND_P_UNDEF_VALUE_ERRORS:
		case D_VALGRIND_P_TRACK_ORIGINS:
		case D_VALGRIND_P_PARTIAL_LOADS_OK:
			return M_ERROR_BOOL(false, "this memcheck parameter is immutable\n", 0);
		default:
			return M_ERROR_BOOL(false, "no such memcheck parameter type\n", 0);
	}
	return false;
}

bool
valgrind_change_general_parameter(char** parameters, uint32_t ptype, int32_t value)
{
	switch (ptype)
	{
		case D_VALGRIND_P_TRACK_FDS:
		case D_VALGRIND_P_TIME_STAMP:
			return __change_general_parameter_yes_no(parameters, ptype, value);
		case D_VALGRIND_P_TRACE_CHILDREN:
		case D_VALGRIND_P_CHILD_SILENT_AFTER_FORK:
		case D_VALGRIND_P_VGDB:
		case D_VALGRIND_P_XML_FD:
		case D_VALGRIND_P_LOG_FD:
		case D_VALGRIND_P_XML:
		case D_VALGRIND_P_DEMANGLE:
		case D_VALGRIND_P_NUM_CALLERS:
		case D_VALGRIND_P_ERROR_LIMIT:
		case D_VALGRIND_P_SHOW_BELOW_MAIN:
		case D_VALGRIND_P_FULLPATH_AFTER:
		case D_VALGRIND_P_READ_VAR_INFOS:
		case D_VALGRIND_P_RUN_LIBC_FREERES:
			return M_ERROR_BOOL(false, "this general parameter is immutable\n", 0);
		default:
			return M_ERROR_BOOL(false, "no such general parameter type\n", 0);
	}
	return false;
}

bool
valgrind_change_tool_parameter(char** parameters, uint32_t ptype, int32_t value)
{
	switch ((uintptr_t)*parameters)
	{
		case D_VALGRIND_TOOL_MEMCHECK:
			return __change_memcheck_parameter(parameters, ptype, value);
		default:
			return M_ERROR_BOOL(false, "no such tool\n", 0);
	}
	return false;
}

bool
valgrind_valid_parameters(char* const* parameters)
{
	switch ((uintptr_t)*parameters)
	{
		case D_VALGRIND_TOOL_MEMCHECK:
			return !strcmp(M_VALGRIND_TOOL_PARAMETER_OFFSET(parameters),
				       "memcheck");
		default:
			return M_ERROR_BOOL(false, "invalid valgrind tool\n", 0);
	}
	return true;
}
