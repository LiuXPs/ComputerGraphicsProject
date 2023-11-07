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


#ifndef _MYGETCHANGEMAT2D_H_
#define _MYGETCHANGEMAT2D_H_

#include <QtMath>

void MyGetChangeMat2D(double(&MyChangeMat2D)[3][3], int MyChangeMatFlage2D, double MyChangeMatDx2D, double MyChangeMatDy2D, double MyChangeMatAngle2D, double MyChangeMatScale2D)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MyChangeMat2D[i][j] = 0;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		MyChangeMat2D[i][i] = 1;
	}

	switch (MyChangeMatFlage2D)
	{
	case 0: //平移
	{
		MyChangeMat2D[2][0] = MyChangeMatDx2D;
		MyChangeMat2D[2][1] = MyChangeMatDy2D;
		break;
	}

	case 1: //旋转
	{
		MyChangeMat2D[0][0] = cos(MyChangeMatAngle2D*M_PI / 180);
		MyChangeMat2D[0][1] = sin(MyChangeMatAngle2D*M_PI / 180);
		MyChangeMat2D[1][0] = -sin(MyChangeMatAngle2D*M_PI / 180);
		MyChangeMat2D[1][1] = cos(MyChangeMatAngle2D*M_PI / 180);
		break;
	}

	case 2: //x轴镜像
	{
		MyChangeMat2D[1][1] = -1;
		break;
	}

	case 3: //y轴镜像
	{
		MyChangeMat2D[0][0] = -1;
		break;
	}

	case 4:  //x轴错移
	{
		MyChangeMat2D[1][0] = MyChangeMatDx2D;
		break;
	}

	case 5: //y轴错移
	{
		MyChangeMat2D[0][1] = MyChangeMatDy2D;
		break;
	}

	case 6: //全比例缩放
	{
		//MyChangeMat2D[2][2] = MyChangeMatScale2D;
		for (int i = 0; i < 2; i++)
		{
			MyChangeMat2D[i][i] = MyChangeMatScale2D;
		}
		break;
	}

	default:
		break;
	}
}


#endif // !_MYGETCHANGEMAT2D_H_
