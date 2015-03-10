/**
 * This section will contain the profiler level and the exec path + options
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

#include <QHBoxLayout>
#include <c_profilers_infos.h>
#include <d_design.h>
#include <c_exec_infos.h>
#include <c_output_infos.h>
#include <c_launching_options.h>
#include <tools.h>
#include <c_profiler.h>
#include <launcher.h>
#include <errors.h>
#include <c_main_content.h>
#include <c_tab_displayer.h>

using namespace	pH;

c_launching_options::c_launching_options(QWidget* father): QSplitter(Qt::Horizontal, father),
							   __v_profilers_infos(NULL),
							   __v_exec_infos(NULL),
							   __v_output_infos(NULL),
							   __v_layout(NULL)
{
}

c_launching_options::~c_launching_options(void)
{
	delete this->__v_layout;
	delete this->__v_profilers_infos;
	delete this->__v_exec_infos;
	delete this->__v_output_infos;
}

/*
 * C_LAUNCHING_OPTIONS PUBLIC METHODS
 */

bool	c_launching_options::f_init(std::list<c_tab*>* tabs)
{
	if (this->__f_init_layout() == false ||
	    this->__f_init_profilers_infos() == false ||
	    this->__f_init_output_infos(tabs) == false ||
	    this->__f_init_exec_infos() == false)
		return false;
	this->setMaximumHeight(D_LAUNCHING_OPTIONS_HEIGHT);
	this->setLayout(this->__v_layout);
	return true;
}

/*
 * C_LAUNCHING_OPTIONS PROTECTED METHODS
 */

/*
 * C_LAUNCHING_OPTIONS PRIVATE METHODS
 */

bool	c_launching_options::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QHBoxLayout;
	return this->__v_layout;
}

bool	c_launching_options::__f_init_profilers_infos(void)
{
	this->__v_profilers_infos = new(std::nothrow) c_profilers_infos(this);
	if (this->__v_profilers_infos == NULL ||
	    this->__v_profilers_infos->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->__v_profilers_infos);
	return true;
}

void	c_launching_options::__f_launch(void)
{
	std::string	exec_infos;

	this->__v_exec_infos->f_get_exec_infos(&exec_infos);
	M_LAUNCHER(l, exec_infos.c_str());
	if (this->__f_browse_profilers(&l) == false)
		M_ERROR_BOOL(false, "Invalid profiler options", 0);
	else if (launcher_launch(&l) == false)
		M_ERROR_BOOL(false, "Couldn't execute the given program", 0);
	else
		((c_main_content*)this->parent())->v_tab_displayer->f_load_tabs(this->__v_output_infos->f_options());
	M_LAUNCHER_DESTROY(l);
}

bool	c_launching_options::__f_browse_profilers(launcher* l)
{
	std::list<c_profiler*>::iterator	it;
	std::list<c_profiler*>::iterator	end;

	it = this->__v_profilers_infos->f_profilers()->begin();
	end = this->__v_profilers_infos->f_profilers()->end();
	while (it != end)
	{
		if ((*it)->f_toggled() == true)
			return this->__f_add_profiler_options(l, *it);
		++it;
	}
	return true;
}

bool	c_launching_options::__f_add_profiler_options(launcher* l, c_profiler* profiler)
{
	std::vector<ph_tools::c_profiler_option*>*		options;
	std::vector<ph_tools::c_profiler_option*>::iterator	it;
	std::vector<ph_tools::c_profiler_option*>::iterator	end;

	options = profiler->f_profiler()->f_options();
	it = options->begin();
	end = options->end();
	while (it != end)
	{
		if ((*it)->f_activated() == true)
			if (launcher_add_task(l, (*it)->f_option(), NULL) == false)
				return M_ERROR_BOOL(false, "Couldn't add the option %s", (*it)->f_string());
		++it;
	}
	return true;
}

bool	c_launching_options::__f_init_exec_infos(void)
{
	this->__v_exec_infos = new(std::nothrow) c_exec_infos(this);
	if (this->__v_exec_infos == NULL ||
	    this->__v_exec_infos->f_init() == false)
		return false;
	this->__v_layout->addWidget(this->__v_exec_infos);
	return true;
}

bool	c_launching_options::__f_init_output_infos(std::list<c_tab*>* tabs)
{
	this->__v_output_infos = new(std::nothrow) c_output_infos(this);
	if (this->__v_output_infos == NULL ||
	    this->__v_output_infos->f_init(tabs) == false)
		return false;
	this->__v_layout->addWidget(this->__v_output_infos);
	return true;
}
