/**
 * This is the main content of profilHub, here the c_tab_displayer
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

#include <c_tab_displayer.h>
#include <QGridLayout>
#include <c_main_content.h>
#include <c_launching_options.h>

using namespace	pH;

c_main_content::c_main_content(QWidget* father): QSplitter(Qt::Vertical, father),
						 v_tab_displayer(NULL),
						 __v_launching_options(NULL),
						 __v_layout(NULL)
{
}

c_main_content::~c_main_content(void)
{
	delete this->__v_layout;
	delete this->v_tab_displayer;
}

/*
 * C_MAIN_CONTENT PUBLIC METHODS
 */

bool	c_main_content::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_tab_displayer() == false ||
	    this->__f_init_launching_options() == false)
		return false;
	this->setLayout(this->__v_layout);
	this->setFrameShape(QFrame::WinPanel);
	return true;
}

/*
 * C_MAIN_CONTENT PROTECTED METHODS
 */

/*
 * C_MAIN_CONTENT PRIVATE METHODS
 */

bool	c_main_content::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QGridLayout;
	return this->__v_layout;
}

bool	c_main_content::__f_init_tab_displayer(void)
{
	this->v_tab_displayer = new(std::nothrow) c_tab_displayer(this);
	if (this->v_tab_displayer == NULL ||
	    this->v_tab_displayer->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->v_tab_displayer, 0, 0);
	return true;
}

bool	c_main_content::__f_init_launching_options(void)
{
	this->__v_launching_options = new(std::nothrow) c_launching_options(this);
	if (this->__v_launching_options == NULL ||
	    this->__v_launching_options->f_init(this->v_tab_displayer->f_tabs()) == false)
		return false;
	this->__v_layout->addWidget(this->__v_launching_options, 1, 0);
	return true;
}
