/**
 * BlaBla Description
 * Copyright (C) 2013  Jean-Baptiste Noblot <jb.noblot@gmail.com>
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


#include <c_options_popup.h>
#include "../include/c_options_popup.h"
#include <new>
#include <QSettings>
#include <QGridLayout>
#include <QDialogButtonBox>

using namespace pH;

c_options_popup::c_options_popup(QWidget* father) : QDialog(father)
{
	this->teb.gT = 0;
}

c_options_popup::~c_options_popup(void)
{
	delete (this->teb.gT);
}

bool
c_options_popup::f_init(void)
{
	QGridLayout*		grid = new (std::nothrow) QGridLayout(this);
	QVBoxLayout*		vbox = new (std::nothrow) QVBoxLayout();
	QDialogButtonBox*	buttonBox = new (std::nothrow) QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

	this->labelTitle = new (std::nothrow) QLabel(this);
	this->listOption = new (std::nothrow) QListWidget(this);
	this->tab = new (std::nothrow) QTabWidget(this);
	this->panel = new (std::nothrow) QFrame(this);
	if (grid == NULL ||
	    vbox == NULL ||
	    this->listOption == NULL ||
	    buttonBox == NULL ||
	    this->labelTitle == NULL ||
	    this->tab == NULL ||
	    this->panel == NULL)
	{
		delete grid;
		delete this->listOption;
		delete vbox;
		delete buttonBox;
		delete this->labelTitle;
		delete this->tab;
		delete this->panel;
		return false;
	}

	this->listOption->setSelectionMode(QAbstractItemView::SingleSelection);
	this->listOption->addItem(tr("Environment"));
	this->listOption->setMaximumWidth(100);
	connect(this->listOption, SIGNAL(itemSelectionChanged()), this, SLOT(s_clicked_option()));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(s_accepted()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(s_rejected()));

	grid->addWidget(this->labelTitle, 0, 1);
	this->setLayout(grid);
	vbox->addWidget(this->tab);
	this->panel->setLayout(vbox);
	if (this->__f_environmentOption() == false)
			return false;
	grid->addWidget(listOption, 1, 0);
	grid->addWidget(this->panel, 1, 1);
	grid->addWidget(buttonBox, 2, 1);
	return true;

}

void
c_options_popup::s_accepted()
{
    QSettings       settings("profilHubTeam", "profilHub");

    settings.setValue("lang", this->teb.gT->selectedLang);
    this->close();
}

void
c_options_popup::s_rejected()
{
    this->close();
}


void
c_options_popup::s_clicked_option(void)
{
	int	max = this->tab->count() - 1;

	while (max >= 0)
	{
		this->tab->removeTab(max);
		--max;
	}
	for (int i = 0; i < this->listOption->count(); i++)
	{
		if ((this->listOption->item(i))->isSelected() == true)
		{
			if (i == 0)
				this->__f_environmentOption();
		}
	}
}


bool
c_options_popup::__f_environmentOption(void)
{
	if (this->teb.gT == NULL)
	{
		this->teb.gT = new (std::nothrow) c_generalTab(this->tab);
		if (this->teb.gT == NULL || this->teb.gT->f_init() == false)
		{
			return false;
		}
	}

	this->labelTitle->setText(tr("Environment"));
	this->tab->addTab(this->teb.gT, tr("General"));
	return true;
}
