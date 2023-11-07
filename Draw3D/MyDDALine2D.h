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


#ifndef _MYDDALINE2D_H_
#define _MYDDALINE2D_H_

#include <QPainter>
#include <QPoint>

#include "MyLine2D.h"
#include "MyLine3D.h"

void MyDDALine2D(QPainter* MyPainter, QPoint& PointStart, QPoint& PointEnd)
{
	if (PointStart.x() == PointEnd.x())
	{
		if (PointStart.y() <= PointEnd.y())
		{
			for (int i = PointStart.y(); i <= PointEnd.y(); i += 1)
			{
				MyPainter->drawPoint(PointStart.x(), i);
			}
		}
		else if (PointStart.y() > PointEnd.y())
		{
			for (int i = PointStart.y(); i >= PointEnd.y(); i -= 1)
			{
				MyPainter->drawPoint(PointStart.x(), i);
			}
		}
	}
	else if (PointStart.y() == PointEnd.y())
	{
		if (PointStart.x() <= PointEnd.x())
		{
			for (int i = PointStart.x(); i <= PointEnd.x(); i += 1)
			{
				MyPainter->drawPoint(i, PointStart.y());
			}
		}
		else if (PointStart.x() > PointEnd.x())
		{
			for (int i = PointStart.x(); i >= PointEnd.x(); i -= 1)
			{
				MyPainter->drawPoint(i, PointStart.y());
			}
		}
	}
	else
	{
		double k = 1.0 * (1.0 * PointEnd.y() - 1.0 * PointStart.y()) / (1.0 * PointEnd.x() - 1.0 * PointStart.x());
		double x = double(PointStart.x());
		double y = double(PointStart.y());
		if (abs(k) <= 1.0)
		{
			for (int i = 0; i < abs(PointEnd.x() - PointStart.x()); i += 1)
			{
				if (PointStart.x() < PointEnd.x())
				{
					x += 1;
					y += k;
				}
				else
				{
					x -= 1;
					y -= k;
				}
				MyPainter->drawPoint(int(x), int(y + 0.5));
			}
		}
		else if (abs(k) > 1.0)
		{
			for (int i = 0; i < abs(PointEnd.y() - PointStart.y()); i += 1)
			{
				if (PointStart.y() < PointEnd.y())
				{
					x += 1.0 / k;
					y += 1;
				}
				else
				{
					x -= 1.0 / k;
					y -= 1;
				}
				MyPainter->drawPoint(int(x + 0.5), int(y));
			}
		}
	}
}

void MyDDALine2D(QPainter* MyPainter, MyLine2D& MyLine)
{
	QPoint PointStart, PointEnd;
	PointStart = MyLine.MyLineStart;
	PointEnd = MyLine.MyLineEnd;

	if (PointStart.x() == PointEnd.x())
	{
		if (PointStart.y() <= PointEnd.y())
		{
			for (int i = PointStart.y(); i <= PointEnd.y(); i += 1)
			{
				MyPainter->drawPoint(PointStart.x(), i);
			}
		}
		else if (PointStart.y() > PointEnd.y())
		{
			for (int i = PointStart.y(); i >= PointEnd.y(); i -= 1)
			{
				MyPainter->drawPoint(PointStart.x(), i);
			}
		}
	}
	else if (PointStart.y() == PointEnd.y())
	{
		if (PointStart.x() <= PointEnd.x())
		{
			for (int i = PointStart.x(); i <= PointEnd.x(); i += 1)
			{
				MyPainter->drawPoint(i, PointStart.y());
			}
		}
		else if (PointStart.x() > PointEnd.x())
		{
			for (int i = PointStart.x(); i >= PointEnd.x(); i -= 1)
			{
				MyPainter->drawPoint(i, PointStart.y());
			}
		}
	}
	else
	{
		double k = 1.0 * (1.0 * PointEnd.y() - 1.0 * PointStart.y()) / (1.0 * PointEnd.x() - 1.0 * PointStart.x());
		double x = double(PointStart.x());
		double y = double(PointStart.y());
		if (abs(k) <= 1.0)
		{
			for (int i = 0; i < abs(PointEnd.x() - PointStart.x()); i += 1)
			{
				if (PointStart.x() < PointEnd.x())
				{
					x += 1;
					y += k;
				}
				else
				{
					x -= 1;
					y -= k;
				}
				MyPainter->drawPoint(int(x), int(y + 0.5));
			}
		}
		else if (abs(k) > 1.0)
		{
			for (int i = 0; i < abs(PointEnd.y() - PointStart.y()); i += 1)
			{
				if (PointStart.y() < PointEnd.y())
				{
					x += 1.0 / k;
					y += 1;
				}
				else
				{
					x -= 1.0 / k;
					y -= 1;
				}
				MyPainter->drawPoint(int(x + 0.5), int(y));
			}
		}
	}
}

void MyDDALine2D(QPainter* MyPainter, MyLine3D& MyLine)
{
	QPoint PointStart, PointEnd;
	PointStart = MyLine.MyLineStart.To2DPoint();
	PointEnd = MyLine.MyLineEnd.To2DPoint();

	if (PointStart.x() == PointEnd.x())
	{
		if (PointStart.y() <= PointEnd.y())
		{
			for (int i = PointStart.y(); i <= PointEnd.y(); i += 1)
			{
				MyPainter->drawPoint(PointStart.x(), i);
			}
		}
		else if (PointStart.y() > PointEnd.y())
		{
			for (int i = PointStart.y(); i >= PointEnd.y(); i -= 1)
			{
				MyPainter->drawPoint(PointStart.x(), i);
			}
		}
	}
	else if (PointStart.y() == PointEnd.y())
	{
		if (PointStart.x() <= PointEnd.x())
		{
			for (int i = PointStart.x(); i <= PointEnd.x(); i += 1)
			{
				MyPainter->drawPoint(i, PointStart.y());
			}
		}
		else if (PointStart.x() > PointEnd.x())
		{
			for (int i = PointStart.x(); i >= PointEnd.x(); i -= 1)
			{
				MyPainter->drawPoint(i, PointStart.y());
			}
		}
	}
	else
	{
		double k = 1.0 * (1.0 * PointEnd.y() - 1.0 * PointStart.y()) / (1.0 * PointEnd.x() - 1.0 * PointStart.x());
		double x = double(PointStart.x());
		double y = double(PointStart.y());
		if (abs(k) <= 1.0)
		{
			for (int i = 0; i < abs(PointEnd.x() - PointStart.x()); i += 1)
			{
				if (PointStart.x() < PointEnd.x())
				{
					x += 1;
					y += k;
				}
				else
				{
					x -= 1;
					y -= k;
				}
				MyPainter->drawPoint(int(x), int(y + 0.5));
			}
		}
		else if (abs(k) > 1.0)
		{
			for (int i = 0; i < abs(PointEnd.y() - PointStart.y()); i += 1)
			{
				if (PointStart.y() < PointEnd.y())
				{
					x += 1.0 / k;
					y += 1;
				}
				else
				{
					x -= 1.0 / k;
					y -= 1;
				}
				MyPainter->drawPoint(int(x + 0.5), int(y));
			}
		}
	}
}

#endif // !_MYDDALINE2D_H_
