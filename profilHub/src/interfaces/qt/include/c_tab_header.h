/**
 * Used to describe the content of a tab
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

#ifndef __TAB_HEADER_CLASS_HEADER__
#define __TAB_HEADER_CLASS_HEADER__

#include <QFrame>

class	QFrame;
class	QLabel;
class	QHBoxLayout;

namespace	pH
{
	class	c_tab_label;
	class	c_img;
	class	c_tab;
	enum	e_tab_header_state
	{
		QUITABLE,
		NOT_QUITABLE
	};

	class	c_tab_header: public QFrame
	{
		Q_OBJECT
		public:
						c_tab_header(QWidget* father, const char* label_title, const char* image_path, e_tab_header_state state);
			virtual			~c_tab_header(void);
			bool			f_init(c_tab* tab);
			c_tab_label*		f_label(void);
		public slots:
			void			f_close_tab(void);
		protected:
		private:
			const char*		__v_label_title;
			const char*		__v_image_path;
			c_tab_label*		__v_label;
			c_img*			__v_image;
			e_tab_header_state	__v_state;
			QHBoxLayout*		__v_layout;
			c_tab*			__v_tab;

			bool			__f_init_label(void);
			bool			__f_init_image(void);
			bool			__f_init_layout(void);
	};
}

#endif
