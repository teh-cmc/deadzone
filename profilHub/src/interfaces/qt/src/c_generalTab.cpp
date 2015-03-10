/**
 * General Tab of Option Popup
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


#include <iostream>
#include <QGridLayout>
#include <QApplication>
#include <QLocale>
#include <QVBoxLayout>
#include <QSettings>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <c_generalTab.h>
#include "../include/c_generalTab.h"
#include <QTranslator>

using namespace	pH;

c_generalTab::c_generalTab(QWidget* father) : QWidget(father)
{
}

c_generalTab::~c_generalTab(void)
{

}


	bool
c_generalTab::f_init(void)
{
	QVBoxLayout*	vbox;
	QGroupBox*      ui_group;
	QGridLayout*	grid;
	QLabel*         lang;
	QComboBox*  	langBox;
	QSettings       settings("profilHubTeam", "profilHub");

	if (settings.value("lang", "").toString() == "")
	{
		this->selectedLang = QLocale::system().name().section('_', 0, 0);
	}
	else
	{
		this->selectedLang = settings.value("lang").toString();
	}
	grid = new (std::nothrow) QGridLayout();
	langBox = new (std::nothrow) QComboBox(this);
	vbox = new (std::nothrow) QVBoxLayout();
	ui_group = new (std::nothrow) QGroupBox(tr("User Interface"), this);
	lang = new (std::nothrow) QLabel(tr("Language"), this);

	if (grid == NULL ||
			langBox == NULL ||
			vbox == NULL ||
			ui_group == NULL ||
			lang == NULL)
	{
		delete grid;
		delete langBox;
		delete vbox;
		delete ui_group;
		delete lang;
		return false;
	}

	langBox->addItem(tr("French"));
	langBox->addItem(tr("English"));
	if (this->selectedLang == "fr")
		langBox->setCurrentIndex(0);
	else
		langBox->setCurrentIndex(1);
	connect(langBox, SIGNAL(currentIndexChanged(int)), this, SLOT(s_handleSelectionChanged(int)));
	grid->addWidget(lang, 0, 0);
	grid->addWidget(langBox, 0, 1);
	ui_group->setLayout(grid);
	vbox->addWidget(ui_group);
	this->setLayout(vbox);
	return true;
}


	void
c_generalTab::s_handleSelectionChanged(int index)
{

	if (index == 0)
	{
		this->selectedLang = "fr";
	}
	else if (index == 1)
	{
		this->selectedLang = "en";
	}
}
