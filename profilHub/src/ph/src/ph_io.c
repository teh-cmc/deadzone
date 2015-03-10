/**
 * .ph file I/O API
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

#include <ph_io.h>
#include <stdio.h>
#include <errors.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

bool
create_ph_file(const char* path)
{
	FILE*		fp = NULL;
	uint32_t	magic = D_PH_FILE_MAGIC_NUMBER;

	if (!path)
		return M_ERROR_BOOL(false, "no path given\n", 0);
	if (!(fp = fopen(path, "w")))
		return M_ERROR_BOOL(false, "could not open file %s: %s\n",
				    path, strerror(errno));
	if (fwrite(&magic, sizeof(magic), 1, fp) != 1)
	{
		/* man page doesn't state that errno is set but... anyway */
		M_ERROR("could not write .ph headers to file %s: %s\n", path, strerror(errno));
		if (fclose(fp))
			M_ERROR("could not close (and flush) stream to %s: %s\n",
				path, strerror(errno));
		if (unlink(path))
			M_ERROR("could not delete .ph file %s: %s\n", path, strerror(errno));
		return false;
	}
	if (fclose(fp))
		return M_ERROR_BOOL(false, "could not close (and flush) stream to %s: %s\n",
				    path, strerror(errno));
	return true;
}

bool
is_ph_file(const char* path)
{
	FILE*		fp = NULL;
	uint32_t	magic = 0;

	if (!path)
		return M_ERROR_BOOL(false, "no path given\n", 0);
	if (!(fp = fopen(path, "r")))
		return M_ERROR_BOOL(false, "could not open file %s: %s\n",
				    path, strerror(errno));
	if (fread(&magic, sizeof(magic), 1, fp) != 1)
		/* man page doesn't state that errno is set but... anyway */
		M_ERROR(false, "could not read .ph file %s headers: %s\n",
			path, strerror(errno));
	if (fclose(fp))
		return M_ERROR_BOOL(false, "could not close (and flush) stream to %s: %s\n",
				    path, strerror(errno));
	return magic == D_PH_FILE_MAGIC_NUMBER;
}
