#include "SFLModelAbstract.h"
#include <QDebug>

SFLModelAbstract *SFLModelAbstract::currentUseWidget = nullptr;

SFLModelAbstract::SFLModelAbstract():QOpenGLFunctions()
{
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

SFLViewAbstract *SFLModelAbstract::view()
{
    return _view;
}

SFLToolBtn *SFLModelAbstract::toolBtn()
{
    return _btn;
}
