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


#include <QMouseEvent>
#include <QAction>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QTabWidget>
#include <QTimer>

#include "MyGUI1.h"
#include "MyAxisDialog2D.h"
#include "MyAxisDialog2D.h"
#include "MyOperatorDialog3D.h"
#include "MyDDALine2D.h"
#include "MyCut2D.h"
#include "MyFill2D.h"
#include "MyXPoint2D.h"
#include "MyXYPointLine2D.h"
#include "MySortPolyGons2D.h"
#include "MyVectorXVector2D.h"
#include "MyTrans2D.h"
#include "MyTrans3D.h"
#include "MyRot2D.h"
#include "MyRot3D.h"
#include "MyMirr2D.h"
#include "MyScale2D.h"
#include "MyPlane2D.h"
#include "My2DStretch3D.h"
#include "MyDrawPolyGons2D.h"
#include "MyDrawPolyGons3D.h"
#include "MyDrawBody3D.h"
#include "MyVector3D.h"
#include "MyAnimation3D.h"

MyGUI1::MyGUI1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.centralWidget->setMouseTracking(true); //鼠标追踪
	this->setMouseTracking(true); //鼠标追踪
	this->MyDrawType = -1;
	this->MyDrawFlage = 0;
	MyAnimationTimer3D = new QTimer(this);

	/******************** 文件栏 ********************/
	//新建
	//打开
	connect(MyGUI1::ui.ActionOpenFile, &QAction::triggered, 
		[=]() 
	{
		QString Path = QFileDialog::getOpenFileName(this, 
			"打开", "../", 
			"Source(*.cpp *.h);;"
			"Text(*.txt);;All(*.*))");
		qDebug() << Path;
	}
	);

	//保存
	//另存为
	//退出
	connect(MyGUI1::ui.ActionExit, &QAction::triggered, 
		[=]() 
	{
		this->close();
	}
	);

	/******************** 绘图2D栏 ********************/
	//绘图
	connect(MyGUI1::ui.ActionDraw2D, &QAction::triggered, 
		[=]() 
	{
		this->MyDrawType = 0;
		this->MyDrawFlage = 0;
		this->MyMouseTracking = false;
		this->MyPolyGonLine2D.MyLineStart = QPoint(0, 0);
		this->MyPolyGonLine2D.MyLineEnd = QPoint(0, 0);
		this->MyMouseFrom = QPoint(0, 0);
		this->MyMouseTo = QPoint(0, 0);
		this->MyDrawPlane2D.MyClearPolyGons();
		this->MyCutPlane2D.MyClearPolyGons();
		this->MySolid3D.MyClearSolid();
		this->update();
	}
	);

	//裁剪
	connect(MyGUI1::ui.ActionTailor2D, &QAction::triggered,
		[=]() mutable
		{
			this->MyDrawType = 1;
			this->MyDrawFlage = 0;
			this->MyMouseTracking = false;
			this->MyPolyGonLine2D.MyLineStart = QPoint(0, 0);
			this->MyPolyGonLine2D.MyLineEnd = QPoint(0, 0);
			this->MyMouseFrom = QPoint(0, 0);
			this->MyMouseTo = QPoint(0, 0);
			this->MyCutPlane2D.MyClearPolyGons();
			this->MySolid3D.MyClearSolid();
			this->update();
		}
	);

	//填充
	connect(MyGUI1::ui.ActionFill2D, &QAction::triggered,
		[=]() mutable
		{
			this->MyFillFlage2D = true;
			this->update();
		}
	);

	//颜色
	connect(MyGUI1::ui.ActionColor2D, &QAction::triggered,
		[=]() mutable
		{
			this->MyColor2D = QColorDialog::getColor(Qt::blue, this, "SetColor");
			this->MyColorFill2D = MyColor2D;
		}
	);

	//字体
	connect(MyGUI1::ui.ActionFont2D, &QAction::triggered,
		[=]() mutable
		{
			bool FontOk;
			this->MyFont2D = QFontDialog::getFont(&FontOk, QFont("宋体"), this, "字体设置");
		}
	);

	//编辑
	connect(MyGUI1::ui.ActionEdit2D, &QAction::triggered,
		[=]() mutable
		{
			this->MyAxisDlg2D.show();
		}
	);

	//坐标
	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyTabAxis2DSignal,
		[=]() mutable
		{
			this->update();
		}
	);

	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyAxisAddPoint2DSignal,
		[=](QPoint Point) mutable
		{
			switch (this->MyDrawType)
			{
			case 0: //图形绘制
			{
				this->MyMouseRightPressFalge = false;
				this->MyMouseTracking = false;
				this->MyFillFlage2D = false;

				if (this->MyDrawFlage == 0)
				{
					this->setCursor(Qt::CrossCursor);
					this->MyPolyGonLine2D.MyLineStart = Point;
					this->MyDrawFlage = 1;
				}
				else if (this->MyDrawFlage == 1)
				{
					this->MyPolyGonLine2D.MyLineEnd = Point;
					this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
					this->MyPolyGonLine2D.MyLineID = this->MyDrawPlane2D.MyPolyGonsID2D;
					this->MyDrawPlane2D.MyPolyGons2D[this->MyDrawPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
					this->MyDrawFlage = 2;
				}
				else if (this->MyDrawFlage == 2)
				{
					this->MyPolyGonLine2D.MyLineStart = this->MyPolyGonLine2D.MyLineEnd;
					this->MyPolyGonLine2D.MyLineEnd = Point;
					this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
					this->MyPolyGonLine2D.MyLineID = this->MyDrawPlane2D.MyPolyGonsID2D;
					this->MyDrawPlane2D.MyPolyGons2D[this->MyDrawPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
				}
				this->MyMouseFrom = Point;
				this->MyMouseTo = Point;

				this->update();
				break;
			}

			case 1: //裁剪绘制
			{
				this->MyMouseRightPressFalge = false;
				this->MyMouseTracking = false;
				this->MyFillFlage2D = false;

				if (this->MyDrawFlage == 0)
				{
					this->setCursor(Qt::CrossCursor);
					this->MyPolyGonLine2D.MyLineStart = Point;
					this->MyDrawFlage = 1;
				}
				else if (this->MyDrawFlage == 1)
				{
					this->MyPolyGonLine2D.MyLineEnd = Point;
					this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
					this->MyPolyGonLine2D.MyLineID = this->MyCutPlane2D.MyPolyGonsID2D;
					this->MyCutPlane2D.MyPolyGons2D[this->MyCutPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
					this->MyDrawFlage = 2;
				}
				else if (this->MyDrawFlage == 2)
				{
					this->MyPolyGonLine2D.MyLineStart = this->MyPolyGonLine2D.MyLineEnd;
					this->MyPolyGonLine2D.MyLineEnd = Point;
					this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
					this->MyPolyGonLine2D.MyLineID = this->MyCutPlane2D.MyPolyGonsID2D;
					this->MyCutPlane2D.MyPolyGons2D[this->MyCutPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
				}
				this->MyMouseFrom = Point;
				this->MyMouseTo = Point;

				this->update();
				break;
			}

			default:
				break;
			}
		}
	);

	//平移
	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyTabTrans2DSignal,
		[=]() mutable
		{
			this->MyDrawType = 2;
			this->MyDrawFlage = 0;
			this->MyMouseTracking = false;
			this->MyChangeMatPoint2D = QPoint(50, 50);
			this->update();
		}
	);

	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyAxisTrans2DSignal,
		[=](QPoint Point) mutable
		{
			this->MyChangeMatPoint2D = Point;
			this->MyDrawFlage = 2;
			if (this->MyDrawType == 2)
			{
				if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0 && this->MyDrawFlage == 2)
				{
					MyTrans2D(&this->MyDrawPlane2D, this->MyChangeMatPoint2D);
				}
			}
			this->update();
		}
	);

	//旋转
	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyTabRot2DSignal,
		[=]() mutable
		{
			this->MyDrawType = 3;
			this->MyMouseTracking = false;
			this->MyChangeMatAngle2D = 10;
			this->MyChangeMatPoint2D = QPoint(600, 600);
			this->update();
		}
	);

	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyAxisRot2DSignal,
		[=](QPoint Point, double Angle) mutable
		{
			this->MyChangeMatPoint2D = Point;
			this->MyChangeMatAngle2D = Angle;

			if (this->MyDrawType == 3)
			{
				if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0)
				{
					MyRot2D(&this->MyDrawPlane2D, MyChangeMatPoint2D, MyChangeMatAngle2D);
				}
			}
			this->update();
		}
	);

	//镜像
	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyTabMirr2DSignal,
		[=]() mutable
		{
			this->MyDrawType = 4;
			this->MyDrawFlage = 2;
			this->MyMouseTracking = false;
			this->MyChangeMatLine2D.MyLineStart = QPoint(100, 100);
			this->MyChangeMatLine2D.MyLineEnd = QPoint(500, 500);
			this->MyChangeMatLine2D.MyLineColor = this->MyColor2D;
			this->update();
		}
	);

	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyAxisMirr2DSignal,
		[=](MyLine2D Line) mutable
		{
			this->MyChangeMatLine2D = Line;
			this->MyChangeMatLine2D.MyLineColor = this->MyColor2D;

			if (this->MyDrawType == 4)
			{
				if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0 && this->MyDrawFlage == 2)
				{
					MyMirr2D(&this->MyDrawPlane2D, &this->MyChangeMatLine2D);
				}
			}
			this->update();
		}
	);

	//缩放
	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyTabScale2DSignal,
		[=]() mutable
		{
			this->MyDrawType = 5;
			this->MyMouseTracking = false;
			this->MyChangeMatScale2D = 1.1;
			this->MyChangeMatPoint2D = QPoint(600, 600);
			this->update();
		}
	);

	connect(&MyAxisDlg2D, &MyAxisDialog2D::MyAxisScale2DSignal,
		[=](QPoint Point, double Scale) mutable
		{
			this->MyChangeMatPoint2D = Point;
			this->MyChangeMatScale2D = Scale;

			if (this->MyDrawType == 5)
			{
				if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0)
				{
					MyScale2D(&this->MyDrawPlane2D, MyChangeMatPoint2D, MyChangeMatScale2D);
				}
				this->update();
			}
		}
	);

	/******************** 绘图3D栏 ********************/
	//编辑
	connect(MyGUI1::ui.ActionEdit3D, &QAction::triggered,
		[=]()
		{
			this->MyOperatorDlg3D.show();
		}
	);

	//重置
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorReset3DSignal,
		[=](bool MyReset) mutable
		{
			if (MyReset)
			{
				this->MySolid3D.MySolidStart3D.MyClearPolyGons();
				this->MySolid3D.MySolidEnd3D.MyClearPolyGons();
				My2DStretch3D(&this->MySolid3D);
			}
			this->update();
		}
	);

	//拉伸预处理
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyTabStretch3DSignal,
		[=]() mutable
		{
			this->update();
		}
	);
	//拉伸
	connect(&MyOperatorDlg3D,&MyOperatorDialog3D::MyOperatorStretch3DSignal, 
		[=](double MyLength) mutable
		{
			this->MyFillFlage2D = false;
			this->MySolid3D.MyClearSolid(); //实体清空
			this->MySolid3D.MyPlaneOriginal2D = this->MyDrawPlane2D;
			this->MySolid3D.MySolidLength3D = MyLength;
			My2DStretch3D(&this->MySolid3D);
			this->update();
		}
	);

	//旋转预处理
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyTabRot3DSignal,
		[=]() mutable
		{
			this->update();
		}
	);
	//旋转
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatotRot3DSignal, 
		[=](MyPoint3D Point, double AngleX, double AngleY, double AngleZ) mutable
		{
			MyRot3D(&this->MySolid3D, Point, AngleX, AngleY, AngleZ);
			this->update();
		}
	);

	//平移预处理
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyTabTrans3DSignal,
		[=]() mutable
		{
			this->update();
		}
	);
	//平移
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorTrans3DSignal, 
		[=](MyPoint3D Point) mutable
		{
			MyTrans3D(&this->MySolid3D, Point);
			this->update();
		}
	);

	//显示预处理
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyTabShow3DSignal, 
		[=]() mutable
		{
			this->update();
		}
	);
	//显示
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorShow3DSignal,
		[=](int flage) mutable
		{
			this->MyDrawBodyTypeFlage3D = flage;
			this->update();
		}
	);

	//渲染预处理
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyTabRend3DSignal, 
		[=]() mutable
		{
			this->update();
		}
	);
	//渲染
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorRend3DSignal,
		[=](QColor LightColor, MyVector3D LightPos, double LightEnvironment, double LightAttenuation, 
			double LightDiffuse, double LightMirror, double LightMirrorNs) mutable
		{
			this->MyRendLightColor3D = LightColor;
			this->MyRendLightPos3D = LightPos;
			this->MyRendLightEnvironment3D = LightEnvironment;
			this->MyRendLightAttenuation3D = LightAttenuation;
			this->MyRendLightDiffuse3D = LightDiffuse;
			this->MyRendLightMirror3D = LightMirror;
			this->MyRendLightMirrorNs3D = LightMirrorNs;

			this->update();
		}
	);

	//动画预处理
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyTabAnimation3DSignal, 
		[=]() mutable
		{
			this->MyDrawType = 6;
			this->MyDrawFlage = 3;
			this->MyMouseTracking = false;

			MyPoint3D point1, point2;
			point1.x = 0;
			point1.y = 0;
			point1.z = 0;
			point2.x = 0;
			point2.y = 0;
			point2.z = 0;
			for (int i = 0; i < this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].size(); i++)
			{
				point1.x = point1.x + 1.0 * this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].value(i).MyLineStart.x / this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].size();
				point1.y = point1.y + 1.0 * this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].value(i).MyLineStart.y / this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].size();
				point1.z = point1.z + 1.0 * this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].value(i).MyLineStart.z / this->MySolid3D.MySolidStart3D.MyPolyGons3D[0].size();
			}
			for (int i = 0; i < this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].size(); i++)
			{
				point2.x = point2.x + 1.0 * this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].value(i).MyLineStart.x / this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].size();
				point2.y = point2.y + 1.0 * this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].value(i).MyLineStart.y / this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].size();
				point2.z = point2.z + 1.0 * this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].value(i).MyLineStart.z / this->MySolid3D.MySolidEnd3D.MyPolyGons3D[0].size();
			}
			this->MyAnimationMass3D.x = (point1.x + point2.x) / 2;
			this->MyAnimationMass3D.y = (point1.y + point2.y) / 2;
			this->MyAnimationMass3D.z = (point1.z + point2.z) / 2;

