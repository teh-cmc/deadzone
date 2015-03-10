/**
 * Valgrind data structures
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

#ifndef __VALGRIND_DATA_STRUCTURES__
#define __VALGRIND_DATA_STRUCTURES__

#ifdef __cplusplus
extern "C" {
#endif

enum	vgd_error_type
{
	/* MEMCHECK */
	// free/delete invalid pointe
	E_FREE_INVALID,
	// new + free / malloc + delete
	E_FREE_MISMATCHED,
	// reading from invalid address
	E_READ_INVALID,
	// writing to invalid address
	E_WRITE_INVALID,
	// jumping to invalid address
	E_JUMP_INVALID,
	// invalid memory pool in client request
	E_MEMPOOL_INVALID,
	// calling syscall with invalid parameters
	E_SYSPARAMS_INVALID,
	// jumping condition depends on undefined value
	E_UNINIT_JUMP,
	// other condition depends on undefined value
	E_UNINIT_VALUE,
	// error resulting from a client check request
	E_CLIENT_CHECK_FAILURE,
	// memleak: blocks are lost
	E_LEAK_DEFINITELY,
	// memleak: all pointers to blocks are in leaked blocks
	E_LEAK_INDIRECT,
	// memleak: only interior pointers to blocks are still available
	E_LEAK_POSSIBLE,
	// memleak: pointers to unfreed blocks are still available
	E_LEAK_STILL_REACHABLE,
	/* SGCheck */
	// overrun of a stack or a global array
	E_STACK_ARRAY_OVERRUN,
	/* Helgrind */
	// data race
	E_RACE_CONDITION,
	// unlocking an unlocked lock
	E_UNLOCK_UNLOCKED,
	// unlocking a lock you do not own
	E_UNLOCK_FOREIGN,
	// unlocking an address which is not a lock
	E_UNLOCK_INVALID,
	// pthread failed, this is bad
	E_PTHREAD_FAILURE,
	// inconsistent lock order
	E_LOCK_ORDER,
	// helgrind miscellaneous error
	E_HELGRIND_MISC
};

struct	vgd_error_memcheck
{
	uint32_t	bytes;
	uint32_t	blocks;
};

struct	vgd_error_helgrind
{
	uint32_t	tid;
};

union	vgd_error_content
{
	struct vgd_error_memcheck	memcheck;
	struct vgd_error_helgrind	helgrind;
};

struct	vgd_error
{
	enum vgd_error_type	type;
	union vgd_error_content	content;
};

#ifdef __cplusplus
}
#endif

#endif
