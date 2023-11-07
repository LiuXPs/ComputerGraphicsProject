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


#ifndef _MYTRANS3D_H_
#define _MYTRANS3D_H_

#include <QList>
#include <QDebug>

#include "MyStretchSolid3D.h"
#include "MyPoint3D.h"
#include "MyLine3D.h"
#include "MyGetChangeMat3D.h"
#include "MyMatProductMat3D.h"
#include "MyPointProductMat3D.h"

void MyTrans3D(MyStretchSolid3D* MySolid, MyPoint3D MyChangeMatPoint3D)
{
	QList<MyLine3D> MyNewPolyGonsStart3D, MyNewPolyGonsEnd3D;
	MyLine3D MyNewLineStart, MyNewLineEnd;

	double MyTransMat3D[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	MyGetChangeMat3D(MyTransMat3D, 0, MyChangeMatPoint3D.x, MyChangeMatPoint3D.y, MyChangeMatPoint3D.z, 0, 1);

	for (int i = 0; i < MySolid->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
	{
		MyNewPolyGonsStart3D.clear();
		MyNewPolyGonsEnd3D.clear();

		for (int j = 0; j < MySolid->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
		{
			MyNewLineStart = MySolid->MySolidStart3D.MyPolyGons3D[i].value(j);
			MyNewLineStart.MyLineStart = MyPointProductMat3D(MySolid->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart, MyTransMat3D);
			MyNewLineStart.MyLineEnd = MyPointProductMat3D(MySolid->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd, MyTransMat3D);

			MyNewLineEnd = MySolid->MySolidEnd3D.MyPolyGons3D[i].value(j);
			MyNewLineEnd.MyLineStart = MyPointProductMat3D(MySolid->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineStart, MyTransMat3D);
			MyNewLineEnd.MyLineEnd = MyPointProductMat3D(MySolid->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd, MyTransMat3D);

			MyNewPolyGonsStart3D.append(MyNewLineStart);
			MyNewPolyGonsEnd3D.append(MyNewLineEnd);
		}

		MySolid->MySolidStart3D.MyPolyGons3D[i].clear();
		MySolid->MySolidStart3D.MyPolyGons3D[i].append(MyNewPolyGonsStart3D);
		MySolid->MySolidEnd3D.MyPolyGons3D[i].clear();
		MySolid->MySolidEnd3D.MyPolyGons3D[i].append(MyNewPolyGonsEnd3D);

		MyNewPolyGonsStart3D.clear();
		MyNewPolyGonsEnd3D.clear();
	}
}

#endif // !_MYTRANS3D_H_
