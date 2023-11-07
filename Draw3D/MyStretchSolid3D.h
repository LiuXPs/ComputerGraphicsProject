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


#ifndef _MYSTRETCHSOLID3D_H_
#define _MYSTRETCHSOLID3D_H_

#include <QDebug>

#include "MyPlane2D.h"
#include "MyPlane3D.h"

class MyStretchSolid3D
{
public:
	MyPlane3D MySolidStart3D;
	MyPlane3D MySolidEnd3D;
	MyPlane2D MyPlaneOriginal2D;
	double MySolidLength3D;

	void MyClearSolid() //清除实体
	{
		this->MySolidStart3D.MyClearPolyGons();
		this->MySolidEnd3D.MyClearPolyGons();
		this->MyPlaneOriginal2D.MyClearPolyGons();
		this->MySolidLength3D = 0;
	}

	MyStretchSolid3D& operator=(MyStretchSolid3D& MySolid) //实体赋值
	{
		this->MyClearSolid();
		this->MySolidStart3D = MySolid.MySolidStart3D;
		this->MySolidEnd3D = MySolid.MySolidEnd3D;
		this->MyPlaneOriginal2D = MySolid.MyPlaneOriginal2D;
		this->MySolidLength3D = MySolid.MySolidLength3D;

		return *this;
	}

	bool operator==(MyStretchSolid3D& MySolid) //判断两实体是否相等
	{
		if (this->MyPlaneOriginal2D.MyPolyGonsNum2D != MySolid.MyPlaneOriginal2D.MyPolyGonsNum2D)
		{
			return false;
		}
		else if (this->MySolidLength3D != MySolid.MySolidLength3D)
		{
			return false;
		}
		else
		{
			if (this->MyPlaneOriginal2D == MySolid.MyPlaneOriginal2D)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

private:

};

#endif // !_MYSTRETCHSOLID3D_H_
