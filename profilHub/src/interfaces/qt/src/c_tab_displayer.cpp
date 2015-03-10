/**
 * This is the class used to render the different tabs
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

#include <QGridLayout>
#include <QHBoxLayout>
#include <c_tab_displayer.h>
#include <c_tab_main.h>
#include <errors.h>
#include <c_tab_calltree.h>
#include <c_tab_content.h>
#include <d_design.h>
#include <c_tab_label.h>
#include <c_tab_callgraph.h>
#include <c_tab_graph.h>
#include <c_output_option.h>
#include <stdint.h>

using namespace	pH;

c_tab_displayer::c_tab_displayer(QWidget* father): QWidget(father),
						   __v_layout(NULL),
						   __v_tab_layout(NULL),
						   __v_current_tab(NULL)
{
}

c_tab_displayer::~c_tab_displayer(void)
{
	delete this->__v_tab_layout;
	delete this->__v_layout;
	this->__f_delete_tabs();
}

/*
 * C_TAB_DISPLAYER PUBLIC METHODS
 */

bool	c_tab_displayer::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_create_single_tab(new(std::nothrow) c_tab_main(this)) == false ||
	    this->__f_create_single_tab(new(std::nothrow) c_tab_calltree(this)) == false ||
	    this->__f_create_single_tab(new(std::nothrow) c_tab_callgraph(this)) == false ||
	    this->__f_create_single_tab(new(std::nothrow) c_tab_graph(this)) == false)
		return M_ERROR_BOOL(false, "Couldn't create the tab displayer\n", 0);
	this->setLayout(this->__v_layout);
	return true;
}

void	c_tab_displayer::f_select_tab(c_tab* tab)
{
	if (tab != this->__v_current_tab)
	{
		if (this->__v_current_tab != NULL)
		{
			this->__v_current_tab->f_tab_header()->f_label()->hide();
			this->__v_layout->removeWidget((QWidget*)this->__v_current_tab->f_tab_content());
			this->__v_current_tab->f_tab_content()->hide();
		}
		this->__f_set_content(tab);
	}
}

std::list<c_tab*>*	c_tab_displayer::f_tabs(void)
{
	return &this->__v_tabs;
}

void	c_tab_displayer::f_load_tabs(std::vector<c_output_option*>* vector)
{
	uint32_t	counter;
	uint32_t	total;

	counter = 0;
	total = vector->size();
	this->f_change_tab_visibility("main", false);
	while (counter < total)
	{
		this->f_change_tab_visibility((*vector)[counter]->f_value(), (*vector)[counter]->f_activated());
		++counter;
	}
}

void	c_tab_displayer::f_close_tab(c_tab* tab)
{
	std::list<c_tab*>::iterator	it;
	std::list<c_tab*>::iterator	end;
	c_tab*				tmp;
	bool				v_continue;

	it = this->__v_tabs.begin();
	end = this->__v_tabs.end();
	v_continue = true;
	tmp = NULL;
	while (it != end)
	{
		if (tab == *it)
		{
			(*it)->hide();
			(*it)->f_here(false);
			this->__v_layout->removeWidget((QWidget*)(*it)->f_tab_header());
			this->__v_layout->removeWidget((QWidget*)(*it)->f_tab_content());
			v_continue = false;
		}
		else if ((*it)->f_here() == true)
			tmp = *it;
		if (v_continue == false && tmp != NULL)
			return this->__f_set_content(tmp);
		++it;
	}
}

void	c_tab_displayer::f_change_tab_visibility(const char* id, bool value)
{
	std::list<c_tab*>::iterator	it;
	std::list<c_tab*>::iterator	end;

	it = this->__v_tabs.begin();
	end = this->__v_tabs.end();
	while (it != end)
	{
		if (strcmp(id, (*it)->f_value()) == 0)
		{
			if (value == true)
			{
				if ((*it)->f_here() == false)
				{
					this->__f_add_tab(*it);
					this->f_select_tab(*it);
					(*it)->f_tab_content()->f_load();
				}
				(*it)->show();
			}
			else
				(*it)->hide();
			(*it)->f_here(value);
		}
		++it;
	}
}

/*
 * C_TAB_DISPLAYER PROTECTED METHODS
 */

/*
 * C_TAB_DISPLAYER PRIVATE METHODS
 */

bool	c_tab_displayer::__f_create_single_tab(c_tab* tab)
{
	if (tab == NULL)
		return false;
	try
	{
		if (tab->f_init() == false)
			throw -1;
		this->__v_tabs.push_back(tab);
		if (this->__v_tabs.size() == 1)
		{
			this->__f_add_tab(tab);
			this->__f_set_content(tab);
		}
		else
		{
			tab->f_here(false);
			tab->hide();
		}
	}
	catch (...)
	{
		delete tab;
		return false;
	}
	return true;
}

bool	c_tab_displayer::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QGridLayout;
	this->__v_tab_layout = new(std::nothrow) QHBoxLayout;
	if (this->__v_layout == NULL || this->__v_tab_layout == NULL)
		return false;
	this->__v_layout->setContentsMargins(D_TAB_DISPLAYER_MARGIN, D_TAB_DISPLAYER_MARGIN,
					     D_TAB_DISPLAYER_MARGIN, D_TAB_DISPLAYER_MARGIN);
	this->__v_layout->setSpacing(5);
	this->__v_layout->addLayout(this->__v_tab_layout, 0, 0);
	return true;
}

void	c_tab_displayer::__f_add_tab(c_tab* tab)
{
	tab->f_here(true);
	tab->f_tab_header()->show();
	this->__v_tab_layout->addWidget(tab->f_tab_header());
}

void	c_tab_displayer::__f_set_content(c_tab* tab)
{
	this->__v_current_tab = tab;
	tab->show();
	tab->f_tab_header()->f_label()->show();
	this->__v_layout->addWidget(tab->f_tab_content(), 1, 0);
}

void	c_tab_displayer::__f_delete_tabs(void)
{
	std::list<c_tab*>::iterator	it;
	std::list<c_tab*>::iterator	end;

	it = this->__v_tabs.begin();
	end = this->__v_tabs.end();
	while (it != end)
	{
		delete *it;
		++it;
	}
	this->__v_tabs.clear();
}
