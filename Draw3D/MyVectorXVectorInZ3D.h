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


#ifndef _MYVECTORXVECTORINZ3D_H_
#define _MYVECTORXVECTORINZ3D_H_

#include "MyPoint3D.h"
#include "MyVector3D.h"

//三维向量叉乘的Z分量
double MyVectorXVectorInZ3D(MyVector3D vectorA, MyVector3D vectorB)
{
	MyVector3D vector;
	vector.vz = 1.0 * vectorA.vx * vectorB.vy - 1.0 * vectorB.vx * vectorA.vy;

	return vector.vz;
}

double MyVectorXVectorInZ3D(MyPoint3D pointA, MyPoint3D pointB, MyPoint3D pointC)
{
	MyVector3D vector;
	vector.vz = 1.0 * (pointB.x - pointA.x) * (pointC.y - pointB.y) - 1.0 * (pointC.x - pointB.x) * (pointB.y - pointA.y);

	return vector.vz;
}

#endif // !_MYVECTORXVECTORINZ3D_H_