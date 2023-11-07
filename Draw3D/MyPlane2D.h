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


#ifndef _MYPLANE2D_H_
#define _MYPLANE2D_H_

#include <QList>
#include <QColor>
#include <QPoint>

#include "MyLine2D.h"

class MyPlane2D
{
public:
	QList<MyLine2D> MyPolyGons2D[100]; //多边形对应的线段
	QList<QColor> MyPolyGonsColor2D; //多边形颜色
	int MyPolyGonsNum2D = 0; //多边形对应的数量
	int MyPolyGonsID2D = 1; //多边形编号

	void MyClearPolyGons() //多边形清空
	{
		for (int i = 0; i < this->MyPolyGonsNum2D; i++)
		{
			this->MyPolyGons2D[i].clear();
		}
		this->MyPolyGonsColor2D.clear();
		this->MyPolyGonsNum2D = 0;
		this->MyPolyGonsID2D = 1;
	}

	MyPlane2D& operator=(const MyPlane2D& MyPlane) //多边形赋值
	{
		this->MyClearPolyGons();
		for (int i = 0; i < MyPlane.MyPolyGonsNum2D; i++)
		{
			this->MyPolyGons2D[i].append(MyPlane.MyPolyGons2D[i]);
		}
		this->MyPolyGonsColor2D.append(MyPlane.MyPolyGonsColor2D);
		this->MyPolyGonsNum2D = MyPlane.MyPolyGonsNum2D;
		this->MyPolyGonsID2D = MyPlane.MyPolyGonsID2D;

		return *this;
	}

	bool operator==(const MyPlane2D& MyPlane) //判断两个多边形是否相等
	{
		if (this->MyPolyGonsNum2D != MyPlane.MyPolyGonsNum2D)
		{
			return false;
		}
		else
		{
			if (this->MyPolyGons2D == MyPlane.MyPolyGons2D)
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

#endif // !_MYPLANE2D_H_
