/**
 * Menubar class for the profilHub Qt interface
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

#include <c_menubar.h>
#include "../include/c_menubar.h"
#include <c_options_popup.h>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <new>
#include <iostream>

using namespace	pH;

c_menubar::c_menubar(QWidget* father) : QWidget(father)
{
}

c_menubar::~c_menubar(void)
{
}

bool
c_menubar::f_init(void)
{
	this->__v_menubar = new (std::nothrow) QMenuBar(this->parentWidget());
	if (this->__v_menubar == NULL ||
	    this->__f_fileMenu(this->__v_menubar) == false ||
	    this->__f_toolMenu(this->__v_menubar) == false ||
	    this->__f_helpMenu(this->__v_menubar) == false)
		return false;
	return true;
}

QMenuBar*
c_menubar::f_getMenubar(void) const
{
	return this->__v_menubar;
}

bool
c_menubar::__f_fileMenu(QMenuBar* bar)
{
	QMenu*		fileMenu;
	QAction*	openAction;
	QAction*	saveAsAction;
	QAction*	exitAction;
	QKeySequence	saveAsKey(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
	QKeySequence	exitKey(Qt::CTRL + Qt::Key_Q);

	fileMenu = bar->addMenu(tr("&File"));
	openAction = new (std::nothrow) QAction(tr("&Open"), fileMenu);
	saveAsAction = new (std::nothrow) QAction(tr("&Save As ..."), fileMenu);
	exitAction = new (std::nothrow) QAction(tr("&Exit"), fileMenu);
	if (fileMenu == NULL ||
	    openAction == NULL ||
	    saveAsAction == NULL ||
	    exitAction == NULL)
	{
		delete fileMenu;
		delete openAction;
		delete saveAsAction;
		delete exitAction;
		return false;
	}
	openAction->setShortcuts(QKeySequence::Open);
	saveAsAction->setShortcut(saveAsKey);
	exitAction->setShortcut(exitKey);

	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	QObject::connect(openAction, SIGNAL(triggered()), this, SLOT(s_openFile()));
	QObject::connect(saveAsAction, SIGNAL(triggered()), this, SLOT(s_saveAsFile()));
	QObject::connect(exitAction, SIGNAL(triggered()), this, SLOT(s_exitApp()));
	return true;
}



bool
c_menubar::__f_toolMenu(QMenuBar* bar)
{
	QMenu*		optionMenu;
	QAction*	settingAction;

	optionMenu = bar->addMenu(tr("&Tools"));
	settingAction = new (std::nothrow) QAction(tr("&Options"), optionMenu);
	if (optionMenu == NULL ||
	    settingAction == NULL)
	{
		delete optionMenu;
		delete settingAction;
		return false;
	}

	optionMenu->addAction(settingAction);

	QObject::connect(settingAction, SIGNAL(triggered()), this, SLOT(s_setting()));
	return true;
}

bool
c_menubar::__f_helpMenu(QMenuBar* bar)
{
	QMenu*		helpMenu;
	QAction*	bugAction;
	QAction*	aboutAction;

	helpMenu = bar->addMenu(tr("&Help"));
	bugAction = new (std::nothrow) QAction(tr("&Report Bug"), helpMenu);
	aboutAction = new (std::nothrow) QAction(tr("&About profilHub"), helpMenu);
	if (helpMenu == NULL ||
	    bugAction == NULL ||
	    aboutAction == NULL)
	{
		delete helpMenu;
		delete aboutAction;
		delete bugAction;
		return false;
	}

	helpMenu->addAction(bugAction);
	helpMenu->addAction(aboutAction);

	QObject::connect(bugAction, SIGNAL(triggered()), this, SLOT(s_bug_report()));
	QObject::connect(aboutAction, SIGNAL(triggered()), this, SLOT(s_about()));
	return true;
}


//SLOT QT

void
c_menubar::s_openFile(void)
{
	QStringList	fileNames = QFileDialog::getOpenFileNames(this, tr("Open pH File"),
							"/home/", tr("ph File (*.pH *.ph)"));
	int		nbFiles = fileNames.size();

	if (nbFiles != 0)
	{
		QStringList::const_iterator	it;
		QStringList::const_iterator	end;

		it = fileNames.constBegin();
		end = fileNames.constEnd();
		while (it != end)
		{
			std::cout << it->toLocal8Bit().constData() << std::endl;
			++it;
		}
	}
}

void
c_menubar::s_saveAsFile(void)
{
	QString	fileName = QFileDialog::getSaveFileName(this, tr("Save pH File"),
							"/home/", tr("ph File (*.pH *.ph)"));
	QFile	f(fileName);

	if (f.open(QIODevice::WriteOnly | QIODevice::Text) == true)
	{
		QTextStream	out(&f);
		//out << truc << endl;
	
		std::cout << fileName.toLocal8Bit().constData() << std::endl;
	}
	//QFile oldFile;
	//oldFile.copy(fileName);
	//bool	valid = QFile::copy(oldFile, fileName);
	f.close();
}

void
c_menubar::s_exitApp(void)
{
	exit(0);
}


void
c_menubar::s_setting(void)
{
	c_options_popup	pop;

	if (pop.f_init() == false)
		return ;
	pop.exec();
}

void
c_menubar::s_bug_report(void)
{
	QDesktopServices::openUrl(QUrl("https://github.com/reyclement/profilHub/issues/new", QUrl::TolerantMode));
}

void
c_menubar::s_about(void)
{
	QMessageBox	msgBox;

	msgBox.setText("I'am profilHub in Alpha");
	msgBox.setWindowTitle(tr("About profilHub"));
	msgBox.exec();
}
