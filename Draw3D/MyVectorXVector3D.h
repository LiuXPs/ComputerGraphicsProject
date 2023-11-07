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


#ifndef _MYVECTORXVECTOR3D_H_
#define _MYVECTORXVECTOR3D_H_

#include "MyPoint3D.h"
#include "MyVector3D.h"

MyVector3D MyVectorXVector3D(MyVector3D vectorA, MyVector3D vectorB)
{
	MyVector3D vector;
	vector.vx = 1.0 * vectorA.vy * vectorB.vz - 1.0 * vectorB.vy * vectorA.vz;
	vector.vy = 1.0 * vectorA.vz * vectorB.vx - 1.0 * vectorB.vz * vectorA.vx;
	vector.vz = 1.0 * vectorA.vx * vectorB.vy - 1.0 * vectorB.vx * vectorA.vy;

	return vector;
}
MyVector3D MyVectorXVector3D(MyPoint3D pointA, MyPoint3D pointB, MyPoint3D pointC)
{
	MyVector3D vector;
	vector.vx = 1.0 * (pointB.y - pointA.y) * (pointC.z - pointB.z) - 1.0 * (pointC.y - pointB.y) * (pointB.z - pointA.z);
	vector.vy = 1.0 * (pointB.z - pointA.z) * (pointC.x - pointB.x) - 1.0 * (pointC.z - pointB.z) * (pointB.x - pointA.x);
	vector.vz = 1.0 * (pointB.x - pointA.x) * (pointC.y - pointB.y) - 1.0 * (pointC.x - pointB.x) * (pointB.y - pointA.y);

	return vector;
}

#endif // !_MYVECTORXVECTOR3D_H_