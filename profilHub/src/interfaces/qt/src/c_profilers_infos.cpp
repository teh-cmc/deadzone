/**
 * This section will contain the profiler information
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

#include <c_profilers_infos.h>
#include <QHBoxLayout>
#include <errors.h>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <c_profiler.h>
#include <QListWidget>
#include <QCheckBox>
#include <d_design.h>
#include <QButtonGroup>
#include <tools.h>

using namespace	pH;

c_profilers_infos::c_profilers_infos(QWidget* father): QGroupBox("Profilers", father),
						       __v_layout(NULL),
						       __v_profilers(NULL),
						       __v_profilers_options(NULL),
						       __v_selected_profiler(NULL)
{
}

c_profilers_infos::~c_profilers_infos(void)
{
	delete this->__v_layout;
	this->__f_destroy_choices();
	this->__f_destroy_old_options();
	delete this->__v_profilers;
	delete this->__v_profilers_options;
}

/*
 * C_PROFILERS_INFOS PUBLIC METHODS
 */

bool	c_profilers_infos::f_init(void)
{
	this->__v_button_group = new(std::nothrow) QButtonGroup;
	if (this->__v_button_group == NULL ||
	    this->__f_init_layout() == false ||
	    this->__f_init_scrollable_areas() == false ||
	    this->__f_init_choices() == false)
		return false;
	this->setMaximumHeight(D_LAUNCHING_OPTIONS_HEIGHT);
	this->setLayout(this->__v_layout);
	return true;
}

std::list<c_profiler*>*	c_profilers_infos::f_profilers(void)
{
	return &this->__v_choices;
}

/*
 * C_PROFILERS_INFOS PROTECTED METHODS
 */

/*
 * C_PROFILERS_INFOS PRIVATE METHODS
 */

bool	c_profilers_infos::__f_init_layout(void)
{
	this->__v_layout = new(std::nothrow) QHBoxLayout;
	return this->__v_layout;
}

bool	c_profilers_infos::__f_init_choices(void)
{
	uint32_t				counter;
	uint32_t				total;
	std::vector<ph_tools::c_profiler*>	choices;

	if (ph_tools::c_profilers::sf_get_choices(&choices) == false)
		return false;
	counter = 0;
	total = choices.size();
	while (counter < total)
	{
		if (this->__f_add_choice(choices[counter]) == false)
			return this->__f_destroy_vector_elements(&choices, counter);
		++counter;
	}
	choices.clear();
	return true;
}

bool	c_profilers_infos::__f_destroy_vector_elements(std::vector<ph_tools::c_profiler*>* vector, uint32_t counter)
{
	while (counter < vector->size())
	{
		delete (*vector)[counter];
		++counter;
	}
	vector->clear();
	return false;
}

bool	c_profilers_infos::__f_add_choice(ph_tools::c_profiler* profiler)
{
	c_profiler*		radio_button;
	QListWidgetItem*	item;

	radio_button = NULL;
	item = NULL;
	try
	{
		item = new QListWidgetItem(this->__v_profilers);
		radio_button = new c_profiler(profiler, item, this);
		QObject::connect(radio_button, SIGNAL(activated()), this, SLOT(__f_display_profiler_options()));
		this->__v_choices.push_back(radio_button);
		this->__v_profilers->addItem(item);
		this->__v_profilers->setItemWidget(item, radio_button);
		this->__v_button_group->addButton(radio_button);
	}
	catch (...)
	{
		delete item;
		delete radio_button;
		return M_ERROR_BOOL(false, "Couldn't create a profiler choice", 0);
	}
	return true;
}

void	c_profilers_infos::__f_destroy_choices(void)
{
	std::list<c_profiler*>::iterator	it;
	std::list<c_profiler*>::iterator	end;

	it = this->__v_choices.begin();
	end = this->__v_choices.end();
	while (it != end)
	{
		this->__v_profilers->takeItem(this->__v_profilers->row((*it)->f_widget_item()));
		delete *it;
		++it;
	}
	this->__v_choices.clear();
}

bool	c_profilers_infos::__f_init_scrollable_areas(void)
{
	QPalette	pal = this->palette();

	pal.setColor(QPalette::Highlight, QColor(qRgb(255, 255, 255)));
	this->__v_profilers = new(std::nothrow) QListWidget;
	this->__v_profilers_options = new(std::nothrow) QListWidget;
	if (this->__v_profilers == NULL || this->__v_profilers_options == NULL)
		return false;
	this->__v_profilers->setSpacing(5);
	this->__v_profilers_options->setSpacing(5);
	this->__v_profilers->setPalette(pal);
	this->__v_profilers_options->setPalette(pal);
	this->__v_layout->addWidget(this->__v_profilers);
	this->__v_layout->addWidget(this->__v_profilers_options);
	return true;
}

void	c_profilers_infos::__f_display_profiler_options(void)
{
	std::vector<ph_tools::c_profiler_option*>*		list;
	std::vector<ph_tools::c_profiler_option*>::iterator	it;
	std::vector<ph_tools::c_profiler_option*>::iterator	end;

	this->__f_destroy_old_options();
	this->__v_selected_profiler = (c_profiler*)QObject::sender();
	list = ((c_profiler*)QObject::sender())->f_profiler()->f_options();
	it = list->begin();
	end = list->end();
	while (it != end)
	{
		this->__f_add_option(*it);
		++it;
	}
}

void	c_profilers_infos::__f_add_option(ph_tools::c_profiler_option* profiler_option)
{
	QListWidgetItem*	item;
	QCheckBox*		checkbox;

	item = NULL;
	try
	{
		item = new QListWidgetItem(this->__v_profilers_options);
		checkbox = new QCheckBox(profiler_option->f_string(), this);
		QObject::connect(checkbox, SIGNAL(clicked()), this, SLOT(__f_select_option()));
		if (profiler_option->f_activated() == true)
			checkbox->setCheckState(Qt::Checked);
		else
			checkbox->setCheckState(Qt::Unchecked);
		this->__v_profilers_options->addItem(item);
		this->__v_profilers_options->setItemWidget(item, checkbox);
		this->__v_options.push_back(item);
	}
	catch (...)
	{
		delete item;
		delete checkbox;
	}
}

void	c_profilers_infos::__f_destroy_old_options(void)
{
	std::list<QListWidgetItem*>::iterator	it;
	std::list<QListWidgetItem*>::iterator	end;

	it = this->__v_options.begin();
	end = this->__v_options.end();
	while (it != end)
	{
		delete this->__v_profilers_options->itemWidget(*it);
		this->__v_profilers_options->takeItem(this->__v_profilers_options->row(*it));
		delete *it;
		++it;
	}
	this->__v_options.clear();
}

void	c_profilers_infos::__f_select_option(void)
{
	uint32_t					counter;
	uint32_t					total;
	const char*					string;
	std::vector<ph_tools::c_profiler_option*>*	vector;

	if (this->__v_selected_profiler != NULL)
	{
		vector = this->__v_selected_profiler->f_profiler()->f_options();
		string = ((QCheckBox*)QObject::sender())->text().toLocal8Bit().data();
		counter = 0;
		total = vector->size();
		while (counter < total)
		{
			if (strcmp(string, (*vector)[counter]->f_string()) == 0)
				break;
			++counter;
		}
		if (counter < total)
			(*vector)[counter]->f_activated(!(*vector)[counter]->f_activated());
	}
}
