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


#ifndef _MYREND3D_H_
#define _MYREND3D_H_

#include <QDebug>
#include <QColor>

#include "MyPoint3D.h"
#include "MyVector3D.h"
#include "MyVectorXVector3D.h"
#include "MyVectorDotVector3D.h"

QColor MyRend3D(MyPoint3D pointA, MyPoint3D pointB, MyPoint3D pointC, 
	QColor LightColor, MyVector3D LightPos, double LightEnvironment, double LightAttenuation,
	double LightDiffuse, double LightMirror, double LightMirrorNs)
{
	QColor RendColor;
	MyVector3D LightVector, Vector1, NVector, VVector, HVector;
	double IEnvironment, IDiffuse, IMirror, ITotal;
	double LDotN, NDotH;
	
	//光源位矢单位化
	LightVector.vx = 1.0 * LightPos.vx / sqrt(pow(LightPos.vx, 2) + pow(LightPos.vy, 2) + pow(LightPos.vz, 2));
	LightVector.vy = 1.0 * LightPos.vy / sqrt(pow(LightPos.vx, 2) + pow(LightPos.vy, 2) + pow(LightPos.vz, 2));
	LightVector.vz = 1.0 * LightPos.vz / sqrt(pow(LightPos.vx, 2) + pow(LightPos.vy, 2) + pow(LightPos.vz, 2));

	IEnvironment = LightEnvironment;

	NVector = MyVectorXVector3D(pointA, pointB, pointC);
	LDotN = MyVectorDotVector3D(LightVector, NVector);
	if (LDotN < 0)
	{
		LDotN = 0;
	}
	IDiffuse = LightAttenuation * LightDiffuse * LDotN;

	VVector.vx = 0.0;
	VVector.vy = 0.0;
	VVector.vz = -1.0;
	HVector.vx = (LightVector.vx + VVector.vx) / 2;
	HVector.vy = (LightVector.vy + VVector.vy) / 2;
	HVector.vz = (LightVector.vz + VVector.vz) / 2;
	NDotH = MyVectorDotVector3D(NVector, HVector);
	if (NDotH < 0)
	{
		NDotH = 0;
	}
	IMirror = LightAttenuation * LightMirror * pow(NDotH, LightMirrorNs);

	ITotal = 1.0 * (IEnvironment + IDiffuse + IMirror) / 3;

	RendColor.setRed(int(LightColor.red() * ITotal + 0.5));
	RendColor.setGreen(int(LightColor.green() * ITotal + 0.5));
	RendColor.setBlue(int(LightColor.blue() * ITotal + 0.5));

	//return RendColor;
	return RendColor;
}

#endif // !_MYREND3D_H_
