/**
 * This class will be used to know whether or not a tab has to be generated.
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

#include <c_output_option.h>
#include <c_tab.h>

using namespace	pH;

c_output_option::c_output_option(QWidget* father, const char* value): QCheckBox(value, father),
								      __v_value(value),
								      __v_activated(NULL)
{
	QObject::connect(this, SIGNAL(clicked()), this, SLOT(__f_activation()));
}

c_output_option::~c_output_option(void)
{
}

/*
 * C_OUTPUT_OPTION PUBLIC METHODS
 */

bool	c_output_option::f_init(std::list<c_tab*>* tabs)
{
	std::list<c_tab*>::iterator	it;
	std::list<c_tab*>::iterator	end;

	it = tabs->begin();
	end = tabs->end();
	while (it != end)
	{
		if (strcmp((*it)->f_value(), this->__v_value) == 0)
		{
			this->__v_activated = (*it)->f_activated();
			return true;
		}
		++it;
	}
	return false;
}

/*
 * C_OUTPUT_OPTION PROTECTED METHODS
 */

/*
 * C_OUTPUT_OPTION PRIVATE METHODS
 */

void	c_output_option::__f_activation(void)
{
	*this->__v_activated = !*this->__v_activated;
}