//			qDebug() << this->MyAnimationMass3D.x << '\t' << this->MyAnimationMass3D.y << '\t' << this->MyAnimationMass3D.z << endl;

			this->update();
		}
	);
	//动画
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorDraw3DSignal,
		[=]() mutable
		{
			this->MyAnimationPath3D.MyPolyGonsNum3D = 1;
			this->MyAnimationPath3D.MyClearPolyGons();

			this->MyDrawType = 6;
			this->MyDrawFlage = 0;
			this->MyMouseTracking = false;
			this->MyMouseRightPressFalge = false;
			this->MyMouseFrom = QPoint(0, 0);
			this->MyMouseTo = QPoint(0, 0);

			this->MyPolyGonLine3D.MyLineStart.x = 0;
			this->MyPolyGonLine3D.MyLineStart.y = 0;
			this->MyPolyGonLine3D.MyLineStart.z = 0;
			this->MyPolyGonLine3D.MyLineEnd.x = 0;
			this->MyPolyGonLine3D.MyLineEnd.y = 0;
			this->MyPolyGonLine3D.MyLineEnd.z = 0;

			this->MyAnimationPathFlage3D = 0;
			this->MyAnimationNumFlage3D = 0;

			this->update();
		}
	);
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorRun3DSignal,
		[=]() mutable
		{
			if (this->MyAnimationTimer3D->isActive() == false)
			{
				this->MyAnimationTimer3D->start(30);
			}

			this->update();
		}
	);
	connect(&MyOperatorDlg3D, &MyOperatorDialog3D::MyOperatorStop3DSignal,
		[=]() mutable
		{
			if (this->MyAnimationTimer3D->isActive() == true)
			{
				this->MyAnimationTimer3D->stop();
			}

			this->update();
		}
	);
	connect(MyAnimationTimer3D, &QTimer::timeout, 
		[=]() mutable
		{
			this->MyAnimationNumFlage3D++;
			this->MyAnimationNum3D = qSqrt(qPow(this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.x - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.x, 2)
				+ qPow(this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.y - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.y, 2)
				+ qPow(this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.z - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.z, 2)) 
				/ this->MyAnimationLong3D;
			this->MyAnimationPos3D.x = this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.x
				+ 1.0 * (this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.x - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.x) * MyAnimationNumFlage3D / MyAnimationNum3D;
			this->MyAnimationPos3D.y = this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.y
				+ 1.0 * (this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.y - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.y) * MyAnimationNumFlage3D / MyAnimationNum3D;
			this->MyAnimationPos3D.z = this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.z
				+ 1.0 * (this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.z - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.z) * MyAnimationNumFlage3D / MyAnimationNum3D;
			
			this->MyAnimationDertaPos3D.x = 1.0 * (this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.x - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.x) / MyAnimationNum3D;
			this->MyAnimationDertaPos3D.y = 1.0 * (this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.y - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.y) / MyAnimationNum3D;
			this->MyAnimationDertaPos3D.z = 1.0 * (this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineEnd.z - this->MyAnimationPath3D.MyPolyGons3D[0].value(this->MyAnimationPathFlage3D).MyLineStart.z) / MyAnimationNum3D;

			this->MyAnimationDertaAngle3D.x = 5.0;
			this->MyAnimationDertaAngle3D.y = 5.0;
			this->MyAnimationDertaAngle3D.z = 5.0;

			MyAnimation3D(&this->MySolid3D, this->MyAnimationPos3D, this->MyAnimationDertaPos3D, this->MyAnimationDertaAngle3D);

			if (this->MyAnimationNumFlage3D >= this->MyAnimationNum3D)
			{
				this->MyAnimationNumFlage3D = 0;
				this->MyAnimationPathFlage3D++;
				if (this->MyAnimationPathFlage3D >= this->MyAnimationPath3D.MyPolyGons3D[0].size())
				{
					this->MyAnimationTimer3D->stop();
				}
			}

			this->update();
		}
	);
}

