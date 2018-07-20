#include "SFLModelAbstract.h"

SFLModelAbstract *SFLModelAbstract::currentUseWidget = nullptr;

SFLModelAbstract::SFLModelAbstract()
{
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

QWidget *SFLModelAbstract::view()
{
    return _view;
}

SFLToolBtn *SFLModelAbstract::toolBtn()
{
    return _btn;
}
