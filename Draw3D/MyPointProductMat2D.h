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


#ifndef _MYPOINTPRODUCTMAT2D_H_
#define _MYPOINTPRODUCTMAT2D_H_

#include <QPoint>

QPoint MyPointProductMat2D(QPoint MyPoint, double MyMat[3][3])
{
	double sum;
	double MyPointVector[1][3], MyNewPointVector[1][3];

	MyPointVector[0][0] = MyPoint.x();
	MyPointVector[0][1] = MyPoint.y();
	MyPointVector[0][2] = 1.0;

	for (int i = 0; i < 3; i++)
	{
		sum = 0;
		for (int j = 0; j < 3; j++)
		{
			sum = sum + 1.0*MyPointVector[0][j] * MyMat[j][i];
		}
		MyNewPointVector[0][i] = int(sum + 0.5);
	}

	MyPoint.setX(MyNewPointVector[0][0]);
	MyPoint.setY(MyNewPointVector[0][1]);

	return MyPoint;
}

#endif // !_MYPOINTPRODUCTMAT2D_H_
