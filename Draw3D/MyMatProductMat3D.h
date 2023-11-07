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


#ifndef _MYMATPRODUCTMAT3D_H_
#define _MYMATPRODUCTMAT3D_H_

double MyMatProductMat3D(double(&MyMat)[4][4], double(&MyMat1)[4][4], double(&MyMat2)[4][4])
{
	double sum;

	for (int i = 0; i < 4; i++) //矩阵MyMat1的行数
	{
		for (int j = 0; j < 4; j++) // //矩阵MyMat2的列数
		{
			sum = 0;
			for (int k = 0; k < 4; k++) //矩阵MyMat1的列数
			{
				sum = sum + 1.0*MyMat1[i][k] * MyMat2[k][j];
			}
			MyMat[i][j] = sum;
		}
	}

	return MyMat[4][4];
}

#endif // !_MYMATPRODUCTMAT3D_H_