/**
 * This class inherits from QLabel, and is used to manage our own tab imgs
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

#include <c_tab_img.h>
#include <QPixmap>
#include <d_design.h>
#include <QObject>
#include <errors.h>
#include <iostream>
#include <QMouseEvent>
#include <c_tab_displayer.h>

using namespace	pH;

c_tab_img::c_tab_img(QWidget* father): QLabel(father),
				       v_tab(NULL)
{
}

c_tab_img::~c_tab_img(void)
{
}

/*
 * C_TAB_IMG PUBLIC METHODS
 */

void	c_tab_img::mouseReleaseEvent(QMouseEvent* mouse_event)
{
	if (mouse_event->button() == Qt::LeftButton)
		if (this->v_tab != NULL)
			((c_tab_displayer*)this->parent()->parent())->f_close_tab(this->v_tab);
}

bool	c_tab_img::f_init(const char* image_path)
{
	QPixmap	pix;

	if (pix.load(image_path) == false)
		return M_ERROR_BOOL(false, "Couldn't load the image '%s'\n", image_path);
	this->setPixmap(pix.scaled(QSize(D_ICON_SIZE, D_ICON_SIZE)));
	return true;
}

/*
 * C_TAB_IMG PROTECTED METHODS
 */

/*
 * C_TAB_IMG PRIVATE METHODS
 */
