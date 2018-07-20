#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T11:00:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawEasy3D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#   CONFIG += precompile_header
#   PRECOMPILED_HEADER = common/SFLDefine.h

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    views/SFLViewRender.cpp \
    views/SFLViewControl.cpp \
    views/SFLToolBar.cpp \
    views/SFLViewLight.cpp \
    views/SFLViewNoLight.cpp \
    common/SFLModelAbstract.cpp

HEADERS += \
        MainWindow.h \
    views/SFLViewRender.h \
    views/SFLViewControl.h \
    views/SFLToolBar.h \
    views/SFLViewLight.h \
    common/SFLModelAbstract.h \
    models/SFLModelLight.h \
    views/SFLViewNoLight.h \
    common/SFLDefine.h \
    models/SFLModelNoLight.h \
    common/SFLToolBtn.h

RESOURCES += \
    assets/assetInfo.qrc
