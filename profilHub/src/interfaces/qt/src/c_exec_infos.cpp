/**
 * This section will contain the executable informations
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
#include <QPushButton>
#include <QLineEdit>
#include <d_design.h>
#include <d_constants.h>
#include <errors.h>
#include <c_exec_infos.h>
#include "../include/c_exec_infos.h"
#include <QFileDialog>

using namespace	pH;

c_exec_infos::c_exec_infos(QWidget* father): QGroupBox("Executable", father),
					     __v_launch_button(NULL),
					     __v_browse_button(NULL),
					     __v_exec_path(NULL),
					     __v_exec_args(NULL),
					     __v_exec_layout(NULL),
					     __v_layout(NULL),
					     __v_file_dialog(NULL)
{
}

c_exec_infos::~c_exec_infos(void)
{
	delete this->__v_exec_layout;
	delete this->__v_layout;
	delete this->__v_launch_button;
	delete this->__v_file_dialog;
	delete this->__v_browse_button;
	delete this->__v_exec_path;
	delete this->__v_exec_args;
}

/*
 * C_EXEC_INFOS PUBLIC METHODS
 */

bool	c_exec_infos::f_init(void)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_exec_path() == false ||
	    this->__f_init_args() == false ||
	    this->__f_init_file_dialog() == false ||
	    this->__f_init_launch_button() == false)
		return false;
	this->setMaximumHeight(D_LAUNCHING_OPTIONS_HEIGHT);
	this->setLayout(this->__v_layout);
	return true;
}

void	c_exec_infos::f_get_exec_infos(std::string* exec_infos)
{
	exec_infos->clear();
	exec_infos->append(this->__v_exec_path->text().toLocal8Bit().data());
	exec_infos->append(" ");
	exec_infos->append(this->__v_exec_args->text().toLocal8Bit().data());
}

/*
 * C_EXEC_INFOS PROTECTED METHODS
 */

/*
 * C_EXEC_INFOS PRIVATE METHODS
 */

bool	c_exec_infos::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QGridLayout;
	this->__v_exec_layout = new(std::nothrow) QHBoxLayout;
	if (this->__v_layout == NULL || this->__v_exec_layout == NULL)
		return false;
	this->__v_layout->addLayout(this->__v_exec_layout, 0, 0);
	return this->__v_layout;
}

bool	c_exec_infos::__f_init_exec_path(void)
{
	this->__v_exec_path = new(std::nothrow) QLineEdit(this);
	this->__v_browse_button = new(std::nothrow) QPushButton(tr("Browse"), this);
	if (this->__v_exec_path == NULL ||
	    this->__v_browse_button == NULL)
		return false;
	QObject::connect(this->__v_browse_button, SIGNAL(clicked()), this, SLOT(__f_browse()));
	this->__v_exec_path->setMaxLength(D_TEXTBOX_MAX_LENGTH);
	this->__v_exec_path->setPlaceholderText("Executable path");
	this->__v_exec_layout->addWidget(this->__v_exec_path);
	this->__v_exec_layout->addWidget(this->__v_browse_button);
	return true;
}

bool	c_exec_infos::__f_init_args(void)
{
	this->__v_exec_args = new(std::nothrow) QLineEdit(this);
	if (this->__v_exec_args == NULL)
		return false;
	this->__v_exec_args->setPlaceholderText("Executable args");
	this->__v_layout->addWidget(this->__v_exec_args, 1, 0);
	return true;
}

bool	c_exec_infos::__f_init_launch_button(void)
{
	this->__v_launch_button = new(std::nothrow) QPushButton(tr("Launch"), this);
	if (this->__v_launch_button == NULL)
		return false;
	QObject::connect(this->__v_launch_button, SIGNAL(clicked()), this->parent(), SLOT(__f_launch()));
	this->__v_layout->addWidget(this->__v_launch_button, 2, 0);
	return true;
}

bool	c_exec_infos::__f_init_file_dialog(void)
{
	this->__v_file_dialog = new(std::nothrow) QFileDialog(this);
	if (this->__v_file_dialog == NULL)
		return false;
	QObject::connect(this->__v_file_dialog, SIGNAL(accepted()), this, SLOT(__f_selected_file()));
	this->__v_file_dialog->setDirectory("./");
	this->__v_file_dialog->hide();
	return true;
}

void	c_exec_infos::__f_selected_file(void)
{
	this->__v_exec_path->clear();
	this->__v_exec_path->insert(this->__v_file_dialog->selectedFiles().at(0));
}

void	c_exec_infos::__f_browse(void)
{
	this->__v_file_dialog->show();
}
