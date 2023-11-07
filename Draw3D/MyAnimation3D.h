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


#ifndef _MYANIMATION3D_H_
#define _MYANIMATION3D_H_

#include <QDebug>

#include "MyPoint3D.h"
#include "MyStretchSolid3D.h"
#include "MyRot3D.h"
#include "MyTrans3D.h"

void MyAnimation3D(MyStretchSolid3D* solid3D, MyPoint3D pos, MyPoint3D trans3D, MyPoint3D rot3D)
{
	MyTrans3D(solid3D, trans3D);
	MyRot3D(solid3D, pos, rot3D.x, rot3D.y, rot3D.z);
}

#endif // !_MYANIMATION3D_H_
