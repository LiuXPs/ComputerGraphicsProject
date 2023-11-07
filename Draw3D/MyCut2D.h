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


#ifndef _MYCUT2D_H_
#define _MYCUT2D_H_

#include <QList>
#include <QPoint>
#include <QColor>

#include "MyVectorXVector2D.h"
#include "MySortPolyGons2D.h"
#include "MyXYPointLine2D.h"
#include "MyLine2D.h"
#include "MyPlane2D.h"

void MyCut2D(MyPlane2D* MyPlane, MyPlane2D* MyPlaneCut, QColor* MyColor)
{
	QList<QPoint> MyPoints,MyPointsChange;
	QPoint PointXY;
	QPoint PointA, PointB, Point0, Point1;
	bool MyInOutFlage; //true:内侧;false:外侧
	MyLine2D MyLineChange2D;

	MySortPolyGons2D(MyPlaneCut);


	for (int i = 0; i < MyPlane->MyPolyGonsNum2D; i++)
	{
		MyPoints.clear();
		MyPointsChange.clear();
		MyPoints.append(MyPlane->MyPolyGons2D[i].value(0).MyLineStart);

		for (int j = 0; j < MyPlane->MyPolyGons2D[i].size(); j++)
		{
			MyPoints.append(MyPlane->MyPolyGons2D[i].value(j).MyLineEnd);
		}

		for (int k = 0; k < MyPlaneCut->MyPolyGons2D[0].size(); k++)
		{
			PointA = MyPlaneCut->MyPolyGons2D[0].value(k).MyLineStart;
			PointB = MyPlaneCut->MyPolyGons2D[0].value(k).MyLineEnd;
			Point0 = MyPoints.value(0);

			if (MyVectorXVector2D(PointA, PointB, Point0)) //内部
			{
				MyInOutFlage = true;
				MyPointsChange.append(Point0);
			}
			else //外部
			{
				MyInOutFlage = false;
			}

			for (int m = 1; m < MyPoints.size(); m++)
			{
				Point1 = MyPoints.value(m);
				if (MyVectorXVector2D(PointA, PointB, Point1)) //内部
				{
					if (MyInOutFlage)
					{
						MyPointsChange.append(Point1);
						Point0 = Point1;
					}
					else
					{
						PointXY = MyXYPointLine2D(PointA, PointB, Point0, Point1);
						MyPointsChange.append(PointXY);
						MyPointsChange.append(Point1);
						Point0 = Point1;
						MyInOutFlage = true;
					}
				}
				else //外部
				{
					if (MyInOutFlage)
					{
						PointXY = MyXYPointLine2D(PointA, PointB, Point0, Point1);
						MyPointsChange.append(PointXY);
						Point0 = Point1;
						MyInOutFlage = false;
					}
					else
					{
						Point0 = Point1;
					}
				}
			}

			MyPointsChange.append(MyPointsChange.value(0));
			MyPoints.clear();
			MyPoints.append(MyPointsChange);
			MyPointsChange.clear();
		}

		MyPlane->MyPolyGons2D[i].clear();
		MyPointsChange.append(MyPointsChange.value(0));

		for (int w = 0; w < MyPoints.size() - 1; w++)
		{
			MyLineChange2D.MyLineStart = MyPoints.value(w);
			MyLineChange2D.MyLineEnd = MyPoints.value(w + 1);
			MyLineChange2D.MyLineColor = *MyColor;
			MyPlane->MyPolyGons2D[i].append(MyLineChange2D);
		}

		MyPoints.clear();
		MyPointsChange.clear();
	}
}

#endif // !_MYCUT2D_H_
