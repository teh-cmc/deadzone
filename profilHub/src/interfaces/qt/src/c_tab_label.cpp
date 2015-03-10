/**
 * This class inherits from QLabel, and is used to manage our own tab labels
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

#include <c_tab_label.h>
#include <QPalette>
#include <c_tab_displayer.h>

using namespace	pH;

c_tab_label::c_tab_label(QString title, QWidget* father): QLabel(title, father)
{
	this->setAlignment(Qt::AlignHCenter);
}

c_tab_label::~c_tab_label(void)
{
}

/*
 * C_TAB_HEADER PUBLIC METHODS
 */

void	c_tab_label::mousePressEvent(QMouseEvent*)
{
	((c_tab_displayer*)this->parent()->parent())->f_select_tab(this->v_tab);
}

void	c_tab_label::show(void)
{
	QPalette	pal(this->palette());

	pal.setColor(QPalette::Background, QColor(qRgb(255, 163, 71)));
	this->setAutoFillBackground(true);
	this->setPalette(pal);
}

void	c_tab_label::hide(void)
{
	QPalette	pal(this->palette());

	pal.setColor(QPalette::Background, QColor(qRgb(212, 208, 200)));
	this->setAutoFillBackground(true);
	this->setPalette(pal);
}

/*
 * C_TAB_HEADER PROTECTED METHODS
 */

/*
 * C_TAB_HEADER PRIVATE METHODS
 */
