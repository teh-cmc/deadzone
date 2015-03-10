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

#ifndef __NS_INLINE__
#define __NS_INLINE__

#include <vector>
#include <stdint.h>
#include <ncurses.h>
#include <e_insertion_child.h>
#include <string.h>
#include <d_error.h>

#define D_RELATIVE_FILE			(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define	M_ERROR(ret, format, vargs...)	tools::f_debug_file_info_dev(ret, D_RELATIVE_FILE, __func__, __LINE__, format, vargs)
#define	M_ERROR_VOID(format, vargs...)	tools::f_debug_file_info_dev(true, D_RELATIVE_FILE, __func__, __LINE__, format, vargs)
#define	M_ERROR_NO_ARGS(ret, format)	tools::f_debug_file_info_dev(ret, D_RELATIVE_FILE, __func__, __LINE__, format)
#define	M_ERROR_VOID_NO_ARGS(format)	tools::f_debug_file_info_dev(true, D_RELATIVE_FILE, __func__, __LINE__, format)

namespace	tools
{
	//	use this function to see debug in the file "debug_ph"
	//	compile with debug define
	//	do command "tail -f debug_ph" in an other terminal to see in real time debug
	//	this function print debug
	void					f_debug_file(const char* format, ...);
	template <typename T> T			f_debug_file_info_dev(T ret, const char* file, const char* func, int line, const char* format, ...);

	bool					f_debug_file(const char* format, va_list* vargs);
#ifdef	D_DEBUG_ON
	bool					f_open_debug_file(void);
#endif
	uintmax_t				f_strlen(const char* str);
	char*					f_strdup(const char* str);
	char					f_strcmp(const char* src, const char* cmp);
	char					f_strncmp(const char* src, const char* cmp, unsigned int size);
	void					f_strcpy(char* dest, const char* src);
	void					f_strncpy(char* dest, const char* src, unsigned int size);
	char*					f_strcat(char* dest_str, const char* src_str);
	char*					f_strncat(char* dest, const char* src, unsigned int len);
	template <typename T> T			f_abs(T a);
	template <typename T> void		f_delete_ptr(T& ptr);
	template <typename T> void		f_delete_aptr(T& ptr);
	template <typename T> void		f_delete_tab_aptr(T& ptr, int size);
	template <typename T> void		f_delete_ptr_container(T& container);
	template <typename T> void		f_memset(T* addr, uintmax_t size, uint8_t value);
	template <typename T, typename U> bool	f_push_in_container(T* container, U obj, e_insertion_child insertion);
	template <typename T, typename U> void	f_memcpy(const T* from, U* to, uintmax_t size);
	template <typename T, typename U> bool	f_memcmp(const T* a, const U* b, uintmax_t size);
	bool					f_my_wresize(WINDOW* win, int height, int width);
	bool					f_my_mvwin(WINDOW* win, int y, int x);
	bool					f_my_mvwaddnstr(WINDOW* win, int min_w_win, int y, int x, const char* str, int n = -1);
	bool					f_my_mvwaddch(WINDOW* win, int y, int x, const chtype c);
	bool					f_my_border(WINDOW* win);
	template <typename T> int		f_nb_element(T* array);
	char*					f_itoa(int num);
	void					f_itoa_fill(int num, char* ret, int a);
	void					f_print_str(int fd, const char* str);
	void					f_print_err(const char* str);
	bool					f_printable_character(char c);
	int					f_atoi(const char* str);
}

#include <tools.hpp>

#endif
