/**
 * This class is used to load a scaled img
 * Copyright (C) 2013  Hugo Nedelec <hugo.nedelec@gmail.com>
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

#include <QPixmap>
#include <d_paths.h>
#include <d_design.h>
#include <QSize>
#include <errors.h>
#include <c_img.h>

using namespace	pH;

c_img::c_img(QWidget* father): QLabel(father)
{
}

c_img::~c_img(void)
{
}

/*
 * C_IMG PUBLIC METHODS
 */

bool	c_img::f_init(const char* image_path)
{
	QPixmap	pix;

	if (pix.load(image_path) == false)
		return M_ERROR_BOOL(false, "Couldn't load the image '%s'\n", image_path);
	this->setPixmap(pix.scaled(QSize(D_ICON_SIZE, D_ICON_SIZE)));
	return true;
}

void	c_img::mouseReleaseEvent(QMouseEvent*)
{
	emit clicked();
}

/*
 * C_IMG PROTECTED METHODS
 */

/*
 * C_IMG PRIVATE METHODS
 */
