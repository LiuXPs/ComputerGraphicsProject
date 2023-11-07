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


#ifndef _MYGETCHANGEMAT3D_H_
#define _MYGETCHANGEMAT3D_H_

#include <QtMath>

void MyGetChangeMat3D(double(&MyChangeMat3D)[4][4], int MyChangeMatFlage3D, double MyChangeMatDx3D, double MyChangeMatDy3D, double MyChangeMatDz3D, double MyChangeMatAngle3D, double MyChangeMatScale3D)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MyChangeMat3D[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		MyChangeMat3D[i][i] = 1;
	}

	switch (MyChangeMatFlage3D)
	{
	case 0: //平移
	{
		MyChangeMat3D[3][0] = MyChangeMatDx3D;
		MyChangeMat3D[3][1] = MyChangeMatDy3D;
		MyChangeMat3D[3][2] = MyChangeMatDz3D;
		break;
	}

	case 1: //x轴旋转
	{
		MyChangeMat3D[1][1] = cos(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[1][2] = sin(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[2][1] = -sin(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[2][2] = cos(MyChangeMatAngle3D*M_PI / 180);
		break;
	}

	case 2: //y轴旋转
	{
		MyChangeMat3D[0][0] = cos(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[0][2] = -sin(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[2][0] = sin(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[2][2] = cos(MyChangeMatAngle3D*M_PI / 180);
		break;
	}

	case 3: //z轴旋转
	{
		MyChangeMat3D[0][0] = cos(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[0][1] = sin(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[1][0] = -sin(MyChangeMatAngle3D*M_PI / 180);
		MyChangeMat3D[1][1] = cos(MyChangeMatAngle3D*M_PI / 180);
		break;
	}

	case 4: //缩放
	{
		//MyChangeMat3D[3][3] = MyChangeMatScale3D;
		for (int i = 0; i < 3; i++)
		{
			MyChangeMat3D[i][i] = MyChangeMatScale3D;
		}
		break;
	}

	case 5: //yoz镜像
	{
		MyChangeMat3D[0][0] = -1;
		break;
	}

	case 6: //xoz镜像
	{
		MyChangeMat3D[1][1] = -1;
		break;
	}

	case 7: //xoy镜像
	{
		MyChangeMat3D[2][2] = -1;
		break;
	}

	case 8: //沿x含y错移
	{
		MyChangeMat3D[1][0] = MyChangeMatDy3D;
		break;
	}

	case 9: //沿x含z错移
	{
		MyChangeMat3D[2][0] = MyChangeMatDz3D;
		break;
	}

	case 10: //沿y含z错移
	{
		MyChangeMat3D[2][1] = MyChangeMatDz3D;
		break;
	}

	case 11: //沿y含x错移
	{
		MyChangeMat3D[0][1] = MyChangeMatDx3D;
		break;
	}

	case 12: //沿z含x错移
	{
		MyChangeMat3D[0][2] = MyChangeMatDx3D;
		break;
	}

	case 13: //沿z含y错移
	{
		MyChangeMat3D[1][2] = MyChangeMatDy3D;
		break;
	}

	default:
		break;
	}
}

#endif // !_MYGETCHANGEMAT3D_H_
