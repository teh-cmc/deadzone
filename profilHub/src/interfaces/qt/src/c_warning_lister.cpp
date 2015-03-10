/**
 * This is the section displaying the errors, by file/line
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

#include <c_warning_lister.h>
#include <d_design.h>
#include <c_warning.h>
#include <errors.h>

using namespace	pH;

c_warning_lister::c_warning_lister(QWidget* father): QListWidget(father)
{
}

c_warning_lister::~c_warning_lister(void)
{
	this->__f_delete_warnings();
}

/*
 * C_WARNING_LISTER PUBLIC METHODS
 */

bool	c_warning_lister::f_init(void)
{
	QPalette	pal = this->palette();

	pal.setColor(QPalette::Highlight, QColor(qRgb(255, 163, 71)));
	this->setPalette(pal);
	return true;
}

void	c_warning_lister::f_search(const char* search)
{
	std::list<c_warning*>::iterator	it;
	std::list<c_warning*>::iterator	end;

	it = this->__v_warnings.begin();
	end = this->__v_warnings.end();
	while (it != end)
	{
		if ((*it)->f_here() == true)
		{
			if ((*it)->f_search(search) == false)
				this->setRowHidden(this->row((*it)->f_widget_item()), true);
			else
				this->setRowHidden(this->row((*it)->f_widget_item()), false);
		}
		++it;
	}
}

void	c_warning_lister::f_filter(const char* filter)
{
	std::list<c_warning*>::iterator	it;
	std::list<c_warning*>::iterator	end;

	it = this->__v_warnings.begin();
	end = this->__v_warnings.end();
	while (it != end)
	{
		if ((*it)->f_here() == true)
			if ((*it)->f_filter(filter) == true)
				this->setRowHidden(this->row((*it)->f_widget_item()), true);
		++it;
	}
}

void	c_warning_lister::f_unfilter(const char* filter)
{
	std::list<c_warning*>::iterator	it;
	std::list<c_warning*>::iterator	end;

	it = this->__v_warnings.begin();
	end = this->__v_warnings.end();
	while (it != end)
	{
		if ((*it)->f_here() == false)
			if ((*it)->f_unfilter(filter) == true)
				this->setRowHidden(this->row((*it)->f_widget_item()), false);
		++it;
	}
}

void	c_warning_lister::f_remove_warning(void)
{
	std::list<c_warning*>::iterator	it;
	std::list<c_warning*>::iterator	end;
	c_warning*			warning;

	warning = (c_warning*)QObject::sender()->parent();
	it = this->__v_warnings.begin();
	end = this->__v_warnings.end();
	while (it != end)
	{
		if (*it == warning)
		{
			this->__v_warnings.erase(it);
			this->takeItem(this->row(warning->f_widget_item()));
			delete warning;
			break;
		}
		++it;
	}
}

bool	c_warning_lister::f_add_warning(const char* title)
{
	c_warning*		warning;
	QListWidgetItem*	list_item;

	warning = NULL;
	list_item = NULL;
	try
	{
		list_item = new QListWidgetItem(this);
		warning = new c_warning(this, list_item, title);
		if (warning->f_init() == false)
			throw -1;
		this->__v_warnings.push_back(warning);
		list_item->setSizeHint(QSize(0, warning->height() + D_ICON_SIZE));
		this->addItem(list_item);
		this->setItemWidget(list_item, warning);
	}
	catch (...)
	{
		delete warning;
		delete list_item;
		return M_ERROR_BOOL(false, "Couldn't add the warning '%s'", title);
	}
	return true;
}

/*
 * C_WARNING_LISTER PROTECTED METHODS
 */

/*
 * C_WARNING_LISTER PRIVATE METHODS
 */

void	c_warning_lister::__f_delete_warnings(void)
{
	std::list<c_warning*>::iterator	it;
	std::list<c_warning*>::iterator	end;

	it = this->__v_warnings.begin();
	end = this->__v_warnings.end();
	while (it != end)
	{
		this->takeItem(this->row((*it)->f_widget_item()));
		delete *it;
		++it;
	}
}
