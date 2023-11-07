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


#ifndef _MYDRAWBODY3D_H_
#define _MYDRAWBODY3D_H_

#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QPoint>
#include <QColor>

#include "MyLine2D.h"
#include "MyFill2D.h"
#include "MyDDALine2D.h"
#include "MyPoint3D.h"
#include "MyPlane3D.h"
#include "MyStretchSolid3D.h"
#include "MyVectorXVectorInZ3D.h"
#include "MyRend3D.h"

void MyDrawBody3D(QPen* pen, QPainter* painter, MyStretchSolid3D* Body3D, int falge, 
	QColor LightColor, MyVector3D LightPos, double LightEnvironment, double LightAttenuation,
	double LightDiffuse, double LightMirror, double LightMirrorNs)
{
	QPoint point1_1, point1_2, point2_1, point2_2;
	MyPoint3D pointA, pointB, pointC;
	double value;
    int showflage = 0; //1:起始面可见; 0:终止面可见; -1:上下两个面都不可见;
	int linewidth = 2;
	int linewidthRend = 1;
	QColor MyRendColor;
	MyPlane2D Plane;
	MyLine2D Line;
    MyLine3D line3d;

	switch (falge)
	{
	case 0: //绘制线框
	{
		for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
		{
			for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
			{
				point1_1 = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
				point1_2 = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();
				point2_1 = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
				point2_2 = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();

				pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
				pen->setWidth(linewidth);
				painter->setPen(*pen);

				painter->drawLine(point1_1, point1_2);
				painter->drawLine(point2_1, point2_2);
				painter->drawLine(point1_1, point2_1);
			}
		}

		break;
	}

	case 1: //绘制消隐
	{
		pointA = Body3D->MySolidStart3D.MyPolyGons3D[0].value(0).MyLineStart;
		pointB = Body3D->MySolidStart3D.MyPolyGons3D[0].value(0).MyLineEnd;
		pointC = Body3D->MySolidStart3D.MyPolyGons3D[0].value(1).MyLineEnd;

		value = MyVectorXVectorInZ3D(pointA, pointB, pointC);

		if (value > 0)
		{
			if (Body3D->MySolidLength3D > 0)
			{
				showflage = 1;
			}
			else
			{
				showflage = 0;
			}
		}
		else if (value == 0)
		{
			showflage = -1;
		}
		else if (value < 0)
		{
			if (Body3D->MySolidLength3D < 0)
			{
				showflage = 1;
			}
			else
			{
				showflage = 0;
			}
		}

		if (showflage == 1)
		{
			for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
			{
				for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
				{
					pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
					pen->setWidth(linewidth);
					painter->setPen(*pen);
                    line3d = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j);
                    MyDDALine2D(painter, line3d);
				}
			}
		}
		else if (showflage == 0)
		{
			for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
			{
				for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
				{
					pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
					pen->setWidth(linewidth);
					painter->setPen(*pen);
                    line3d = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j);
                    MyDDALine2D(painter, line3d);
				}
			}
		}

		for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
		{
			for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
			{
				pointA = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart;
				pointB = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd;
				pointC = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd;

				if (Body3D->MySolidLength3D > 0)
				{
					value = MyVectorXVectorInZ3D(pointA, pointB, pointC);
				}
				else if (Body3D->MySolidLength3D < 0)
				{

					value = MyVectorXVectorInZ3D(pointC, pointB, pointA);
				}
				
				if (value < 0)
				{
					point1_1 = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
					point1_2 = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();
					point2_1 = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
					point2_2 = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();

					pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
					pen->setWidth(linewidth);
					painter->setPen(*pen);

					painter->drawLine(point1_1, point1_2);
					painter->drawLine(point2_1, point2_2);
					painter->drawLine(point1_1, point2_1);
					painter->drawLine(point1_2, point2_2);
				}
			}
		}

		break;
	}

	case 2: //渲染
	{
		pointA = Body3D->MySolidStart3D.MyPolyGons3D[0].value(0).MyLineStart;
		pointB = Body3D->MySolidStart3D.MyPolyGons3D[0].value(0).MyLineEnd;
		pointC = Body3D->MySolidStart3D.MyPolyGons3D[0].value(1).MyLineEnd;

		value = MyVectorXVectorInZ3D(pointA, pointB, pointC);

		if (value > 0)
		{
			if (Body3D->MySolidLength3D > 0)
			{
				showflage = 1;
			}
			else
			{
				showflage = 0;
			}
		}
		else if (value == 0)
		{
			showflage = -1;
		}
		else if (value < 0)
		{
			if (Body3D->MySolidLength3D < 0)
			{
				showflage = 1;
			}
			else
			{
				showflage = 0;
			}
		}
		
		if (showflage == 1)
		{
			for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
			{
				//绘制起始面边框
				//for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
				//{
				//	pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
				//	pen->setWidth(linewidth);
				//	painter->setPen(*pen);
				//	MyDDALine2D(painter, Body3D->MySolidStart3D.MyPolyGons3D[i].value(j));
				//}

				//填充起始面图形
				Plane.MyClearPolyGons();
				Plane.MyPolyGonsNum2D = Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D;

				for (int j = 0; j < Body3D->MySolidStart3D.MyPolyGons3D[i].size(); j++)
				{
					Line.MyLineStart = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
					Line.MyLineEnd = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();

					Plane.MyPolyGons2D[i].append(Line);
				}

				if (Body3D->MySolidLength3D > 0)
				{
					MyRendColor = MyRend3D(Body3D->MySolidStart3D.MyPolyGons3D[i].value(1).MyLineEnd,
						Body3D->MySolidStart3D.MyPolyGons3D[i].value(0).MyLineEnd,
						Body3D->MySolidStart3D.MyPolyGons3D[i].value(0).MyLineStart,
						LightColor, LightPos, LightEnvironment, LightAttenuation,
						LightDiffuse, LightMirror, LightMirrorNs);
				}
				else if (Body3D->MySolidLength3D < 0)
				{
					MyRendColor = MyRend3D(Body3D->MySolidStart3D.MyPolyGons3D[i].value(0).MyLineStart,
						Body3D->MySolidStart3D.MyPolyGons3D[i].value(0).MyLineEnd,
						Body3D->MySolidStart3D.MyPolyGons3D[i].value(1).MyLineEnd,
						LightColor, LightPos, LightEnvironment, LightAttenuation,
						LightDiffuse, LightMirror, LightMirrorNs);
				}
				
				pen->setColor(MyRendColor);
				pen->setWidth(linewidthRend);
				painter->setPen(*pen);
				MyFill2D(painter, &Plane);
			}
		}
		else if (showflage == 0)
		{
			for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
			{
				//绘制终止面边框
				//for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
				//{
				//	pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
				//	pen->setWidth(linewidth);
				//	painter->setPen(*pen);
				//	MyDDALine2D(painter, Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j));
				//}

				//填充终止面图形
				Plane.MyClearPolyGons();
				Plane.MyPolyGonsNum2D = Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D;

				for (int j = 0; j < Body3D->MySolidEnd3D.MyPolyGons3D[i].size(); j++)
				{
					Line.MyLineStart = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
					Line.MyLineEnd = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();

					Plane.MyPolyGons2D[i].append(Line);
				}

				if (Body3D->MySolidLength3D > 0)
				{
					MyRendColor = MyRend3D(Body3D->MySolidEnd3D.MyPolyGons3D[i].value(0).MyLineStart,
						Body3D->MySolidEnd3D.MyPolyGons3D[i].value(0).MyLineEnd,
						Body3D->MySolidEnd3D.MyPolyGons3D[i].value(1).MyLineEnd,
						LightColor, LightPos, LightEnvironment, LightAttenuation,
						LightDiffuse, LightMirror, LightMirrorNs);
				}
				else if (Body3D->MySolidLength3D < 0)
				{
					MyRendColor = MyRend3D(Body3D->MySolidEnd3D.MyPolyGons3D[i].value(1).MyLineEnd,
						Body3D->MySolidEnd3D.MyPolyGons3D[i].value(0).MyLineEnd,
						Body3D->MySolidEnd3D.MyPolyGons3D[i].value(0).MyLineStart,
						LightColor, LightPos, LightEnvironment, LightAttenuation,
						LightDiffuse, LightMirror, LightMirrorNs);
				}

				pen->setColor(MyRendColor);
				pen->setWidth(linewidthRend);
				painter->setPen(*pen);
				MyFill2D(painter, &Plane);
			}
		}

		for (int i = 0; i < Body3D->MyPlaneOriginal2D.MyPolyGonsNum2D; i++)
		{
			for (int j = 0; j < Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].size(); j++)
			{
				pointA = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart;
				pointB = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd;
				pointC = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd;

				if (Body3D->MySolidLength3D > 0)
				{
					value = MyVectorXVectorInZ3D(pointA, pointB, pointC);
				}
				else if (Body3D->MySolidLength3D < 0)
				{
					value = MyVectorXVectorInZ3D(pointC, pointB, pointA);
				}

				if (value < 0)
				{
					point1_1 = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
					point1_2 = Body3D->MySolidStart3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();
					point2_1 = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineStart.To2DPoint();
					point2_2 = Body3D->MySolidEnd3D.MyPolyGons3D[i].value(j).MyLineEnd.To2DPoint();

					//绘制侧面边框
					//pen->setColor(Body3D->MyPlaneOriginal2D.MyPolyGons2D[i].value(j).MyLineColor);
					//pen->setWidth(linewidth);
					//painter->setPen(*pen);

					//painter->drawLine(point1_1, point1_2);
					//painter->drawLine(point2_1, point2_2);
					//painter->drawLine(point1_1, point2_1);
					//painter->drawLine(point1_2, point2_2);

					//填充侧面图形
					Plane.MyClearPolyGons();
					Plane.MyPolyGonsNum2D = 1;

					Line.MyLineStart = point1_1;
					Line.MyLineEnd = point1_2;
					Plane.MyPolyGons2D[0].append(Line);
					Line.MyLineStart = point1_2;
					Line.MyLineEnd = point2_2;
					Plane.MyPolyGons2D[0].append(Line);
					Line.MyLineStart = point2_2;
					Line.MyLineEnd = point2_1;
					Plane.MyPolyGons2D[0].append(Line);
					Line.MyLineStart = point2_1;
					Line.MyLineEnd = point1_1;
					Plane.MyPolyGons2D[0].append(Line);

					if (Body3D->MySolidLength3D > 0)
					{
						MyRendColor = MyRend3D(pointA, pointB, pointC,
							LightColor, LightPos, LightEnvironment, 
							LightAttenuation, LightDiffuse, LightMirror, LightMirrorNs);
					}
					else if (Body3D->MySolidLength3D < 0)
					{
						MyRendColor = MyRend3D(pointC, pointB, pointA,
							LightColor, LightPos, LightEnvironment, 
							LightAttenuation, LightDiffuse, LightMirror, LightMirrorNs);
					}

					pen->setColor(MyRendColor);
					pen->setWidth(linewidthRend);
					painter->setPen(*pen);
					MyFill2D(painter, &Plane);
				}
			}
		}

		break;
	}

	default:
		break;
	}
}

#endif // !_MYDRAWBODY3D_H_
