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


#ifndef _MYVECTORDOTVECTOR3D_H_
#define _MYVECTORDOTVECTOR3D_H_

#include <QtMath>

#include "MyVector3D.h"

double MyVectorDotVector3D(MyVector3D vectorA, MyVector3D vectorB)
{
	MyVector3D VectorA, VectorB;
	double value;

	//单位化
	if (vectorA.vx != 0 || vectorA.vy != 0 || vectorA.vz != 0)
	{
		VectorA.vx = vectorA.vx / sqrt(pow(vectorA.vx, 2) + pow(vectorA.vy, 2) + pow(vectorA.vz, 2));
		VectorA.vy = vectorA.vy / sqrt(pow(vectorA.vx, 2) + pow(vectorA.vy, 2) + pow(vectorA.vz, 2));
		VectorA.vz = vectorA.vz / sqrt(pow(vectorA.vx, 2) + pow(vectorA.vy, 2) + pow(vectorA.vz, 2));
	}

	if (vectorB.vx != 0 || vectorB.vy != 0 || vectorB.vz != 0)
	{
		VectorB.vx = 1.0 * vectorB.vx / sqrt(pow(vectorB.vx, 2) + pow(vectorB.vy, 2) + pow(vectorB.vz, 2));
		VectorB.vy = 1.0 * vectorB.vy / sqrt(pow(vectorB.vx, 2) + pow(vectorB.vy, 2) + pow(vectorB.vz, 2));
		VectorB.vz = 1.0 * vectorB.vz / sqrt(pow(vectorB.vx, 2) + pow(vectorB.vy, 2) + pow(vectorB.vz, 2));
	}

	//内积
	value = 1.0 * (VectorA.vx * VectorB.vx + VectorA.vy * VectorB.vy + VectorA.vz * VectorB.vz);

	return value;
}

#endif // !_MYVECTORDOTVECTOR3D_H_
