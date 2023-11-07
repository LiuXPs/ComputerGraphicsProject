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


#ifndef _MYROT2D_H_
#define _MYROT2D_H_

#include <QList>
#include <QPoint>
#include <QDebug>

#include "MyLine2D.h"
#include "MyPlane2D.h"
#include "MyGetChangeMat2D.h"
#include "MyMatProductMat2D.h"
#include "MyPointProductMat2D.h"

void MyRot2D(MyPlane2D* MyPlane, QPoint MyChangeMatPoint2D, double MyChangeMatAngle2D)
{
	QList<MyLine2D> MyNewPolyGons2D;
	MyLine2D MyNewLine;

	double MyRotMat2D[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyRotMat2D1[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyRotMat2D2[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyRotMat2D3[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyRotMat2D4[3][3] = { 0,0,0,0,0,0,0,0,0 };

	MyGetChangeMat2D(MyRotMat2D1, 0, -MyChangeMatPoint2D.x(), -MyChangeMatPoint2D.y(), 0, 1);
	MyGetChangeMat2D(MyRotMat2D2, 1, 0, 0, MyChangeMatAngle2D, 1);
	MyGetChangeMat2D(MyRotMat2D3, 0, MyChangeMatPoint2D.x(), MyChangeMatPoint2D.y(), 0, 1);

	MyMatProductMat2D(MyRotMat2D4, MyRotMat2D1, MyRotMat2D2);
	MyMatProductMat2D(MyRotMat2D, MyRotMat2D4, MyRotMat2D3);

	for (int i = 0; i < MyPlane->MyPolyGonsNum2D; i++)
	{
		MyNewPolyGons2D.clear();

		for (int j = 0; j < MyPlane->MyPolyGons2D[i].size(); j++)
		{
			MyNewLine = MyPlane->MyPolyGons2D[i].value(j);

			MyNewLine.MyLineStart = MyPointProductMat2D(MyPlane->MyPolyGons2D[i].value(j).MyLineStart, MyRotMat2D);
			MyNewLine.MyLineEnd = MyPointProductMat2D(MyPlane->MyPolyGons2D[i].value(j).MyLineEnd, MyRotMat2D);

			MyNewPolyGons2D.append(MyNewLine);
		}

		MyPlane->MyPolyGons2D[i].clear();
		MyPlane->MyPolyGons2D[i].append(MyNewPolyGons2D);

		MyNewPolyGons2D.clear();
	}
}

#endif // !_MYROT2D_H_
