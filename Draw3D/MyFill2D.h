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


#ifndef _MYFILL2D_H_
#define _MYFILL2D_H_


#include <QPainter>
#include <QList>
#include <QPoint>

#include "MyInterSortXYPoint2D.h"
#include "MyXPoint2D.h"
#include "MyDDALine2D.h"
#include "MyLine2D.h"
#include "MyPlane2D.h"

void MyFill2D(QPainter* MyPainter2D, MyPlane2D* MyPlane)
{
    int MyPoints2DYmin = 0;
    int MyPoints2DYmax = 0;
    // int x = 0;
    int y = 0;
	QPoint Change;
    QPoint point_start;
    QPoint Point_end;
	QList<QPoint> MyPoints2DXY;

	//求最大最小Y值
	for (int i = 0; i < MyPlane->MyPolyGonsNum2D; i++)
	{
		for (int j = 0; j < MyPlane->MyPolyGons2D[i].size(); j++)
		{
			if (i == 0 && j == 0)
			{
				if (MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y() <= MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y())
				{
					MyPoints2DYmin = MyPlane->MyPolyGons2D[i].value(j).MyLineStart.y();
					MyPoints2DYmax = MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y();
				}
				else if (MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y() > MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y())
				{
					MyPoints2DYmax = MyPlane->MyPolyGons2D[i].value(j).MyLineStart.y();
					MyPoints2DYmin = MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y();
				}
			}
			else
			{
				if (MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y() <= MyPoints2DYmin)
				{
					MyPoints2DYmin = MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y();
				}
				else if (MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y() <= MyPoints2DYmin)
				{
					MyPoints2DYmin = MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y();
				}
				if (MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y() >= MyPoints2DYmax)
				{
					MyPoints2DYmax = MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y();
				}
				else if (MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y() >= MyPoints2DYmax)
				{
					MyPoints2DYmax = MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y();
				}
			}
		}
	}

	//填充
	for (y = MyPoints2DYmin; y <= MyPoints2DYmax; y++)
	{
		//求交点并插入
		MyPoints2DXY.clear();
		for (int i = 0; i < MyPlane->MyPolyGonsNum2D; i++)
		{
			for (int j = 0; j < MyPlane->MyPolyGons2D[i].size(); j++)
			{
				if ((y == MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y()) && (y == MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y()))
				{
					MyPoints2DXY.append(MyPlane->MyPolyGons2D[i].value(j).MyLineStart);
					MyPoints2DXY.append(MyPlane->MyPolyGons2D[i].value(j).MyLineEnd);
				}
				else if ((y > MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y()) && (y <= MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y()))
				{
					MyPoints2DXY.append(MyXPoint2D(y, MyPlane->MyPolyGons2D[i].value(j).MyLineStart, MyPlane->MyPolyGons2D[i].value(j).MyLineEnd));
				}
				else if ((y > MyPlane->MyPolyGons2D[i].at(j).MyLineEnd.y()) && (y <= MyPlane->MyPolyGons2D[i].at(j).MyLineStart.y()))
				{
					MyPoints2DXY.append(MyXPoint2D(y, MyPlane->MyPolyGons2D[i].value(j).MyLineStart, MyPlane->MyPolyGons2D[i].value(j).MyLineEnd));
				}
			}
		}

		//交点排序
		for (int i = 0; i <= MyPoints2DXY.size()-1; i++)
		{
			for (int j = i+1; j <= MyPoints2DXY.size()-1; j++)
			{
				if (MyPoints2DXY.value(i).x() >= MyPoints2DXY.value(j).x())
				{
					Change = MyPoints2DXY.value(i);
					MyPoints2DXY.replace(i, MyPoints2DXY.value(j));
					MyPoints2DXY.replace(j, Change);
				}
			}
		}

		//填充
		for (int i = 0; i <= MyPoints2DXY.size() - 1; i += 2)
        {
            point_start = MyPoints2DXY.value(i);
            Point_end = MyPoints2DXY.value(i + 1);
            MyDDALine2D(MyPainter2D, point_start, Point_end);
		}
	}
}

#endif // !_MYFILL2D_H_
