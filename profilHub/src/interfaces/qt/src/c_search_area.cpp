/**
 * This is a search area
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

#include <c_search_area.h>
#include <QKeyEvent>
#include <d_constants.h>

using namespace	pH;

c_search_area::c_search_area(QWidget* father): QLineEdit(father)
{
}

c_search_area::~c_search_area(void)
{
}

/*
 * C_SEARCH_AREA PUBLIC METHODS
 */

bool	c_search_area::f_init(void)
{
	this->setPlaceholderText("Type text here\n");
	this->setFont(QFont("Times", 10, QFont::Bold));
	this->setMaxLength(D_TEXTBOX_MAX_LENGTH);
	return true;
}

void	c_search_area::keyPressEvent(QKeyEvent *ev)
{
	switch (ev->key())
	{
		case	Qt::Key_Return:
			emit submit();
			break;
		case	Qt::Key_Backspace:
			QLineEdit::keyPressEvent(ev);
			emit key_suppressed();
			break;
		default:
			QLineEdit::keyPressEvent(ev);
			emit key_pressed();
			break;
	}
}

/*
 * C_SEARCH_AREA PROTECTED METHODS
 */

/*
 * C_SEARCH_AREA PRIVATE METHODS
 */
