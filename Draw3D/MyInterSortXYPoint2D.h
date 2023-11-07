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


#ifndef _MYINTERSORTXYPOINT2D_H_
#define _MYINTERSORTXYPOINT2D_H_

#include <QList>
#include <QPoint>
#include <QDebug>

void MyInterSortXYPoint2D(QList<QPoint> *MyPoints2DXY, QPoint Point)
{
	MyPoints2DXY->append(Point);
	//if (MyPoints2DXY->size() == 0)
	//{
	//	MyPoints2DXY->append(Point);
	//}
	//else
	//{
	//	for (int i = 0; i <= MyPoints2DXY->size() - 1; i++)
	//	{
	//		if (Point.x() <= MyPoints2DXY->value(i).x())
	//		{
	//			MyPoints2DXY->insert(i, Point);
	//			break;
	//		}
	//		else if (Point.x() > MyPoints2DXY->value(i).x())
	//		{
	//			MyPoints2DXY->append(Point);
	//			break;
	//		}
	//	}
	//}
}

#endif // !_MYINTERSORTXYPOINT2D_H_
