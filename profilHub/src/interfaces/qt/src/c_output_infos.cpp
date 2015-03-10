/**
 * This section is used to choose which tab has to be generated.
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

#include <c_output_infos.h>
#include <c_output_option.h>
#include <QVBoxLayout>
#include <errors.h>

using namespace	pH;

c_output_infos::c_output_infos(QWidget* father): QGroupBox("Output", father),
						 __v_layout(NULL)
{
}

c_output_infos::~c_output_infos(void)
{
	delete this->__v_layout;
	this->__f_destroy_output_options();
}

/*
 * C_OUTPUT_INFOS PUBLIC METHODS
 */

bool	c_output_infos::f_init(std::list<c_tab*>* tabs)
{
	this->__v_layout = new(std::nothrow) QVBoxLayout;
	if (this->__v_layout == NULL ||
	    this->__f_create_single_output_option(tabs, "calltree") == false ||
	    this->__f_create_single_output_option(tabs, "callgraph") == false ||
	    this->__f_create_single_output_option(tabs, "graph") == false)
		return false;
	this->setLayout(this->__v_layout);
	return true;
}

/*
 * C_OUTPUT_INFOS PROTECTED METHODS
 */

/*
 * C_OUTPUT_INFOS PRIVATE METHODS
 */

bool	c_output_infos::__f_create_single_output_option(std::list<c_tab*>* list, const char* value)
{
	c_output_option*	option;

	option = NULL;
	try
	{
		option = new c_output_option(this, value);
		if (option->f_init(list) == false)
			throw -1;
		option->setCheckState(Qt::Checked);
		this->__v_output_options.push_back(option);
		this->__v_layout->addWidget(option);
	}
	catch (...)
	{
		delete option;
		return M_ERROR_BOOL(false, "Couldn't created the '%s' option, this tab doesn't exists", value);
	}
	return true;
}

void	c_output_infos::__f_destroy_output_options(void)
{
	std::vector<c_output_option*>::iterator	it;
	std::vector<c_output_option*>::iterator	end;

	it = this->__v_output_options.begin();
	end = this->__v_output_options.end();
	while (it != end)
	{
		delete *it;
		++it;
	}
	this->__v_output_options.clear();
}
