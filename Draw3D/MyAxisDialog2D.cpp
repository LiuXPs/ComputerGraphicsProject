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


#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QTabWidget>
#include <QFocusFrame>

#include "ui_MyAxisDialog2D.h"
#include "MyAxisDialog2D.h"
#include "MyGUI1.h"

MyAxisDialog2D::MyAxisDialog2D(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyAxisDialog2D)
{
    ui->setupUi(this);

	connect(ui->MyTabWidget2D, &QTabWidget::currentChanged, 
		[=]() mutable
		{
			switch (ui->MyTabWidget2D->currentIndex())
			{
			case 0:
			{
				emit MyTabAxis2DSignal();
				break;
			}

			case 1:
			{
				emit MyTabTrans2DSignal();
				break;
			}

			case 2:
			{
				emit MyTabRot2DSignal();
				break;
			}

			case 3:
			{
				emit MyTabMirr2DSignal();
				break;
			}

			case 4:
			{
				emit MyTabScale2DSignal();
				break;
			}

			default:
				break;
			}
		}
	);

	//坐标
	connect(ui->MyAxisAddPointPushButton2D, &QPushButton::clicked,
		[=]() mutable
		{
			this->MyAxisDlgAddPoint2D.setX((ui->MyDrawAxisEditX2D->text()).toInt());
			this->MyAxisDlgAddPoint2D.setY((ui->MyDrawAxisEditY2D->text()).toInt());
			emit MyAxisAddPoint2DSignal(this->MyAxisDlgAddPoint2D);
		}
	);

	//平移
	connect(ui->MyTransPushButton2D, &QPushButton::clicked, 
		[=]() mutable
		{
			this->MyAxisDlgTransPoint2D.setX((ui->MyTransTXEdit2D->text()).toInt());
			this->MyAxisDlgTransPoint2D.setY((ui->MyTransTYEdit2D->text()).toInt());
			emit MyAxisTrans2DSignal(this->MyAxisDlgTransPoint2D);
		}
	);

	//旋转
	connect(ui->MyRotPushButton2D, &QPushButton::clicked, 
		[=]() mutable
		{
			this->MyAxisDlgRotPoint2D.setX((ui->MyRotRXEdit2D->text()).toInt());
			this->MyAxisDlgRotPoint2D.setY((ui->MyRotRYEdit2D->text()).toInt());
			this->MyAxisDlgAngle2D = (ui->MyRotDoubleSpinBox2D->text()).toDouble();
			emit MyAxisRot2DSignal(this->MyAxisDlgRotPoint2D, this->MyAxisDlgAngle2D);
		}
	);

	//镜像
	connect(ui->MyMirrPushButton2D, &QPushButton::clicked, 
		[=]() mutable
		{
			this->MyAxisDlgMirrLine2D.MyLineStart.setX((ui->MyMirrMXStartEdit2D->text()).toInt());
			this->MyAxisDlgMirrLine2D.MyLineStart.setY((ui->MyMirrMYStartEdit2D->text()).toInt());
			this->MyAxisDlgMirrLine2D.MyLineEnd.setX((ui->MyMirrMXEndEdit2D->text()).toInt());
			this->MyAxisDlgMirrLine2D.MyLineEnd.setY((ui->MyMirrMYEndEdit2D->text()).toInt());
			emit MyAxisMirr2DSignal(this->MyAxisDlgMirrLine2D);
		}
	);

	//缩放
	connect(ui->MyScalePushButton2D, &QPushButton::clicked,
		[=]() mutable
		{
			this->MyAxisDlgScalePoint2D.setX((ui->MyScaleSXEdit2D->text()).toInt());
			this->MyAxisDlgScalePoint2D.setY((ui->MyScaleSYEdit2D->text()).toInt());
			this->MyAxisDlgScale2D = (ui->MyScaleDoubleSpinBox2D->text()).toDouble();
			emit MyAxisScale2DSignal(this->MyAxisDlgScalePoint2D, this->MyAxisDlgScale2D);
		}
	);
}

MyAxisDialog2D::~MyAxisDialog2D()
{
    delete ui;
}
