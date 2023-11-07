/*
========================================================================================================================

* This file is part of Draw3D
*
* Copyright (C) 2018-2024 Xupeng Liu.
*
* Draw3D is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
* Draw3D is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with Draw3D.
* If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================
*/


#ifndef _MYXPOINT2D_H_
#define _MYXPOINT2D_H_

#include <QPoint>

QPoint MyXPoint2D(int y, QPoint Point1, QPoint Point2)
{
	int x;
	QPoint Point0;

	if (y == Point1.y())
	{
		x = Point1.x();
	}
	else if (y == Point2.y())
	{
		x = Point2.x();
	}
	else
	{
		x = int(1.0*(y - Point1.y())*1.0*(Point2.x() - Point1.x()) / (Point2.y() - Point1.y()) + Point1.x() + 0.5);
	}

	Point0 = QPoint(x, y);
	return Point0;
}

#endif // !_MYXPOINT2D_H_
