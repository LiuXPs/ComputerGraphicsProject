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


#ifndef _MYPLANE3D_H_
#define _MYPLANE3D_H_

#include <QList>
#include <QColor>
#include <QPoint>

#include "MyPoint3D.h"
#include "MyLine3D.h"

class MyPlane3D
{
public:
	QList<MyLine3D> MyPolyGons3D[100]; //多边形对应的线段
	QList<QColor> MyPolyGonsColor3D; //多边形颜色
	int MyPolyGonsNum3D = 0; //多边形对应的数量
	int MyPolyGonsID3D = 1; //多边形编号

	void MyClearPolyGons() //多边形清空
	{
		for (int i = 0; i < this->MyPolyGonsNum3D; i++)
		{
			this->MyPolyGons3D[i].clear();
		}
		this->MyPolyGonsColor3D.clear();
		this->MyPolyGonsNum3D = 0;
		this->MyPolyGonsID3D = 1;
	}

	MyPlane3D& operator=(const MyPlane3D& MyPlane) //多边形赋值
	{
		this->MyClearPolyGons();
		for (int i = 0; i < MyPlane.MyPolyGonsNum3D; i++)
		{
			this->MyPolyGons3D[i].append(MyPlane.MyPolyGons3D[i]);
		}
		this->MyPolyGonsColor3D.append(MyPlane.MyPolyGonsColor3D);
		this->MyPolyGonsNum3D = MyPlane.MyPolyGonsNum3D;
		this->MyPolyGonsID3D = MyPlane.MyPolyGonsID3D;

		return *this;
	}

	bool operator==(const MyPlane3D& MyPlane) //判断两个多边形是否相等
	{
		if (this->MyPolyGonsNum3D != MyPlane.MyPolyGonsNum3D)
		{
			return false;
		}
		else
		{
			if (this->MyPolyGons3D == MyPlane.MyPolyGons3D)
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

#endif // !_MYPLANE3D_H_
