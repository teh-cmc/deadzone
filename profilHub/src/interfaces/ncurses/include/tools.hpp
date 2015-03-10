/**
 * Copyright (C) 2013 Jean Hasdenteufel <jeanhasdenteufel@gmail.com>
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

#ifndef __NS_TOOLS_HPP__
#define __NS_TOOLS_HPP__

#include <unistd.h>

#ifdef D_DEBUG_ON

#define D_FILE_DEBUG	"debug_ph"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern FILE*	g_file_debug;
#endif

inline void	tools::f_debug_file(const char* format, ...)
{
#ifdef	D_DEBUG_ON
	va_list	vargs;

	if (tools::f_open_debug_file() == false)
		return ;
	va_start(vargs, format);
	vfprintf(g_file_debug, format, vargs);
	va_end(vargs);
	if (fflush(g_file_debug) != 0)
		return ;
#else
	(void)format;
#endif
}

inline bool	tools::f_debug_file(const char* format, va_list* vargs)
{
#ifdef	D_DEBUG_ON
	if (tools::f_open_debug_file() == false)
		return false;
	vfprintf(g_file_debug, format, *vargs);
	if (fflush(g_file_debug) != 0)
		return false;
#else
	(void)format;
	(void)vargs;
#endif
	return true;
}

template <typename T>
inline T	tools::f_debug_file_info_dev(T ret, const char* file, const char* func, int line, const char* format, ...)
{
#ifdef	D_DEBUG_ON
	va_list	vargs;

	if (tools::f_open_debug_file() == false)
		return ret;
	if (fprintf(g_file_debug, "\nFile: %s\nFunc: %s\nLine: %d\n", file, func, line) == -1)
		return ret;
	va_start(vargs, format);
	if (tools::f_debug_file(format, &vargs) == false)
	{
		va_end(vargs);
		return ret;
	}
	va_end(vargs);
	if (fflush(g_file_debug) != 0)
		return ret;
#else
	(void)file;
	(void)func;
	(void)line;
	(void)format;
#endif
	return ret;
}

#ifdef	D_DEBUG_ON
inline bool	tools::f_open_debug_file(void)
{
	if (g_file_debug == NULL)
	{
		g_file_debug = fopen(D_FILE_DEBUG, "a");
		if (g_file_debug == NULL)
			return false;
		tools::f_debug_file("Welcome in profilHub debug ui ncurses.\n"
				    "<========== Beging program ==========>\n");
		if (fflush(g_file_debug) != 0)
			return false;
	}
	return true;
}
#endif

inline uintmax_t	tools::f_strlen(const char* string)
{
	uintmax_t	i;

	for (i = 0; string[i]; ++i)
		;
	return i;
}

inline char*	tools::f_strdup(const char* str)
{
	char*	dup;

	if (!str)
		return (NULL);
	dup = new (std::nothrow) char[tools::f_strlen(str) + 1];
	if (dup == NULL)
		return (NULL);
	tools::f_strcpy(dup, str);
	dup[tools::f_strlen(str)] = '\0';
	return (dup);
}

inline char	tools::f_strcmp(const char* src, const char* cmp)
{
	int	i;

	i = 0;
	while (*(src + i) && *(src + i) == *(cmp + i))
		++i;
	if (*(src + i) < *(cmp + i))
		return (-1);
	else if (*(src + i) > *(cmp + i))
		return (1);
	return (0);
}

inline char	tools::f_strncmp(const char* src, const char* cmp, unsigned int size)
{
	unsigned int	i;

	if (!src || !cmp || size == 0)
		return (0);
	i = 0;
	while (*(src + i) == *(cmp + i) && i < size)
		i++;
	if (i == size)
		return (0);
	else if (*(src + i) < *(cmp + i))
		return (-1);
	return (1);
}

inline void	tools::f_strcpy(char* dest, const char* src)
{
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = 0;
}

inline void	tools::f_strncpy(char* dest,  const char* src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (*src && i < size)
	{
		*dest = *src;
		++dest;
		++src;
		i++;
	}
}

inline char*	tools::f_strcat(char* dest_str, const char* src_str)
{
	int	size;
	int	i;

	i = 0;
	size = tools::f_strlen(dest_str);
	while (src_str[i] != 0)
	{
		dest_str[size + i] = src_str[i];
		i = i + 1;
	}
	dest_str[size + i] = 0;
	return dest_str;
}

inline char*	tools::f_strncat(char* dest, const char* src, unsigned int len)
{
	unsigned int	i;
	unsigned int	destlen;

	destlen = tools::f_strlen(dest);
	i = 0;
	while (*(src + i) != '\0' && i < len)
	{
		*(dest + destlen) = *(src + i);
		destlen++;
		i++;
	}
	*(dest + destlen) = '\0';
	return (dest);
}

#endif

template <typename T>
inline T	tools::f_abs(T a)
{
	return (((a) < 0) ? -(a) : (a));
}

template <typename T>
inline void	tools::f_delete_ptr(T& ptr)
{
	if (ptr)
		delete ptr;
	ptr = NULL;
}

template <typename T>
inline void	tools::f_delete_aptr(T& ptr)
{
	if (ptr)
		delete [] ptr;
	ptr = NULL;
}

template <typename T>
inline void	tools::f_delete_tab_aptr(T& ptr, int size)
{
	int	i;

	if ((ptr == NULL) || (size <= 0))
		return ;
	i = 0;
	while (i < size)
	{
		tools::f_delete_aptr(ptr[i]);
		++i;
	}
	tools::f_delete_aptr(ptr);
}

template<typename T>
inline void	tools::f_delete_ptr_container(T& container)
{
	uint32_t	i, size;

	i = 0;
	size = container.size();
	while (i < size)
	{
		f_delete_ptr(container[i]);
		++i;
	}
	container.clear();
}

template <typename T>
inline void	tools::f_memset(T* addr, uintmax_t size, uint8_t value)
{
	for (uintmax_t i = 0; i < size; ++i)
		((uint8_t*)addr)[i] = value;
}

template <typename T, typename U>
inline bool	tools::f_push_in_container(T* container, U obj, e_insertion_child insertion)
{
	try
	{
		if (insertion == E_PUSH_BACK_INSERTION)
			container->push_back(obj);
		else if (insertion == E_PUSH_FRONT_INSERTION)
			container->insert(container->begin(), obj);
		else
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

template <typename T, typename U>
inline void	tools::f_memcpy(const T* from, U* to, uintmax_t size)
{
	for (uintmax_t i = 0; i < size; ++i)
		((uint8_t*)to)[i] = ((uint8_t*)from)[i];
}

template <typename T, typename U>
inline bool	tools::f_memcmp(const T* a, const U* b, uintmax_t size)
{
	for (uintmax_t i = 0; i < size; ++i)
		if (((uint8_t*)a)[i] != ((uint8_t*)b)[i])
			return false;
	return true;
}

inline bool	tools::f_my_wresize(WINDOW* win, int height, int width)
{
	if (height <= 0 || height > getmaxy(stdscr) ||
	    width <= 0 || width > getmaxx(stdscr))
		return true;
	return (wresize(win, height, width) != ERR);
}

inline bool	tools::f_my_mvwin(WINDOW* win, int y, int x)
{
	if (y < 0 || y >= getmaxy(stdscr) ||
	    x < 0 || x >= getmaxx(stdscr))
		return true;
	if (mvwin(win, y, x) == ERR)
		return false;
	return true;
}

inline bool	tools::f_my_mvwaddnstr(WINDOW* win, int min_w_win, int y, int x, const char* str, int n)
{
	if (((min_w_win != -1) && (getmaxx(win) < min_w_win)) ||
	    x < 0 || x >= getmaxx(win) ||
	    y < 0 || y >= getmaxy(win))
		return true;
	if (mvwaddnstr(win, y, x, str, n) == ERR)
		return false;
	return true;
}

inline bool	tools::f_my_mvwaddch(WINDOW* win, int y, int x, const chtype c)
{
	if (x < 0 || x >= getmaxx(win) ||
	    y < 0 || y >= getmaxy(win))
		return true;
	if (mvwaddch(win, y, x, c) == ERR)
		return false;
	return true;
}

inline bool	tools::f_my_border(WINDOW* win)
{
	if (box(win, 0, 0) == ERR)
		return false;
	return true;
}

template <typename T>
inline int	tools::f_nb_element(T* array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		++i;
	return i;
}

inline char*	tools::f_itoa(int num)
{
	int	a;
	int	size;
	char*	ret;

	a = 1;
	size = 1;
	while (num / a >= 10 || num / a <= -10)
	{
		a = a * 10;
		size = size + 1;
	}
	if (num < 0)
		size = size + 1;
	ret = new (std::nothrow) char[size + 1];
	if (ret == NULL)
		return (NULL);
	tools::f_itoa_fill(num, ret, a);
	return (ret);
}

inline void	tools::f_itoa_fill(int num, char* ret, int a)
{
	int	i;

	i = 0;
	if (num < 0)
	{
		ret[0] = '-';
		i = 1;
	}
	while (a > 0)
	{
		if (num < 0)
			ret[i] = (num / a % 10 * -1 + '0');
		else
			ret[i] = (num / a % 10 + '0');
		a = a / 10;
		i = i + 1;
	}
	ret[i] = 0;
}

inline void	tools::f_print_str(int fd, const char* str)
{
	if (write(fd, str, tools::f_strlen(str)) == -1)
	{}
}

inline void	tools::f_print_err(const char* str)
{
	tools::f_print_str(2, str);
}

inline bool	tools::f_printable_character(char c)
{
	return ((c >= ' ') && (c <= '~'));
}

inline int	tools::f_atoi(const char* str)
{
	int	number;
	int	neg;

	if (!str)
		return -1;
	neg = 0;
	number = 0;
	while (*str)
	{
		if (*str <= '9' && *str >= '0')
			number = number * 10 + (*str) - '0';
		else if (*str == '-')
			neg = neg + 1;
		str = str + 1;
	}
	if (neg % 2)
		return -number;
	else
		return number;
}
