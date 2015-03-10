/**
 * This is the filter class widget
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

#ifndef __FILTER_CLASS_HEADER__
#define __FILTER_CLASS_HEADER__

#include <QFrame>

class	QLabel;
class	QHBoxLayout;
class	QListWidgetItem;

namespace	pH
{
	class	c_img;
	class	c_filter: public QFrame
	{
		public:
						c_filter(QWidget* father, QListWidgetItem* widget_item, const char* title);
			virtual			~c_filter(void);
			bool			f_init(void);
			QListWidgetItem*	f_widget_item(void);
			QLabel*			f_label(void);
		protected:
		private:
			const char*		__v_title;
			c_img*			__v_image;
			QLabel*			__v_label;
			QListWidgetItem*	__v_widget_item;
			QHBoxLayout*		__v_layout;

			bool			__f_init_layout(void);
			bool			__f_init_title(void);
			bool			__f_init_image(void);
	};
}

#endif
