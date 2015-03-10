/**
 * This is the filter class widget
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

#include <c_filter.h>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <d_paths.h>
#include <d_design.h>
#include <c_img.h>
#include <QFont>
#include <QLabel>

using namespace	pH;

c_filter::c_filter(QWidget* father, QListWidgetItem* widget_item, const char* title): QFrame(father),
										      __v_title(title),
										      __v_image(NULL),
										      __v_label(NULL),
										      __v_widget_item(widget_item),
										      __v_layout(NULL)
{
}

c_filter::~c_filter(void)
{
	delete this->__v_layout;
	delete this->__v_label;
	delete this->__v_image;
	delete this->__v_widget_item;
}

/*
 * C_FILTER PUBLIC METHODS
 */

bool	c_filter::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_title() == false ||
	    this->__f_init_image() == false)
		return false;
	this->setFrameShape(QFrame::WinPanel);
	this->setLayout(this->__v_layout);
	return true;
}

QListWidgetItem*	c_filter::f_widget_item(void)
{
	return this->__v_widget_item;
}

QLabel*	c_filter::f_label(void)
{
	return this->__v_label;
}

/*
 * C_FILTER PROTECTED METHODS
 */

/*
 * C_FILTER PRIVATE METHODS
 */

bool	c_filter::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QHBoxLayout;
	if (this->__v_layout == NULL)
		return false;
	this->__v_layout->setSpacing(1);
	return true;
}

bool	c_filter::__f_init_title(void)
{
	this->__v_label = new(std::nothrow) QLabel(this->__v_title, this);
	if (this->__v_label == NULL)
		return false;
	this->__v_label->setFont(QFont("Times", 10, QFont::Bold));
	this->__v_layout->addWidget(this->__v_label, Qt::AlignLeft);
	return true;
}

bool	c_filter::__f_init_image(void)
{
	this->__v_image = new(std::nothrow) c_img(this);
	if (this->__v_image == NULL ||
	    this->__v_image->f_init(D_QUIT_BUTTON_PATH) == false)
		return false;
	QObject::connect(this->__v_image, SIGNAL(clicked()), this->parent(), SLOT(f_remove_filter()));
	this->__v_layout->addWidget(this->__v_image);
	return true;
}
