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


#ifndef _MYOPERATORDIALOG3D_H_
#define _MYOPERATORDIALOG3D_H_

#include <QDialog>

#include "MyPoint3D.h"
#include "MyVector3D.h"

namespace Ui 
{
	class MyOperatorDialog3D;
}

class MyOperatorDialog3D : public QDialog
{
    Q_OBJECT

public:
    explicit MyOperatorDialog3D(QWidget *parent = nullptr);
    ~MyOperatorDialog3D();

private:
    Ui::MyOperatorDialog3D *ui;

public:
	bool MyOperatorReset3D;
	double MyOperatorStretchLength3D;
	MyPoint3D MyOperatorPoint3D;
	double MyRotRXAngle3D;
	double MyRotRYAngle3D;
	double MyRotRZAngle3D;

	QColor MyLightColor3D;
	MyVector3D MyLightPos3D;
	double MyLightEnvironment3D;
	double MyLightAttenuation3D;
	double MyLightDiffuse3D;
	double MyLightMirror3D;
	double MyLightMirrorNs3D;

	void MyOperatorRendFlage3D();

signals:
	void MyOperatorReset3DSignal(bool);
signals:
	void MyOperatorStretch3DSignal(double);
signals:
	void MyOperatotRot3DSignal(MyPoint3D, double, double, double);
signals:
	void MyOperatorTrans3DSignal(MyPoint3D);
signals:
	void MyOperatorShow3DSignal(int);
signals:
	void MyOperatorRend3DSignal(QColor, MyVector3D, double, double, double, double, double);
signals:
	void MyOperatorDraw3DSignal();
signals:
	void MyOperatorRun3DSignal();
signals:
	void MyOperatorStop3DSignal();

signals:
	void MyTabStretch3DSignal();
signals:
	void MyTabRot3DSignal();
signals:
	void MyTabTrans3DSignal();
signals:
	void MyTabShow3DSignal();
signals:
	void MyTabRend3DSignal();
signals:
	void MyTabAnimation3DSignal();
};

#endif // !_MYOPERATORDIALOG3D_H_