/******************** 鼠标点击事件 ********************/
void MyGUI1::mousePressEvent(QMouseEvent *ev)
{
	//鼠标左键点击
	if (ev->button() == Qt::LeftButton)
	{
		MyMousePressLeftButton(ev);
	}

	//鼠标右键点击
	else if (ev->button() == Qt::RightButton)
	{
		MyMousePressRightButton(ev);
	}
	//鼠标中键点击
	else if (ev->button() == Qt::MiddleButton)
	{
		MyMousePressMiddleButton(ev);
	}
}

//鼠标左键点击
void MyGUI1::MyMousePressLeftButton(QMouseEvent *ev)
{
	switch (this->MyDrawType)
	{
	case 0: //图形绘制
	{
		this->MyMouseRightPressFalge = false;
		this->MyMouseTracking = false;
		this->MyFillFlage2D = false;

		if (this->MyDrawFlage == 0)
		{
			this->setCursor(Qt::CrossCursor);
			this->MyPolyGonLine2D.MyLineStart = ev->pos();
			this->MyDrawFlage = 1;
		}
		else if (this->MyDrawFlage == 1)
		{
			this->MyPolyGonLine2D.MyLineEnd = ev->pos();
			this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
			this->MyPolyGonLine2D.MyLineID = this->MyDrawPlane2D.MyPolyGonsID2D;
			this->MyDrawPlane2D.MyPolyGons2D[this->MyDrawPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
			this->MyDrawFlage = 2;
		}
		else if (this->MyDrawFlage == 2)
		{
			this->MyPolyGonLine2D.MyLineStart = this->MyPolyGonLine2D.MyLineEnd;
			this->MyPolyGonLine2D.MyLineEnd = ev->pos();
			this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
			this->MyPolyGonLine2D.MyLineID = this->MyDrawPlane2D.MyPolyGonsID2D;
			this->MyDrawPlane2D.MyPolyGons2D[this->MyDrawPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
		}
		this->MyMouseFrom = ev->pos();
		this->MyMouseTo = ev->pos();

		this->update();
		break;
	}

	case 1: //裁剪绘制
	{
		this->MyMouseRightPressFalge = false;
		this->MyMouseTracking = false;
		this->MyFillFlage2D = false;

		if (this->MyDrawFlage == 0)
		{
			this->setCursor(Qt::CrossCursor);
			this->MyPolyGonLine2D.MyLineStart = ev->pos();
			this->MyDrawFlage = 1;
		}
		else if (this->MyDrawFlage == 1)
		{
			this->MyPolyGonLine2D.MyLineEnd = ev->pos();
			this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
			this->MyPolyGonLine2D.MyLineID = this->MyCutPlane2D.MyPolyGonsID2D;
			this->MyCutPlane2D.MyPolyGons2D[this->MyCutPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
			this->MyDrawFlage = 2;
		}
		else if (this->MyDrawFlage == 2)
		{
			this->MyPolyGonLine2D.MyLineStart = this->MyPolyGonLine2D.MyLineEnd;
			this->MyPolyGonLine2D.MyLineEnd = ev->pos();
			this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
			this->MyPolyGonLine2D.MyLineID = this->MyCutPlane2D.MyPolyGonsID2D;
			this->MyCutPlane2D.MyPolyGons2D[this->MyCutPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
		}
		this->MyMouseFrom = ev->pos();
		this->MyMouseTo = ev->pos();

		this->update();
		break;
	}

	case 2: //绘制平移起始终止点并计算增量
	{
		if (this->MyDrawFlage == 0)
		{
			MyMouseTracking = true;

			this->MyMouseFrom = ev->pos();
			this->MyMouseTo = ev->pos();

			this->MyChangeMatLine2D.MyLineStart = ev->pos();
			this->MyChangeMatLine2D.MyLineEnd = ev->pos();

			this->MyChangeMatPoint2D = ev->pos();
			this->MyDrawFlage = 1;
		}
		else if (this->MyDrawFlage == 1)
		{
			MyMouseTracking = false;

			this->MyChangeMatLine2D.MyLineEnd = ev->pos();
			this->MyChangeMatLine2D.MyLineColor = this->MyColor2D;

			this->MyChangeMatPoint2D.setX(ev->pos().x() - this->MyChangeMatPoint2D.x());
			this->MyChangeMatPoint2D.setY(ev->pos().y() - this->MyChangeMatPoint2D.y());
			this->MyDrawFlage = 2;
		}
		this->update();
		break;
	}

	case 3: //绘制旋转中心
	{
		this->MyChangeMatPoint2D = ev->pos();
		this->update();
		break;
	}

	case 4: //绘制镜像线
	{
		if (this->MyDrawFlage == 0)
		{
			MyMouseTracking = true;

			this->MyMouseFrom = ev->pos();
			this->MyMouseTo = ev->pos();

			this->MyChangeMatLine2D.MyLineStart = ev->pos();
			this->MyChangeMatLine2D.MyLineEnd = ev->pos();
			this->MyDrawFlage = 1;
		}
		else if (this->MyDrawFlage == 1)
		{
			MyMouseTracking = false;

			this->MyChangeMatLine2D.MyLineEnd = ev->pos();
			this->MyChangeMatLine2D.MyLineColor = this->MyColor2D;
			this->MyDrawFlage = 2;
		}
		this->update();
		break;
	}

	case 5: //绘制缩放中心
	{
		this->MyChangeMatPoint2D = ev->pos();
		this->update();
		break;
	}

	case 6: //绘制动画路径
	{
		this->MyMouseTracking = false;
		this->MyFillFlage2D = false;

		if (this->MyDrawFlage == 0)
		{
			this->MyMouseRightPressFalge = false;
			this->setCursor(Qt::CrossCursor);
			this->MyPolyGonLine3D.MyLineStart.x = this->MyAnimationMass3D.x;
			this->MyPolyGonLine3D.MyLineStart.y = this->MyAnimationMass3D.y;
			this->MyPolyGonLine3D.MyLineStart.z = this->MyAnimationMass3D.z;
			this->MyPolyGonLine3D.MyLineEnd.x = ev->pos().x();
			this->MyPolyGonLine3D.MyLineEnd.y = ev->pos().y();
			this->MyPolyGonLine3D.MyLineEnd.z = 0;
			this->MyPolyGonLine3D.MyLineColor = this->MyColor2D;
			this->MyAnimationPath3D.MyPolyGons3D[0].append(this->MyPolyGonLine3D);
			this->MyDrawFlage = 1;
		}
		else if (this->MyDrawFlage == 1)
		{
			this->MyMouseRightPressFalge = false;
			this->MyPolyGonLine3D.MyLineStart = this->MyPolyGonLine3D.MyLineEnd;
			this->MyPolyGonLine3D.MyLineEnd.x = ev->pos().x();
			this->MyPolyGonLine3D.MyLineEnd.y = ev->pos().y();
			this->MyPolyGonLine3D.MyLineEnd.z = 0;
			this->MyPolyGonLine3D.MyLineColor = this->MyColor2D;
			this->MyAnimationPath3D.MyPolyGons3D[0].append(this->MyPolyGonLine3D);
			this->MyDrawFlage = 2;
		}
		else if (this->MyDrawFlage == 2)
		{
			this->MyMouseRightPressFalge = false;
			this->MyPolyGonLine3D.MyLineStart = this->MyPolyGonLine3D.MyLineEnd;
			this->MyPolyGonLine3D.MyLineEnd.x = ev->pos().x();
			this->MyPolyGonLine3D.MyLineEnd.y = ev->pos().y();
			this->MyPolyGonLine3D.MyLineEnd.z = 0;
			this->MyPolyGonLine3D.MyLineColor = this->MyColor2D;
			this->MyAnimationPath3D.MyPolyGons3D[0].append(this->MyPolyGonLine3D);
		}
		this->MyMouseFrom = ev->pos();
		this->MyMouseTo = ev->pos();

		this->update();
		break;
	}

	default:
		break;
	}
}

//鼠标右键点击
void MyGUI1::MyMousePressRightButton(QMouseEvent *ev)
{
	switch (this->MyDrawType)
	{
	case 0:
	{
		if (this->MyDrawPlane2D.MyPolyGons2D[0].size() == 0)
		{

		}
		else
		{
			if (!MyMouseRightPressFalge)
			{
				this->MyPolyGonLine2D.MyLineStart = this->MyPolyGonLine2D.MyLineEnd;
				this->MyPolyGonLine2D.MyLineEnd = this->MyDrawPlane2D.MyPolyGons2D[this->MyDrawPlane2D.MyPolyGonsNum2D].value(0).MyLineStart;
				this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
				this->MyPolyGonLine2D.MyLineID = this->MyDrawPlane2D.MyPolyGonsID2D;
				this->MyDrawPlane2D.MyPolyGons2D[this->MyDrawPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
				this->MyDrawPlane2D.MyPolyGonsColor2D.append(this->MyColor2D);

				this->MyDrawPlane2D.MyPolyGonsID2D += 1;
				this->MyDrawPlane2D.MyPolyGonsNum2D += 1;
				this->MyDrawFlage = 0;
			}
			this->MyMouseRightPressFalge = true;
			this->MyMouseTracking = false;
			this->MyFillFlage2D = false;
		}
		this->update();
		break;
	}
	case 1:
	{
		this->MyPolyGonLine2D.MyLineStart = this->MyPolyGonLine2D.MyLineEnd;
		this->MyPolyGonLine2D.MyLineEnd = this->MyCutPlane2D.MyPolyGons2D[this->MyCutPlane2D.MyPolyGonsNum2D].value(0).MyLineStart;
		this->MyPolyGonLine2D.MyLineColor = this->MyColor2D;
		this->MyPolyGonLine2D.MyLineID = this->MyCutPlane2D.MyPolyGonsID2D;
		this->MyCutPlane2D.MyPolyGons2D[this->MyCutPlane2D.MyPolyGonsNum2D].append(this->MyPolyGonLine2D);
		this->MyCutPlane2D.MyPolyGonsColor2D.append(this->MyColor2D);
		this->MyCutPlane2D.MyPolyGonsID2D += 1;
		this->MyCutPlane2D.MyPolyGonsNum2D += 1;

		if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0 && this->MyDrawFlage == 2)
		{
			MyCut2D(&this->MyDrawPlane2D, &this->MyCutPlane2D, &this->MyColor2D); //裁剪图形
			this->MyCutPlane2D.MyClearPolyGons();
		}
		this->MyDrawFlage = 0;
		this->MyMouseRightPressFalge = true;
		this->MyMouseTracking = false;
		this->MyFillFlage2D = false;

		this->update();
		break;
	}

	case 2:
	{
		if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0 && this->MyDrawFlage == 2)
		{
			MyTrans2D(&this->MyDrawPlane2D, this->MyChangeMatPoint2D);
			this->MyDrawFlage = 0;
		}

		this->update();
		break;
	}

	case 3:
	{
		if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0)
		{
			MyRot2D(&this->MyDrawPlane2D, MyChangeMatPoint2D, MyChangeMatAngle2D);
		}

		this->update();
		break;
	}

	case 4:
	{
		if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0 && this->MyDrawFlage == 2)
		{
			MyMirr2D(&this->MyDrawPlane2D, &this->MyChangeMatLine2D);
			this->MyDrawFlage = 0;
		}

		this->update();
		break;
	}

	case 5:
	{
		if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0)
		{
			MyScale2D(&this->MyDrawPlane2D, MyChangeMatPoint2D, MyChangeMatScale2D);
		}

		this->update();
		break;
	}

	case 6:
	{
		this->MyDrawFlage = 3;
		this->MyMouseTracking = false;
		this->MyMouseRightPressFalge = true;
		this->update();
		break;
	}

	default:
		break;
	}
}

