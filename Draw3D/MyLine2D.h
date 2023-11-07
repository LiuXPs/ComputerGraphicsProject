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


#ifndef _MYLINE2D_H_
#define _MYLINE2D_H_

#include <QList>
#include <QPoint>
#include <QColor>

class MyLine2D
{
public:
	QPoint MyLineStart; //起点
	QPoint  MyLineEnd; //终点
	QColor MyLineColor; //线段颜色
	int MyLineWide; //线宽
	int MyLineType; //线型
	int MyLineID; //线段对应的多边形编号

	MyLine2D& operator=(const MyLine2D& line) // 重载=等号操作符，实现直线赋值
	{
		this->MyLineStart = line.MyLineStart;
		this->MyLineEnd = line.MyLineEnd;
		this->MyLineColor = line.MyLineColor;
		this->MyLineWide = line.MyLineWide;
		this->MyLineType = line.MyLineType;
		this->MyLineID = line.MyLineID;

		return *this;
	}

	bool operator==(const MyLine2D& line) // 重载==双等号操作符，判断两直线是否相同
	{
		if (((this->MyLineStart == line.MyLineStart) && (this->MyLineEnd == line.MyLineEnd)) || ((this->MyLineStart == line.MyLineEnd) && (this->MyLineEnd == line.MyLineStart)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:

};

#endif // !_MYLINE2D_H_