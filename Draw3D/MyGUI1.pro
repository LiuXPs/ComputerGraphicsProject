QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MyAxisDialog2D.cpp \
    MyOperatorDialog3D.cpp \
    main.cpp \
    MyGUI1.cpp

HEADERS += \
    My2DStretch3D.h \
    MyAnimation3D.h \
    MyAxisDialog2D.h \
    MyCut2D.h \
    MyDDALine2D.h \
    MyDrawBody3D.h \
    MyDrawPolyGons2D.h \
    MyDrawPolyGons3D.h \
    MyFill2D.h \
    MyGUI1.h \
    MyGetChangeMat2D.h \
    MyGetChangeMat3D.h \
    MyInterSortXYPoint2D.h \
    MyLine2D.h \
    MyLine3D.h \
    MyMatProductMat2D.h \
    MyMatProductMat3D.h \
    MyMirr2D.h \
    MyOperatorDialog3D.h \
    MyPlane2D.h \
    MyPlane3D.h \
    MyPoint3D.h \
    MyPointProductMat2D.h \
    MyPointProductMat3D.h \
    MyRend3D.h \
    MyRot2D.h \
    MyRot3D.h \
    MyScale2D.h \
    MySortPolyGons2D.h \
    MyStretchSolid3D.h \
    MyTrans2D.h \
    MyTrans3D.h \
    MyVector3D.h \
    MyVectorDotVector3D.h \
    MyVectorXVector2D.h \
    MyVectorXVector3D.h \
    MyVectorXVectorInZ3D.h \
    MyXPoint2D.h \
    MyXYPointLine2D.h

FORMS += \
    MyAxisDialog2D.ui \
    MyGUI1.ui \
    MyOperatorDialog3D.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
