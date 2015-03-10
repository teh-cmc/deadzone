/**
 * Used to describe the content of a tab
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

#include <c_tab_header.h>
#include <c_tab_label.h>
#include <c_img.h>
#include <QHBoxLayout>
#include <errors.h>
#include <d_design.h>
#include <c_tab_displayer.h>

using namespace	pH;

c_tab_header::c_tab_header(QWidget* father, const char* label_title, const char* image_path, e_tab_header_state state): QFrame(father),
															__v_label_title(label_title),
															__v_image_path(image_path),
															__v_label(NULL),
															__v_image(NULL),
															__v_state(state),
															__v_layout(NULL),
															__v_tab(NULL)
{
}

c_tab_header::~c_tab_header(void)
{
	delete this->__v_label;
	delete this->__v_image;
	delete this->__v_layout;
}

/*
 * C_TAB_HEADER PUBLIC METHODS
 */

bool	c_tab_header::f_init(c_tab* tab)
{
	this->__v_tab = tab;
	if (this->__f_init_label() == false ||
	    (this->__v_state == QUITABLE && this->__f_init_image() == false) ||
	    this->__f_init_layout() == false)
		return false;
	this->setFrameShape(QFrame::WinPanel);
	this->setFrameShadow(Raised);
	return true;
}

c_tab_label*	c_tab_header::f_label(void)
{
	return this->__v_label;
}

void	c_tab_header::f_close_tab(void)
{
	((c_tab_displayer*)this->parent())->f_close_tab(this->__v_tab);
}

/*
 * C_TAB_HEADER PROTECTED METHODS
 */

/*
 * C_TAB_HEADER PRIVATE METHODS
 */

bool	c_tab_header::__f_init_label(void)
{
	this->__v_label = new(std::nothrow) c_tab_label(this->__v_label_title, this);
	if (this->__v_label == NULL)
		return M_ERROR_BOOL(false, "Couldn't create the tab header label\n", 0);
	this->__v_label->setFont(QFont("Times", 10, QFont::Bold));
	this->__v_label->setFrameShape(QFrame::WinPanel);
	this->__v_label->v_tab = this->__v_tab;
	return true;
}

bool	c_tab_header::__f_init_image(void)
{
	this->__v_image = new(std::nothrow) c_img(this);
	if (this->__v_image == NULL ||
	    this->__v_image->f_init(this->__v_image_path) == false)
		return false;
	QObject::connect(this->__v_image, SIGNAL(clicked()), this, SLOT(f_close_tab()));
	return true;
}

bool	c_tab_header::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QHBoxLayout;
	if (this->__v_layout == NULL)
		return M_ERROR_BOOL(false, "Couldn't create the tab header layout\n", 0);
	this->__v_layout->setSizeConstraint(QLayout::SetNoConstraint);
	this->__v_layout->addWidget(this->__v_label, Qt::AlignRight);
	if (this->__v_image != NULL)
		this->__v_layout->addWidget(this->__v_image);
	this->__v_layout->setSpacing(0);
	this->__v_layout->setContentsMargins(D_TAB_HEADER_MARGIN, D_TAB_HEADER_MARGIN,
					     D_TAB_HEADER_MARGIN, D_TAB_HEADER_MARGIN);
	this->setLayout(this->__v_layout);
	return true;
}
