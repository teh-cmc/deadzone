/**
 * Facilitate the execution of a program with the given arguments
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

#include <sys/select.h>
#include <exec.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <errors.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

static inline
void
__fill_args(const char* args[], const char* program, va_list ap, uintmax_t total)
{
	uintmax_t	i = 1;

	args[0] = program;
	while (i < total)
		args[i++] = va_arg(ap, const char*);
	args[i] = NULL;
}

static inline
bool
__execute(const char* args[], const char** env)
{
	pid_t	ret;

	if (!(ret = fork()))
	{
		if (execve(*args, (char* const*)args, (char* const*)env))
		{
			M_ERROR("could not execute %s: %s\n", *args, strerror(errno));
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (ret == -1)
		return M_ERROR_BOOL(false, "could not fork: %s\n", strerror(errno));
	if (waitpid(ret, NULL, 0) == -1)
		return M_ERROR_BOOL(false, "could not wait for pid %i: %s\n", ret,
				    strerror(errno));
	return true;
}

static inline
bool
__execute_p(const char* args[], const char** env, const char* prev, int p[2])
{
	pid_t	ret;
	int	pn[2];

	if (pipe(pn))
		return M_ERROR_BOOL(false, "could not create pipe: %s\n", strerror(errno));
	if (!(ret = fork()))
	{
		close(p[1]);
		if (dup2(pn[1], STDOUT_FILENO) == -1)
			return M_ERROR_BOOL(false, "could not redirect stdout: %s\n",
					    strerror(errno));
		if (prev)
		{
			if (dup2(p[0], STDIN_FILENO) == -1)
				return M_ERROR_BOOL(false, "could not redirect stdin: %s\n",
						    strerror(errno));
		}
		else
			close(p[0]);
		if (execve(*args, (char* const*)args, (char* const*)env))
		{
			M_ERROR("could not execute %s: %s\n", *args, strerror(errno));
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	close(p[0]);
	close(p[1]);
	if (ret == -1)
		return M_ERROR_BOOL(false, "could not fork: %s\n", strerror(errno));
	if (waitpid(ret, NULL, 0) == -1)
		return M_ERROR_BOOL(false, "could not wait for pid %i: %s\n", ret,
				    strerror(errno));
	memcpy(p, pn, sizeof(*p) * 2);
	return true;
}

bool
execute(const char** env, const char* program, uintmax_t total, ...)
{
	const char*	args[total + 2];
	va_list		ap;

	va_start(ap, total);
	__fill_args(args, program, ap, total + 1);
	va_end(ap);
	return __execute((const char**)args, env);
}

bool
execute_a(const char** env, const char* program_args[])
{
	return __execute((const char**)program_args, env);
}

bool
execute_m(const char** env, const char* programs[], const char** args[])
{
	while (*programs)
	{
		**args = *programs++;
		if (!__execute(*args++, env))
			return false;
	}
	return true;
}

int
execute_mp(const char** env, const char* programs[], const char** args[])
{
	const char*	prev = NULL;
	int		p[2];

	if (pipe(p))
		return M_ERROR_INT(0, "could not create pipe: %s\n", strerror(errno));
	while (*programs)
	{
		**args = *programs;
		if (!__execute_p(*args++, env, prev, p))
			return 0;
		prev = *programs++;
	}
	close(p[1]);
	return p[0];
}

bool
get_program_path(const char* program, char path[], uintmax_t path_size)
{
	const char*	p[] = { "/usr/bin/env", 0 };
	const char**	a[] = { (const char*[]){ 0, "which", program, 0 } };
	struct timeval	timeout;
	int		fd = 0;
	fd_set		r_set;
	int		ret = 0;

	if (path_size < 1)
		return M_ERROR_BOOL(false, "path_size must be > 0 (path_size == %i)\n", path_size);
	memset(path, 0, path_size);
	if ((fd = execute_mp(NULL, p, a)) < 2)
		return false;
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
	if ((ret = read(fd, path, path_size - 1)) == -1)
	{
		if (close(fd))
			M_ERROR("could not close file descriptor %u\n", fd);
		return M_ERROR_BOOL(false, "read() failure: %s\n", strerror(errno));
	}
	/* this is weird, just a dirty fix for now */
	if (path[ret - 1] == '\n' || path[ret - 1] == '\r')
		path[ret - 1] = 0;
	if (close(fd))
		M_ERROR_BOOL(false, "could not close file descriptor %u\n", fd);
	return true;
}

bool
program_available(const char* program)
{
	char	available[2];

	if (!get_program_path(program, available, 2))
		return false;
	return strlen(available);
}

bool
debug_symbols_available(const char* executable)
{
	const char*	p[] = { "/usr/bin/env", "/usr/bin/env", 0 };
	const char**	a[] = { (const char*[]){ 0, "nm", "-a", executable, 0 },
				(const char*[]){ 0, "grep", " N .debug_", 0 },
			      };
	struct timeval	timeout;
	int		fd = 0;
	fd_set		r_set;
	int		ret = 0;

	if ((fd = execute_mp(NULL, p, a)) < 0)
		return false;
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
			M_ERROR("could not close file descriptor %u\n", fd);
		return false;
	}
	if ((ret = read(fd, &ret, 1)) == -1)
	{
		if (close(fd))
			M_ERROR("could not close file descriptor %u\n", fd);
		return M_ERROR_BOOL(false, "read() failure: %s\n", strerror(errno));
	}
	if (close(fd))
		M_ERROR_BOOL(false, "could not close file descriptor %u\n", fd);
	return ret;
}
