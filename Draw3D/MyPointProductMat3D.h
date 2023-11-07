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


#ifndef _MYPOINTPRODUCTMAT3D_H_
#define _MYPOINTPRODUCTMAT3D_H_

#include "MyPoint3D.h"

MyPoint3D MyPointProductMat3D(MyPoint3D MyPoint, double MyMat[4][4])
{
	double sum;
	double MyPointVector[1][4], MyNewPointVector[1][4];

	MyPointVector[0][0] = MyPoint.x;
	MyPointVector[0][1] = MyPoint.y;
	MyPointVector[0][2] = MyPoint.z;
	MyPointVector[0][3] = MyPoint.s;

	for (int i = 0; i < 4; i++)
	{
		sum = 0;
		for (int j = 0; j < 4; j++)
		{
			sum = sum + 1.0*MyPointVector[0][j] * MyMat[j][i];
		}
		MyNewPointVector[0][i] = int(sum + 0.5);
	}

	MyPoint.x = MyNewPointVector[0][0];
	MyPoint.y = MyNewPointVector[0][1];
	MyPoint.z = MyNewPointVector[0][2];
	MyPoint.s = MyNewPointVector[0][3];

	return MyPoint;
}

#endif // !_MYPOINTPRODUCTMAT3D_H_