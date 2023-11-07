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


#include <QtDebug>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QColorDialog>

#include "ui_MyOperatorDialog3D.h"
#include "MyOperatorDialog3D.h"

MyOperatorDialog3D::MyOperatorDialog3D(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyOperatorDialog3D)
{
    ui->setupUi(this);
	this->MyLightColor3D = QColor(Qt::green);
	ui->MyLightPosXDoubleSpinBox3D->setValue(1.0 * (ui->MyLightPosXSlider3D->value() - ui->MyLightPosXSlider3D->minimum()) / (ui->MyLightPosXSlider3D->maximum() - ui->MyLightPosXSlider3D->minimum()) * (ui->MyLightPosXDoubleSpinBox3D->maximum() - ui->MyLightPosXDoubleSpinBox3D->minimum()) + ui->MyLightPosXDoubleSpinBox3D->minimum());
	ui->MyLightPosYDoubleSpinBox3D->setValue(1.0 * (ui->MyLightPosYSlider3D->value() - ui->MyLightPosYSlider3D->minimum()) / (ui->MyLightPosYSlider3D->maximum() - ui->MyLightPosYSlider3D->minimum()) * (ui->MyLightPosYDoubleSpinBox3D->maximum() - ui->MyLightPosYDoubleSpinBox3D->minimum()) + ui->MyLightPosYDoubleSpinBox3D->minimum());
	ui->MyLightPosZDoubleSpinBox3D->setValue(1.0 * (ui->MyLightPosZSlider3D->value() - ui->MyLightPosZSlider3D->minimum()) / (ui->MyLightPosZSlider3D->maximum() - ui->MyLightPosZSlider3D->minimum()) * (ui->MyLightPosZDoubleSpinBox3D->maximum() - ui->MyLightPosZDoubleSpinBox3D->minimum()) + ui->MyLightPosZDoubleSpinBox3D->minimum());
	ui->MyLightEnvironmentDoubleSpinBox3D->setValue(1.0 * (ui->MyLightEnvironmentSlider3D->value() - ui->MyLightEnvironmentSlider3D->minimum()) / (ui->MyLightEnvironmentSlider3D->maximum() - ui->MyLightEnvironmentSlider3D->minimum()) * (ui->MyLightEnvironmentDoubleSpinBox3D->maximum() - ui->MyLightEnvironmentDoubleSpinBox3D->minimum()) + ui->MyLightEnvironmentDoubleSpinBox3D->minimum());
	ui->MyLightAttenuationDoubleSpinBox3D->setValue(1.0 * (ui->MyLightAttenuationSlider3D->value() - ui->MyLightAttenuationSlider3D->minimum()) / (ui->MyLightAttenuationSlider3D->maximum() - ui->MyLightAttenuationSlider3D->minimum()) * (ui->MyLightAttenuationDoubleSpinBox3D->maximum() - ui->MyLightAttenuationDoubleSpinBox3D->minimum()) + ui->MyLightAttenuationDoubleSpinBox3D->minimum());
	ui->MyLightDiffuseDoubleSpinBox3D->setValue(1.0 * (ui->MyLightDiffuseSlider3D->value() - ui->MyLightDiffuseSlider3D->minimum()) / (ui->MyLightDiffuseSlider3D->maximum() - ui->MyLightDiffuseSlider3D->minimum()) * (ui->MyLightDiffuseDoubleSpinBox3D->maximum() - ui->MyLightDiffuseDoubleSpinBox3D->minimum()) + ui->MyLightDiffuseDoubleSpinBox3D->minimum());
	ui->MyLightMirrorDoubleSpinBox3D->setValue(1.0 * (ui->MyLightMirrorSlider3D->value() - ui->MyLightMirrorSlider3D->minimum()) / (ui->MyLightMirrorSlider3D->maximum() - ui->MyLightMirrorSlider3D->minimum()) * (ui->MyLightMirrorDoubleSpinBox3D->maximum() - ui->MyLightMirrorDoubleSpinBox3D->minimum()) + ui->MyLightMirrorDoubleSpinBox3D->minimum());
	ui->MyLightMirrorNsDoubleSpinBox3D->setValue(1.0 * (ui->MyLightMirrorNsSlider3D->value() - ui->MyLightMirrorNsSlider3D->minimum()) / (ui->MyLightMirrorNsSlider3D->maximum() - ui->MyLightMirrorNsSlider3D->minimum()) * (ui->MyLightMirrorNsDoubleSpinBox3D->maximum() - ui->MyLightMirrorNsDoubleSpinBox3D->minimum()) + ui->MyLightMirrorNsDoubleSpinBox3D->minimum());

	connect(ui->MyTabWidget3D, &QTabWidget::currentChanged, 
		[=]() mutable
		{
			switch (ui->MyTabWidget3D->currentIndex())
			{
			case 0:
			{
				emit MyTabStretch3DSignal();
				break;
			}

			case 1:
			{
				emit MyTabRot3DSignal();
				break;
			}

			case 2:
			{
				emit MyTabTrans3DSignal();
				break;
			}

			case 3:
			{
				emit MyTabShow3DSignal();
				break;
			}

			case 4:
			{
				emit MyTabRend3DSignal();
			}

			case 5:
			{
				emit MyTabAnimation3DSignal();
			}

			default:
				break;
			}
		}
	);

	//拉伸
	connect(ui->MyStretchPushButton3D, &QPushButton::clicked, 
		[=]() mutable
		{
			this->MyOperatorReset3D = false;
			this->MyOperatorStretchLength3D = ui->MyStretchDoubleSpinBox3D->value();

			emit MyOperatorStretch3DSignal(this->MyOperatorStretchLength3D);
		}
	);

	//重置
	connect(ui->MyResetPushButton3D, &QPushButton::clicked,
		[=]() mutable
		{
			this->MyOperatorReset3D = true;
			emit MyOperatorReset3DSignal(this->MyOperatorReset3D);
		}
	);

	//旋转
	connect(ui->MyRotPushButton3D, &QPushButton::clicked,
		[=]() mutable
		{
			this->MyOperatorReset3D = false;

			this->MyOperatorPoint3D.x = ui->MyRotTXDoubleSpinBox3D->value();
			this->MyOperatorPoint3D.y = ui->MyRotTYDoubleSpinBox3D->value();
			this->MyOperatorPoint3D.z = ui->MyRotTZDoubleSpinBox3D->value();

			this->MyRotRXAngle3D = ui->MyRotRXDoubleSpinBox3D->value();
			this->MyRotRYAngle3D = ui->MyRotRYDoubleSpinBox3D->value();
			this->MyRotRZAngle3D = ui->MyRotRZDoubleSpinBox3D->value();

			emit MyOperatotRot3DSignal(this->MyOperatorPoint3D, this->MyRotRXAngle3D, this->MyRotRYAngle3D, this->MyRotRZAngle3D);
		}
	);

	//平移
	connect(ui->MyTransPushButton3D, &QPushButton::clicked,
		[=]() mutable
		{
			this->MyOperatorReset3D = false;

			this->MyOperatorPoint3D.x = ui->MyTransTXDoubleSpinBox3D->value();
			this->MyOperatorPoint3D.y = ui->MyTransTYDoubleSpinBox3D->value();
			this->MyOperatorPoint3D.z = ui->MyTransTZDoubleSpinBox3D->value();

			emit MyOperatorTrans3DSignal(this->MyOperatorPoint3D);
		}
	);

	//显示
	connect(ui->MyLineShowOnRadioButton3D, &QRadioButton::toggled,
		[=]() mutable
		{
			int MyDrawBodyTypeFlage3D = 0;
			emit MyOperatorShow3DSignal(MyDrawBodyTypeFlage3D);
		}
	);
	connect(ui->MyLineShowOffRadioButton3D, &QRadioButton::toggled,
		[=]() mutable
		{
			int MyDrawBodyTypeFlage3D = 1;
			emit MyOperatorShow3DSignal(MyDrawBodyTypeFlage3D);
		}
	);
	connect(ui->MyRendRadioButton3D, &QRadioButton::toggled,
		[=]() mutable
		{
			int MyDrawBodyTypeFlage3D = 2;
			emit MyOperatorShow3DSignal(MyDrawBodyTypeFlage3D);
		}
	);

	//渲染
	//颜色
	connect(ui->MyLightColorPushButton3D, &QPushButton::clicked, 
		[=]() mutable
		{
			this->MyLightColor3D = QColorDialog::getColor(Qt::green, this, "LightColor");
			MyOperatorRendFlage3D();
		}
	);
	//X向量
	connect(ui->MyLightPosXSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightPosXDoubleSpinBox3D->setValue(1.0* (ui->MyLightPosXSlider3D->value() - ui->MyLightPosXSlider3D->minimum()) / (ui->MyLightPosXSlider3D->maximum() - ui->MyLightPosXSlider3D->minimum()) * (ui->MyLightPosXDoubleSpinBox3D->maximum() - ui->MyLightPosXDoubleSpinBox3D->minimum()) + ui->MyLightPosXDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//Y向量
	connect(ui->MyLightPosYSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightPosYDoubleSpinBox3D->setValue(1.0* (ui->MyLightPosYSlider3D->value() - ui->MyLightPosYSlider3D->minimum()) / (ui->MyLightPosYSlider3D->maximum() - ui->MyLightPosYSlider3D->minimum()) * (ui->MyLightPosYDoubleSpinBox3D->maximum() - ui->MyLightPosYDoubleSpinBox3D->minimum()) + ui->MyLightPosYDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//Z向量
	connect(ui->MyLightPosZSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightPosZDoubleSpinBox3D->setValue(1.0* (ui->MyLightPosZSlider3D->value() - ui->MyLightPosZSlider3D->minimum()) / (ui->MyLightPosZSlider3D->maximum() - ui->MyLightPosZSlider3D->minimum()) * (ui->MyLightPosZDoubleSpinBox3D->maximum() - ui->MyLightPosZDoubleSpinBox3D->minimum()) + ui->MyLightPosZDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//环境光光强
	connect(ui->MyLightEnvironmentSlider3D, &QSlider::valueChanged, 
		[=]() mutable
		{
			ui->MyLightEnvironmentDoubleSpinBox3D->setValue(1.0* (ui->MyLightEnvironmentSlider3D->value() - ui->MyLightEnvironmentSlider3D->minimum()) / (ui->MyLightEnvironmentSlider3D->maximum() - ui->MyLightEnvironmentSlider3D->minimum()) * (ui->MyLightEnvironmentDoubleSpinBox3D->maximum() - ui->MyLightEnvironmentDoubleSpinBox3D->minimum()) + ui->MyLightEnvironmentDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//光强衰减因子
	connect(ui->MyLightAttenuationSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightAttenuationDoubleSpinBox3D->setValue(1.0* (ui->MyLightAttenuationSlider3D->value() - ui->MyLightAttenuationSlider3D->minimum()) / (ui->MyLightAttenuationSlider3D->maximum() - ui->MyLightAttenuationSlider3D->minimum()) * (ui->MyLightAttenuationDoubleSpinBox3D->maximum() - ui->MyLightAttenuationDoubleSpinBox3D->minimum()) + ui->MyLightAttenuationDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//漫反射系数
	connect(ui->MyLightDiffuseSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightDiffuseDoubleSpinBox3D->setValue(1.0* (ui->MyLightDiffuseSlider3D->value() - ui->MyLightDiffuseSlider3D->minimum()) / (ui->MyLightDiffuseSlider3D->maximum() - ui->MyLightDiffuseSlider3D->minimum()) * (ui->MyLightDiffuseDoubleSpinBox3D->maximum() - ui->MyLightDiffuseDoubleSpinBox3D->minimum()) + ui->MyLightDiffuseDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//镜面反射系数
	connect(ui->MyLightMirrorSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightMirrorDoubleSpinBox3D->setValue(1.0* (ui->MyLightMirrorSlider3D->value() - ui->MyLightMirrorSlider3D->minimum()) / (ui->MyLightMirrorSlider3D->maximum() - ui->MyLightMirrorSlider3D->minimum()) * (ui->MyLightMirrorDoubleSpinBox3D->maximum() - ui->MyLightMirrorDoubleSpinBox3D->minimum()) + ui->MyLightMirrorDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//镜面反射指数
	connect(ui->MyLightMirrorNsSlider3D, &QSlider::valueChanged,
		[=]() mutable
		{
			ui->MyLightMirrorNsDoubleSpinBox3D->setValue(1.0* (ui->MyLightMirrorNsSlider3D->value() - ui->MyLightMirrorNsSlider3D->minimum()) / (ui->MyLightMirrorNsSlider3D->maximum() - ui->MyLightMirrorNsSlider3D->minimum()) * (ui->MyLightMirrorNsDoubleSpinBox3D->maximum() - ui->MyLightMirrorNsDoubleSpinBox3D->minimum()) + ui->MyLightMirrorNsDoubleSpinBox3D->minimum());
			MyOperatorRendFlage3D();
		}
	);

	//动画
	connect(ui->MyDrawPushButton3D, &QPushButton::clicked,
		[=]() mutable
		{
			emit MyOperatorDraw3DSignal();
		}
	);
	connect(ui->MyRunPushButton3D, &QPushButton::clicked,
		[=]() mutable
		{
			emit MyOperatorRun3DSignal();
		}
	);
	connect(ui->MyStopPushButton3D, &QPushButton::clicked,
		[=]() mutable
		{
			emit MyOperatorStop3DSignal();
		}
	);
}

MyOperatorDialog3D::~MyOperatorDialog3D()
{
    delete ui;
}

void MyOperatorDialog3D::MyOperatorRendFlage3D()
{
	this->MyLightPos3D.vx = ui->MyLightPosXDoubleSpinBox3D->value();
	this->MyLightPos3D.vy = ui->MyLightPosYDoubleSpinBox3D->value();
	this->MyLightPos3D.vz = ui->MyLightPosZDoubleSpinBox3D->value();

	this->MyLightEnvironment3D = ui->MyLightEnvironmentDoubleSpinBox3D->value();
	this->MyLightAttenuation3D = ui->MyLightAttenuationDoubleSpinBox3D->value();
	this->MyLightDiffuse3D = ui->MyLightDiffuseDoubleSpinBox3D->value();
	this->MyLightMirror3D = ui->MyLightMirrorDoubleSpinBox3D->value();
	this->MyLightMirrorNs3D = ui->MyLightMirrorNsDoubleSpinBox3D->value();

	emit MyOperatorRend3DSignal(this->MyLightColor3D, this->MyLightPos3D, this->MyLightEnvironment3D, this->MyLightAttenuation3D, this->MyLightDiffuse3D, this->MyLightMirror3D, this->MyLightMirrorNs3D);
}
