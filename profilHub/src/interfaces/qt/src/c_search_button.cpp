/**
 * This is the button used to activate the search
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

#include <c_search_button.h>
#include <QPixmap>
#include <d_paths.h>
#include <d_design.h>
#include <errors.h>
#include <QSize>

using namespace	pH;

c_search_button::c_search_button(QWidget* father): QLabel(father)
{
}

c_search_button::~c_search_button(void)
{
}

/*
 * C_SEARCH_BUTTON PUBLIC METHODS
 */

bool	c_search_button::f_init(void)
{
	QPixmap	pix;

	if (pix.load(D_SEARCH_BUTTON_PATH) == false)
		return M_ERROR_BOOL(false, "Couldn't load the image '%s'\n", D_SEARCH_BUTTON_PATH);
	this->setPixmap(pix.scaled(QSize(D_ICON_SIZE, D_ICON_SIZE)));
	return true;
}

/*
 * C_SEARCH_BUTTON PROTECTED METHODS
 */

/*
 * C_SEARCH_BUTTON PRIVATE METHODS
 */