//鼠标中键点击
void MyGUI1::MyMousePressMiddleButton(QMouseEvent *ev)
{

}

/******************** 鼠标释放事件 ********************/
void MyGUI1::mouseReleaseEvent(QMouseEvent *ev)
{
	//鼠标左键释放
	if (ev->button() == Qt::LeftButton)
	{
		MyMouseReleaseLeftButton(ev);
	}

	//鼠标右键释放
	else if (ev->button() == Qt::RightButton)
	{
		MyMouseReleaseRightButton(ev);
	}

	//鼠标中键释放
	else if (ev->button()==Qt::MiddleButton)
	{
		MyMouseReleaseMiddleButton(ev);
	}

}

//鼠标左键释放
void MyGUI1::MyMouseReleaseLeftButton(QMouseEvent *ev)
{
	switch (this->MyDrawType)
	{
	case 0:
	{
		MyMouseTracking = true;
		break;
	}

	case 1:
	{
		MyMouseTracking = true;
		break;
	}

	case 6:
	{
		if (this->MyMouseRightPressFalge == false)
		{
			MyMouseTracking = true;
		}
		
		break;
	}

	default:
		break;
	}
}

//鼠标右键释放
void MyGUI1::MyMouseReleaseRightButton(QMouseEvent *ev)
{

}

