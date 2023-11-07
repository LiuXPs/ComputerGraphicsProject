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


#ifndef _MYAXISDIALOG2D_H_
#define _MYAXISDIALOG2D_H_

#include <QDialog>
#include <QPoint>

#include "MyLine2D.h"

namespace Ui 
{
	class MyAxisDialog2D;
}

class MyAxisDialog2D : public QDialog
{
    Q_OBJECT

public:
    explicit MyAxisDialog2D(QWidget *parent = nullptr);
    ~MyAxisDialog2D();

private:
    Ui::MyAxisDialog2D *ui;

	//变量定义
public:
	QPoint MyAxisDlgAddPoint2D;
	QPoint MyAxisDlgTransPoint2D;
	QPoint MyAxisDlgRotPoint2D;
	QPoint MyAxisDlgScalePoint2D;
	MyLine2D MyAxisDlgMirrLine2D;
	double MyAxisDlgAngle2D;
	double MyAxisDlgScale2D;

signals:
	void MyAxisAddPoint2DSignal(QPoint);
signals:
	void MyAxisTrans2DSignal(QPoint);
signals:
	void MyAxisRot2DSignal(QPoint, double);
signals:
	void MyAxisMirr2DSignal(MyLine2D);
signals:
	void MyAxisScale2DSignal(QPoint, double);
signals:
	void MyTabAxis2DSignal();
signals:
	void MyTabTrans2DSignal();
signals:
	void MyTabRot2DSignal();
signals:
	void MyTabMirr2DSignal();
signals:
	void MyTabScale2DSignal();
};

#endif // !_MYAXISDIALOG2D_H_
