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


#ifndef _MYSORTPOLYGONS2D_H_
#define _MYSORTPOLYGONS2D_H_

#include <QList>
#include <QDebug>

#include "MyVectorXVector2D.h"
#include "MyLine2D.h"
#include "MyPlane2D.h"

void MySortPolyGons2D(MyPlane2D* MyPlane)
{
	QPoint PointA, PointB, PointC;
	MyLine2D LineChange;
	QList<MyLine2D> PolyGonsCutChange;

	PointA = MyPlane->MyPolyGons2D[0].at(0).MyLineStart;
	PointB = MyPlane->MyPolyGons2D[0].at(0).MyLineEnd;
	PointC = MyPlane->MyPolyGons2D[0].at(1).MyLineEnd;

	if (MyVectorXVector2D(PointA, PointB, PointC)) //初始对于屏幕为顺时针
	{

	}
	else //初始对于屏幕为逆时针
	{
		for (int i = MyPlane->MyPolyGons2D[0].size() - 1; i >= 0; i--)
		{
			LineChange.MyLineStart = MyPlane->MyPolyGons2D[0].value(i).MyLineEnd;
			LineChange.MyLineEnd = MyPlane->MyPolyGons2D[0].value(i).MyLineStart;
			LineChange.MyLineID = MyPlane->MyPolyGons2D[0].value(i).MyLineID;
			LineChange.MyLineColor = MyPlane->MyPolyGons2D[0].value(i).MyLineColor;
			LineChange.MyLineType = MyPlane->MyPolyGons2D[0].value(i).MyLineType;
			LineChange.MyLineWide = MyPlane->MyPolyGons2D[0].value(i).MyLineWide;
			PolyGonsCutChange.append(LineChange);
		}
		MyPlane->MyPolyGons2D[0].clear();
		MyPlane->MyPolyGons2D[0].append(PolyGonsCutChange);
		PolyGonsCutChange.clear();
	}
}

#endif // !_MYSORTPOLYGONS2D_H_
