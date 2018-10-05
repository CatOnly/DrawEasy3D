#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T11:00:48
#
#-------------------------------------------------

QT += core gui

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

INCLUDEPATH += $$PWD/library/gmath
INCLUDEPATH += $$PWD/library/

macx {
    DISTFILES += \
        library/zlib/libzlibstatic.a \
        library/assimp/libassimp.3.3.1.dylib\
        library/sfl/libPostProcessing.a

    LIBS += -L$$PWD/library/zlib/ -lzlibstatic
    LIBS += -L$$PWD/library/assimp/ -lassimp.3.3.1
    LIBS += -L$$PWD/library/sfl/ -lPostProcessing
}

SOURCES += \
        main.cpp \
        MainWindow.cpp\
        views/SFLViewRender.cpp\
        views/SFLViewControl.cpp \
        views/SFLToolBar.cpp \
        views/SFLViewLight.cpp \
        views/SFLViewNoLight.cpp \
        common/SFLModelAbstract.cpp \
        common/SFLVec3Editor.cpp \
        common/SFLSelectorLayout.cpp \
        common/SFLVec1Editor.cpp \
        views/SFLViewMapping.cpp \
        views/SFLViewLoadModel.cpp \
        views/SFLViewPostprocessing.cpp

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
        common/SFLToolBtn.h \
        common/SFLVec3Editor.h \
        common/SFLSelectorLayout.h \
        common/SFLViewAbstract.h \
        common/SFLVec1Editor.h \
        renders/SFLShaderProgram.h \
        renders/SFLCameraVirtual.h \
        renders/SFLTexture.h \
        renders/SFLVertexArray.h \
        models/SFLModelMapping.h \
        views/SFLViewMapping.h \
        models/SFLModelLoadModel.h \
        views/SFLViewLoadModel.h \
        models/SFLModelPostprocessing.h \
        views/SFLViewPostprocessing.h \
        renders/SFLMesh.h \
        renders/SFLModel.h

HEADERS += \
    library/assimp/*.hpp \
    library/assimp/*.inl \
    library/assimp/*.h \
    library/assimp/Compiler/*.h\
    library/sfl/SFLPostProcessing.h\
    library/gmath/core/*.h\
    library/gmath/core/*.hpp\
    library/gmath/GMath.hpp

RESOURCES += \
    assets/assetInfo.qrc \
    shaders/shaders.qrc

DISTFILES += \
    shaders/cartoon.fsh \
    shaders/cartoon.vsh
