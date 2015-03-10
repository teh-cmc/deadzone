/**
 * This class inherits from QRadioButton, and contains the profiler options
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

#include <c_profiler.h>
#include <QListWidgetItem>
#include <tools.h>

using namespace	pH;

c_profiler::c_profiler(ph_tools::c_profiler* profiler, QListWidgetItem* item, QWidget* father): QRadioButton(profiler->f_value(), father),
												__v_profiler(profiler),
												__v_item(item),
												__v_toggled(false)
{
	QObject::connect(this, SIGNAL(toggled(bool)), this, SLOT(__f_check_activation()));
}

c_profiler::~c_profiler(void)
{
	delete this->__v_item;
	delete this->__v_profiler;
}

/*
 * C_PROFILER PUBLIC METHODS
 */

QListWidgetItem*	c_profiler::f_widget_item(void)
{
	return this->__v_item;
}

ph_tools::c_profiler*	c_profiler::f_profiler(void)
{
	return this->__v_profiler;
}

bool	c_profiler::f_toggled(void)
{
	return this->__v_toggled;
}

/*
 * C_PROFILER PROTECTED METHODS
 */

/*
 * C_PROFILER PRIVATE METHODS
 */

void	c_profiler::__f_check_activation(void)
{
	if (this->__v_toggled == false)
		emit activated();
	this->__v_toggled = this->isChecked();
}
