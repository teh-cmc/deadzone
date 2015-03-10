/**
 * API to handle the use of valgrind and its various tools
 * - exec stuff -
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

#include <valgrind/exec.h>
#include <valgrind/parameters.h>
#include <valgrind/parsing.h>
#include <exec.h>
#include <unistd.h>
#include <errno.h>

int
__execute_and_get_fd(char** parameters)
{
	char		path[256];
	const char*	p[] = { NULL, NULL };
	const char**	a[] = { (const char**)parameters };

	if (!valgrind_valid_parameters(parameters))
		return M_ERROR_BOOL(false, "invalid parameters\n", 0);
	if (!get_program_path("valgrind", path, sizeof(path)))
		return M_ERROR_BOOL(false, "could not find valgrind\n", 0);
	p[0] = path;
	parameters[0] = NULL;
	return execute_mp(NULL, p, a);
}

bool
__treat_output(int fd)
{
	struct timeval	timeout;
	fd_set		r_set;
	int		ret = 0;

	FD_ZERO(&r_set);
	FD_SET(fd, &r_set);
	memset(&timeout, 0, sizeof(timeout));
	if ((ret = select(fd + 1, &r_set, NULL, NULL, &timeout)) == -1)
	{
		if (close(fd))
			M_ERROR("could not close file descriptor %u\n", fd);
		return M_ERROR_BOOL(false, "select() failure: %s\n", strerror(errno));
	}
	else if (!ret)
	{
		if (close(fd))
			M_ERROR_BOOL(false, "could not close file descriptor %u\n", fd);
		return true;
	}
	if (!(valgrind_parse_memcheck(fd)))
		return M_ERROR_BOOL(false, "could not parse output\n", 0);
	if (ret == -1)
	{
		if (close(fd))
			M_ERROR("could not close file descriptor %u\n", fd);
		return M_ERROR_BOOL(false, "read() failure: %s\n", strerror(errno));
	}
	if (close(fd))
		M_ERROR_BOOL(false, "could not close file descriptor %u\n", fd);
	return true;
}

bool
valgrind_execute(char** parameters)
{
	int	fd = __execute_and_get_fd(parameters);

	if (fd < 2)
		return M_ERROR_BOOL(false, "invalid fd returned\n", 0);
	if (!__treat_output(fd))
		return M_ERROR_BOOL(false, "could not treat output\n", 0);
	return true;
	(void)fd;
}
