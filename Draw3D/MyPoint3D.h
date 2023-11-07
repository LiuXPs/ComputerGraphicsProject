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


#ifndef _MYPOINT3D_H_
#define _MYPOINT3D_H_

#include <QPoint>

class MyPoint3D
{
public:
	double x, y, z, s;

	MyPoint3D& operator=(const QPoint& point2D) //重载=等号操作符，实现二维点赋值给三维点
	{
		this->x = point2D.x();
		this->y = point2D.y();
		this->z = 0;
		this->s = 1;
		return *this;
	}

	MyPoint3D& operator=(const MyPoint3D& point3D) //重载=等号操作符，实现三维点赋值
	{
		this->x = point3D.x;
		this->y = point3D.y;
		this->z = point3D.z;
		this->s = point3D.s;
		return *this;
	}

	bool operator==(const MyPoint3D& point3D) // 重载==双等号操作符，判断两三维点是否相同
	{
		double error = 0.1;
		if ((abs(this->x - point3D.x) < error) && (abs(this->y - point3D.y) < error) && (abs(this->z - point3D.z) < error))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	QPoint& To2DPoint() //三维点转化为屏幕二维点
	{

        point_return.setX(int(this->x + 0.5));
        point_return.setY(int(this->y + 0.5));
        return point_return;
	}

private:
    QPoint point_return;;

};

#endif // !_MYPOINT3D_H_
