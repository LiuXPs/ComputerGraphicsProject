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


#ifndef _MYVECTORXVECTOR2D_H_
#define _MYVECTORXVECTOR2D_H_

#include <QPoint>

#include "MyLine2D.h"

//向量叉乘
bool MyVectorXVector2D(QPoint PointA, QPoint PointB, QPoint PointC)
{
	double Value;
	Value = 1.0 * (PointB.x() - PointA.x()) * (PointC.y() - PointB.y()) - 1.0 * (PointB.y() - PointA.y()) * (PointC.x() - PointB.x());
	if (Value >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif // !_MYVECTORXVECTOR2D_H_
