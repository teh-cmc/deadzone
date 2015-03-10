/**
 * This is the area where every filters will be displayed
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

#include <c_filter_lister.h>
#include <QListWidgetItem>
#include <QLabel>
#include <c_filter.h>
#include <d_design.h>
#include <c_warning_lister.h>
#include <errors.h>

using namespace	pH;

c_filter_lister::c_filter_lister(QWidget* father, c_warning_lister* warning_lister): QListWidget(father),
										     __v_warning_lister(warning_lister)
{
}

c_filter_lister::~c_filter_lister(void)
{
	this->__f_delete_filters();
}

/*
 * C_FILTER_LISTER PUBLIC METHODS
 */

bool	c_filter_lister::f_init(void)
{
	QPalette	pal = this->palette();

	pal.setColor(QPalette::Highlight, QColor(qRgb(255, 163, 71)));
	this->setPalette(pal);
	return true;
}

void	c_filter_lister::f_remove_filter(void)
{
	std::list<c_filter*>::iterator	it;
	std::list<c_filter*>::iterator	end;
	c_filter*			filter;

	filter = (c_filter*)QObject::sender()->parent();
	it = this->__v_filter_list.begin();
	end = this->__v_filter_list.end();
	while (it != end)
	{
		if (*it == filter)
		{
			this->__v_warning_lister->f_unfilter(filter->f_label()->text().toLocal8Bit().data());
			this->__v_filter_list.erase(it);
			this->takeItem(this->row(filter->f_widget_item()));
			delete filter;
			break;
		}
		++it;
	}
}

bool	c_filter_lister::f_add_filter(const char* title)
{
	c_filter*		filter;
	QListWidgetItem*	list_item;

	if (title == NULL || strlen(title) == 0 ||
	    this->__f_filter_already_exists(title) == true)
		return false;
	filter = NULL;
	list_item = NULL;
	try
	{
		list_item = new QListWidgetItem(this);
		filter = new c_filter(this, list_item, title);
		if (filter->f_init() == false)
			throw -1;
		this->__v_filter_list.push_back(filter);
		list_item->setSizeHint(QSize(0, filter->height() + D_ICON_SIZE));
		this->addItem(list_item);
		this->setItemWidget(list_item, filter);
	}
	catch (...)
	{
		delete filter;
		delete list_item;
		return M_ERROR_BOOL(false, "Couldn't add the filter '%s'", title);
	}
	this->__v_warning_lister->f_filter(title);
	return true;
}

/*
 * C_FILTER_LISTER PROTECTED METHODS
 */

/*
 * C_FILTER_LISTER PRIVATE METHODS
 */

void	c_filter_lister::__f_delete_filters(void)
{
	std::list<c_filter*>::iterator	it;
	std::list<c_filter*>::iterator	end;

	it = this->__v_filter_list.begin();
	end = this->__v_filter_list.end();
	while (it != end)
	{
		this->takeItem(this->row((*it)->f_widget_item()));
		delete *it;
		++it;
	}
	this->__v_filter_list.clear();
}

bool	c_filter_lister::__f_filter_already_exists(const char* title)
{
	std::list<c_filter*>::iterator	it;
	std::list<c_filter*>::iterator	end;

	it = this->__v_filter_list.begin();
	end = this->__v_filter_list.end();
	while (it != end)
	{
		if (strcmp((*it)->f_label()->text().toLocal8Bit().data(), title) == 0)
			return true;
		++it;
	}
	return false;
}
