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


#ifndef _MYGUI1_H_
#define _MYGUI1_H_

#include <QtWidgets/QMainWindow>
#include <QPoint>
#include <QList>
#include <QColor>
#include <QFont>
#include <QTimer>

#include "ui_MyGUI1.h"
#include "MyAxisDialog2D.h"
#include "MyOperatorDialog3D.h"
#include "MyPoint3D.h"
#include "MyLine2D.h"
#include "MyPlane2D.h"
#include "MyPlane3D.h"
#include "MyStretchSolid3D.h"
#include "MyVector3D.h"

class MyGUI1 : public QMainWindow
{
	Q_OBJECT

public:
	MyGUI1(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyGUI1Class ui;

	//变量定义
public:
	//变量初始化
	MyPlane2D MyDrawPlane2D; //绘制多边形
	MyPlane2D MyCutPlane2D; //裁剪多边形
	MyStretchSolid3D MySolid3D; //三维拉伸实体

	QPoint MyChangeMatPoint2D; //平移增量点;旋转中心点;缩放中心点
	double MyChangeMatAngle2D; //变换矩阵旋转角度
	double MyChangeMatScale2D; //变换矩阵缩放因子
	MyLine2D MyChangeMatLine2D; //镜像线

	MyPoint3D MyChangeMatPoint3D; //平移增量点;旋转中心点
	double MyChangeMatAngleX3D; //绕X轴旋转角度
	double MyChangeMatAngleY3D; //绕Y轴旋转角度
	double MyChangeMatAngleZ3D; //绕Z轴旋转角度
	int MyDrawBodyTypeFlage3D; //绘制类型

	int MyChangeMatFlage2D; //变换矩阵操作标志
	int MyDrawFlage = 0; //绘制动作标志
	int MyDrawType = -1; //绘图事件标志 0:绘图;1:裁剪;2:平移
	MyLine2D MyPolyGonLine2D; //绘制线段变量

	QColor MyRendLightColor3D; //光源颜色
	MyVector3D MyRendLightPos3D; //光源位矢
	double MyRendLightEnvironment3D; //环境光光强
	double MyRendLightAttenuation3D; //光强衰减因子
	double MyRendLightDiffuse3D; //漫反射系数
	double MyRendLightMirror3D; //镜面反射系数
	double MyRendLightMirrorNs3D; //镜面反射指数

	MyLine3D MyPolyGonLine3D; //动画路径变量
	MyPlane3D MyAnimationPath3D; //动画路径
	QTimer* MyAnimationTimer3D; //动画定时器
	MyPoint3D MyAnimationMass3D; //物体中心
	MyPoint3D MyAnimationPos3D; //物体中心位置
	MyPoint3D MyAnimationDertaPos3D; //物体平移增量
	MyPoint3D MyAnimationDertaAngle3D; //物体旋转增量
	int MyAnimationPathFlage3D; //动画段数计数
	int MyAnimationNumFlage3D; //段数分割计数
	int MyAnimationLong3D = 10; //每段的像素数量
	int MyAnimationNum3D; //每段轨迹的分割数量
	int MyAnimationPathNum3D; //轨迹的段数
	

	QColor MyColor2D = Qt::blue; //线段颜色
	QColor MyColorFill2D = Qt::blue; //填充颜色
	MyAxisDialog2D MyAxisDlg2D; //坐标对话框
	MyOperatorDialog3D MyOperatorDlg3D; //操作对话框
	QFont MyFont2D; //字体

	QPoint MyMouseFrom, MyMouseTo; //橡皮筋首末点
	bool MyMouseTracking = false; //鼠标橡皮筋标志

	bool MyFillFlage2D = false; //填充标志
	bool MyMouseRightPressFalge; //鼠标右键点击标志

	//事件定义
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void paintEvent(QPaintEvent *);

	void MyMousePressLeftButton(QMouseEvent *ev);
	void MyMousePressRightButton(QMouseEvent *ev);
	void MyMousePressMiddleButton(QMouseEvent *ev);
	void MyMouseReleaseLeftButton(QMouseEvent *ev);
	void MyMouseReleaseRightButton(QMouseEvent *ev);
	void MyMouseReleaseMiddleButton(QMouseEvent *ev);
};

#endif // !_MYGUI1_H_