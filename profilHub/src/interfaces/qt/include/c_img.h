/**
 * This class is used to load a scaled img
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

#ifndef __IMG_CLASS_HEADER__
#define __IMG_CLASS_HEADER__

#include <QLabel>

class	QMousEvent;

namespace	pH
{
	class	c_img: public QLabel
	{
		Q_OBJECT
		public:
					c_img(QWidget* father);
			virtual		~c_img(void);
			virtual void	mouseReleaseEvent(QMouseEvent*);
			bool		f_init(const char* image_path);
		protected:
		signals:
			void		clicked(void);
		private:
	};
}

#endif
