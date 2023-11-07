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


#ifndef _MY2DSTRETCH3D_H_
#define _MY2DSTRETCH3D_H_

#include <QDebug>

#include "MyPlane2D.h"
#include "MyPlane3D.h"
#include "MySortPolyGons2D.h"
#include "MyStretchSolid3D.h"

void My2DStretch3D(MyStretchSolid3D* MySolid3D)
{
	MyLine2D MyChangeLine2D;
	MyLine3D MyChangeLine3D1, MyChangeLine3D2;

	MySolid3D->MySolidStart3D.MyClearPolyGons();
	MySolid3D->MySolidEnd3D.MyClearPolyGons();

	MySortPolyGons2D(&MySolid3D->MyPlaneOriginal2D);

	for (int i = 0; i < MySolid3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
	{
		for (int j = 0; j < MySolid3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
		{
			MyChangeLine2D = MySolid3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j);
			MyChangeLine3D1 = MyChangeLine2D;
			MyChangeLine3D2 = MyChangeLine2D;
			MyChangeLine3D1.MyLineStart.z = 0;
			MyChangeLine3D1.MyLineEnd.z = 0;
			MyChangeLine3D2.MyLineStart.z = MySolid3D->MySolidLength3D;
			MyChangeLine3D2.MyLineEnd.z = MySolid3D->MySolidLength3D;
			MySolid3D->MySolidStart3D.MyPolyGons3D[i].append(MyChangeLine3D1);
			MySolid3D->MySolidEnd3D.MyPolyGons3D[i].append(MyChangeLine3D2);
		}
	}
	MySolid3D->MySolidStart3D.MyPolyGonsColor3D = MySolid3D->MyPlaneOriginal2D.MyPolyGonsColor2D;
	MySolid3D->MySolidStart3D.MyPolyGonsID3D = MySolid3D->MyPlaneOriginal2D.MyPolyGonsID2D;
	MySolid3D->MySolidStart3D.MyPolyGonsNum3D = MySolid3D->MyPlaneOriginal2D.MyPolyGonsNum2D;

	MySolid3D->MySolidEnd3D.MyPolyGonsColor3D = MySolid3D->MyPlaneOriginal2D.MyPolyGonsColor2D;
	MySolid3D->MySolidEnd3D.MyPolyGonsID3D = MySolid3D->MyPlaneOriginal2D.MyPolyGonsID2D;
	MySolid3D->MySolidEnd3D.MyPolyGonsNum3D = MySolid3D->MyPlaneOriginal2D.MyPolyGonsNum2D;
}

#endif // !_MY2DSTRETCH3D_H_
