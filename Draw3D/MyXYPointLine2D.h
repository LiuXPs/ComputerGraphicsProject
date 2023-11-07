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


#ifndef _MYXYPOINTLINE2D_H_
#define _MYXYPOINTLINE2D_H_

#include <QPoint>

#include "MyLine2D.h"

//求两直线的交点
QPoint MyXYPointLine2D(MyLine2D LineA, MyLine2D LineB)
{
	QPoint Point;
	int x, y;
	int a1, b1, c1;
	int a2, b2, c2;
	a1 = LineA.MyLineStart.y() - LineA.MyLineEnd.y();
	b1 = LineA.MyLineEnd.x() - LineA.MyLineStart.x();
	c1 = LineA.MyLineStart.x()*LineA.MyLineEnd.y() - LineA.MyLineEnd.x()*LineA.MyLineStart.y();
	a2 = LineB.MyLineStart.y() - LineB.MyLineEnd.y();
	b2 = LineB.MyLineEnd.x() - LineB.MyLineStart.x();
	c2 = LineB.MyLineStart.x()*LineB.MyLineEnd.y() - LineB.MyLineEnd.x()*LineB.MyLineStart.y();
	x = int((1.0*c2*b1 - 1.0*c1*b2) / (1.0*a1*b2 - 1.0*a2*b1) + 0.5);
	y = int((1.0*c1*a2 - 1.0*c2*a1) / (1.0*a1*b2 - 1.0*a2*b1) + 0.5);
	Point.setX(x);
	Point.setY(y);
	return Point;
}

QPoint MyXYPointLine2D(QPoint PointA, QPoint PointB, QPoint Point0, QPoint Point1)
{
	QPoint Point;
	int x, y;
	int a1, b1, c1;
	int a2, b2, c2;
	a1 = PointA.y() - PointB.y();
	b1 = PointB.x() - PointA.x();
	c1 = PointA.x()*PointB.y() - PointB.x()*PointA.y();
	a2 = Point0.y() - Point1.y();
	b2 = Point1.x() - Point0.x();
	c2 = Point0.x()*Point1.y() - Point1.x()*Point0.y();
	x = int((1.0*c2*b1 - 1.0*c1*b2) / (1.0*a1*b2 - 1.0*a2*b1) + 0.5);
	y = int((1.0*c1*a2 - 1.0*c2*a1) / (1.0*a1*b2 - 1.0*a2*b1) + 0.5);
	Point.setX(x);
	Point.setY(y);
	return Point;
}

#endif // !_MYXYPOINTLINE2D_H_



