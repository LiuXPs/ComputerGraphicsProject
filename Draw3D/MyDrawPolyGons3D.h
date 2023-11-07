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


#ifndef _MYDRAWPOLYGONS3D_H_
#define _MYDRAWPOLYGONS3D_H_

#include <QPen>
#include <QPainter>

#include "MyPlane2D.h"
#include "MyPlane3D.h"
#include "MyDDALine2D.h"

void MyDrawPolyGons3D(QPen* pen, QPainter* painter, MyPlane3D* Plane3D)
{
    MyLine3D line3d;

	for (int i = 0; i < Plane3D->MyPolyGons3D[0].size(); i++)
	{
		pen->setColor(Plane3D->MyPolyGons3D[0].value(i).MyLineColor);
		painter->setPen(*pen);
        line3d = Plane3D->MyPolyGons3D[0].value(i);
        MyDDALine2D(painter, line3d);
	}
}

#endif // !_MYDRAWPOLYGONS3D_H_
