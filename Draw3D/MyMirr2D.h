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


#ifndef _MYMIRR2D_H_
#define _MYMIRR2D_H_

#include <QList>
#include <QPoint>
#include <QtDebug>

#include "MyLine2D.h"
#include "MyPlane2D.h"
#include "MyGetChangeMat2D.h"
#include "MyMatProductMat2D.h"
#include "MyPointProductMat2D.h"

void MyMirr2D(MyPlane2D* MyPlane, MyLine2D* MyChangeMatLine2D)
{
	QList<MyLine2D> MyNewPolyGons2D;
	MyLine2D MyNewLine;

	int A, B, C;
	double k, b, angle;

	double MyMirrMat2D[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D1[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D2[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D3[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D4[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D5[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D6[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D7[3][3] = { 0,0,0,0,0,0,0,0,0 };
	double MyMirrMat2D8[3][3] = { 0,0,0,0,0,0,0,0,0 };

	//水平线
	if (MyChangeMatLine2D->MyLineStart.y() == MyChangeMatLine2D->MyLineEnd.y())
	{
		MyGetChangeMat2D(MyMirrMat2D1, 0, 0, -MyChangeMatLine2D->MyLineStart.y(), 0, 1);
		MyGetChangeMat2D(MyMirrMat2D2, 2, 0, 0, 0, 1);
		MyGetChangeMat2D(MyMirrMat2D3, 0, 0, MyChangeMatLine2D->MyLineStart.y(), 0, 1);
		MyMatProductMat2D(MyMirrMat2D4, MyMirrMat2D1, MyMirrMat2D2);
		MyMatProductMat2D(MyMirrMat2D, MyMirrMat2D4, MyMirrMat2D3);
	}
	//竖直线
	else if (MyChangeMatLine2D->MyLineStart.x() == MyChangeMatLine2D->MyLineEnd.x())
	{
		MyGetChangeMat2D(MyMirrMat2D1, 0, -MyChangeMatLine2D->MyLineStart.x(), 0, 0, 1);
		MyGetChangeMat2D(MyMirrMat2D2, 3, 0, 0, 0, 1);
		MyGetChangeMat2D(MyMirrMat2D3, 0, MyChangeMatLine2D->MyLineStart.x(), 0, 0, 1);
		MyMatProductMat2D(MyMirrMat2D4, MyMirrMat2D1, MyMirrMat2D2);
		MyMatProductMat2D(MyMirrMat2D, MyMirrMat2D4, MyMirrMat2D3);
	}
	//一般直线
	else
	{
		A = MyChangeMatLine2D->MyLineEnd.y() - MyChangeMatLine2D->MyLineStart.y();
		B = MyChangeMatLine2D->MyLineEnd.x() - MyChangeMatLine2D->MyLineStart.x();
		C = MyChangeMatLine2D->MyLineEnd.x()*MyChangeMatLine2D->MyLineStart.y() - MyChangeMatLine2D->MyLineStart.x()*MyChangeMatLine2D->MyLineEnd.y();
		k = 1.0*A / B;
		b = 1.0*C / B;
		angle = atan(k) / M_PI * 180;

		MyGetChangeMat2D(MyMirrMat2D1, 0, 0, -b, 0, 1);
		MyGetChangeMat2D(MyMirrMat2D2, 1, 0, 0, -angle, 1);
		MyGetChangeMat2D(MyMirrMat2D3, 2, 0, 0, 0, 1);
		MyGetChangeMat2D(MyMirrMat2D4, 1, 0, 0, angle, 1);
		MyGetChangeMat2D(MyMirrMat2D5, 0, 0, b, 0, 1);
		MyMatProductMat2D(MyMirrMat2D6, MyMirrMat2D1, MyMirrMat2D2);
		MyMatProductMat2D(MyMirrMat2D7, MyMirrMat2D6, MyMirrMat2D3);
		MyMatProductMat2D(MyMirrMat2D8, MyMirrMat2D7, MyMirrMat2D4);
		MyMatProductMat2D(MyMirrMat2D, MyMirrMat2D8, MyMirrMat2D5);
	}

	for (int i = 0; i < MyPlane->MyPolyGonsNum2D; i++)
	{
		MyNewPolyGons2D.clear();

		for (int j = 0; j < MyPlane->MyPolyGons2D[i].size(); j++)
		{
			MyNewLine = MyPlane->MyPolyGons2D[i].value(j);

			MyNewLine.MyLineStart = MyPointProductMat2D(MyPlane->MyPolyGons2D[i].value(j).MyLineStart, MyMirrMat2D);
			MyNewLine.MyLineEnd = MyPointProductMat2D(MyPlane->MyPolyGons2D[i].value(j).MyLineEnd, MyMirrMat2D);

			MyNewPolyGons2D.append(MyNewLine);
		}

		MyPlane->MyPolyGons2D[i].clear();
		MyPlane->MyPolyGons2D[i].append(MyNewPolyGons2D);
		MyNewPolyGons2D.clear();
	}
}

#endif // !_MYMIRR2D_H_
