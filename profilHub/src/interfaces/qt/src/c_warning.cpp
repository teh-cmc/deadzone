/**
 * This is the warning class widget
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

#include <c_warning.h>
#include <QListWidgetItem>
#include <QFont>

using namespace	pH;

c_warning::c_warning(QWidget* father, QListWidgetItem* widget_item, const char* title): QLabel(title, father),
											__v_here(true),
											__v_widget_item(widget_item)
{
}

c_warning::~c_warning(void)
{
	delete this->__v_widget_item;
}

/*
 * C_WARNING PUBLIC METHODS
 */

QListWidgetItem*	c_warning::f_widget_item(void)
{
	return this->__v_widget_item;
}

bool	c_warning::f_init(void)
{
	this->setFont(QFont("Times", 10, QFont::Bold));
	return true;
}

bool	c_warning::f_search(const char* search)
{
	if (strlen(search) == 0 ||
	    strstr(this->text().toLocal8Bit().data(), search) != NULL)
		return true;
	return false;
}

bool	c_warning::f_filter(const char* filter)
{
	if (strstr(this->text().toLocal8Bit().data(), filter) != NULL)
	{
		this->__v_here = false;
		return true;
	}
	return false;
}

bool	c_warning::f_unfilter(const char* filter)
{
	if (strstr(this->text().toLocal8Bit().data(), filter) != NULL)
	{
		this->__v_here = true;
		return true;
	}
	return false;
}

bool	c_warning::f_here(void)
{
	return this->__v_here;
}

/*
 * C_WARNING PROTECTED METHODS
 */

/*
 * C_WARNING PRIVATE METHODS
 */
