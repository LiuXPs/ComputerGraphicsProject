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


#ifndef _MYDRAWPOLYGONS2D_H_
#define _MYDRAWPOLYGONS2D_H_

#include <QPen>
#include <QPainter>

#include "MyPlane2D.h"
#include "MyDDALine2D.h"

void MyDrawPolyGons2D(QPen* pen, QPainter* painter, MyPlane2D* Plane2D)
{
    MyLine2D line2d;

	for (int i = 0; i <= Plane2D->MyPolyGonsNum2D; i++)
	{
		for (int j = 0; j < Plane2D->MyPolyGons2D[i].size(); j++)
		{
			pen->setColor(Plane2D->MyPolyGons2D[i].value(j).MyLineColor);
			painter->setPen(*pen);
            line2d = Plane2D->MyPolyGons2D[i].value(j);
            MyDDALine2D(painter, line2d);
		}
	}
}

#endif // !_MYDRAWPOLYGONS2D_H_