//鼠标中键释放
void MyGUI1::MyMouseReleaseMiddleButton(QMouseEvent *ev)
{

}

/******************** 鼠标移动事件 ********************/
void MyGUI1::mouseMoveEvent(QMouseEvent *ev)
{
	QString labelxy;
	labelxy = QString("(%1,%2)").arg(ev->pos().x()).arg(ev->pos().y());
	ui.statusBar->addWidget(ui.MyLabelMouse);
	ui.statusBar->addWidget(ui.MyLabelMouseXY);
	ui.MyLabelMouseXY->setText(labelxy);

	//QString strx = QString::number(ev->pos().x());
	//QString stry = QString::number(ev->pos().y());

	this->MyMouseTo = ev->pos();
	this->update();
}

/******************** 绘图事件 ********************/
void MyGUI1::paintEvent(QPaintEvent *)
{
	QPainter MyPainter2D(this);
	QPen MyPen2D;

	if (this->MySolid3D.MyPlaneOriginal2D.MyPolyGonsNum2D <= 0)
	{
		if (this->MyDrawPlane2D.MyPolyGons2D[0].size() > 0) //显示绘制图形
		{
			MyDrawPolyGons2D(&MyPen2D, &MyPainter2D, &this->MyDrawPlane2D);
		}
	}
	else
	{
		if (this->MySolid3D.MyPlaneOriginal2D.MyPolyGonsNum2D > 0) //显示三维实体
		{
			MyDrawBody3D(&MyPen2D, &MyPainter2D, &this->MySolid3D, this->MyDrawBodyTypeFlage3D, 
				this->MyRendLightColor3D, this->MyRendLightPos3D, this->MyRendLightEnvironment3D,
				this->MyRendLightAttenuation3D, this->MyRendLightDiffuse3D,
				this->MyRendLightMirror3D, this->MyRendLightMirrorNs3D);
		}
	}
	
	if (this->MyCutPlane2D.MyPolyGons2D[0].size() > 0) //显示裁剪图形
	{
		for (int i = 0; i <= this->MyCutPlane2D.MyPolyGonsNum2D; i++)
		{
			for (int j = 0; j < this->MyCutPlane2D.MyPolyGons2D[i].size(); j++)
			{
				MyDrawPolyGons2D(&MyPen2D, &MyPainter2D, &this->MyCutPlane2D);
			}
		}
	}
	
	if (this->MyDrawType == 2) //显示平移线
	{
		MyPen2D.setColor(this->MyChangeMatLine2D.MyLineColor);
		MyPainter2D.setPen(MyPen2D);
		MyDDALine2D(&MyPainter2D, this->MyChangeMatLine2D.MyLineStart, this->MyChangeMatLine2D.MyLineEnd);
	}

	if (this->MyDrawType == 3) //显示旋转中心点
	{
		MyPen2D.setColor(this->MyColor2D);
		MyPen2D.setWidth(3);
		MyPainter2D.setPen(MyPen2D);
		MyPainter2D.drawPoint(this->MyChangeMatPoint2D);
	}
	
	if (this->MyDrawType == 4) //显示镜像线
	{
		MyPen2D.setColor(this->MyChangeMatLine2D.MyLineColor);
		MyPainter2D.setPen(MyPen2D);
		MyDDALine2D(&MyPainter2D, this->MyChangeMatLine2D.MyLineStart, this->MyChangeMatLine2D.MyLineEnd);
	}
	
	if (this->MyDrawType == 5) //显示缩放中心点
	{
		MyPen2D.setColor(this->MyColor2D);
		MyPen2D.setWidth(3);
		MyPainter2D.setPen(MyPen2D);
		MyPainter2D.drawPoint(this->MyChangeMatPoint2D);
	}

	if (this->MyDrawType == 6) //绘制动画路径
	{
		if (this->MyAnimationPath3D.MyPolyGons3D[0].size() > 0)
		{
			MyPen2D.setColor(this->MyColor2D);
			MyPainter2D.setPen(MyPen2D);

			for (int i = 0; i < this->MyAnimationPath3D.MyPolyGons3D[0].size(); i++)
			{
				MyDrawPolyGons3D(&MyPen2D, &MyPainter2D, &this->MyAnimationPath3D);
			}
		}
	}
	
	MyPen2D.setColor(this->MyColor2D); //橡皮筋
	MyPainter2D.setPen(MyPen2D);
	if (this->MyMouseTracking)
	{
		switch (this->MyDrawType)
		{
		case 0: //绘图
		{
			MyDDALine2D(&MyPainter2D, this->MyMouseFrom, this->MyMouseTo);
			break;
		}

		case 1: //裁剪
		{
			MyDDALine2D(&MyPainter2D, this->MyMouseFrom, this->MyMouseTo);
			break;
		}

		case 2:  //平移线
		{
			MyDDALine2D(&MyPainter2D, this->MyMouseFrom, this->MyMouseTo);
			break;
		}

		case 4:  //镜像线
		{
			MyDDALine2D(&MyPainter2D, this->MyMouseFrom, this->MyMouseTo);
			break;
		}

		case 6:  //动画路径
		{
			MyDDALine2D(&MyPainter2D, this->MyMouseFrom, this->MyMouseTo);
			break;
		}

		default:
			break;
		}
	}
	
	if (this->MyFillFlage2D) //填充图形
	{
		if (this->MyDrawPlane2D.MyPolyGonsNum2D > 0)
		{
			MyPen2D.setColor(this->MyColor2D);
			MyPainter2D.setPen(MyPen2D);
			MyFill2D(&MyPainter2D, &this->MyDrawPlane2D);
		}
	}
}
