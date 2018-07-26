#include "SFLModelAbstract.h"
#include <QDebug>

SFLModelAbstract *SFLModelAbstract::currentUseWidget = nullptr;

SFLModelAbstract::SFLModelAbstract():QOpenGLFunctions()
{
    _times = 0;
    _hasInitialized = false;
    _btn = new SFLToolBtn();
    _btn->setOwner(this);
    _btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
}

SFLModelAbstract::~SFLModelAbstract()
{
   if (SFLModelAbstract::currentUseWidget != this){
       DELETE_SAFE(_view)
   }
    qDebug()<< __func__;
}

void SFLModelAbstract::initializeOpenGLFunctions()
{
    if (_hasInitialized) return;

    QOpenGLFunctions::initializeOpenGLFunctions();
    initializeOpenGL();
    _hasInitialized = true;
}

void SFLModelAbstract::setDelegate(SFLCameraVirtual *delegate)
{
    _delegateCamaera = delegate;
}

void SFLModelAbstract::logMatrix(glm::mat4 matrix)
{
    float *a = glm::value_ptr(matrix);
    qDebug() << "matrix" << endl;
    for (int i=0; i < 4; ++i){
        qDebug() << *(a + i * 4) << *(a + i * 4 + 1) << *(a + i * 4 + 2) << *(a + i * 4 + 3);
    }
}

SFLViewAbstract *SFLModelAbstract::view()
{
    return _view;
}

SFLToolBtn *SFLModelAbstract::toolBtn()
{
    return _btn;
}
