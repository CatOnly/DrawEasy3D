#include "SFLViewShadow.h"
#include "../models/SFLModelShadow.h"

SFLViewShadow::SFLViewShadow(SFLModelAbstract *owner, QWidget *parent):SFLViewAbstract(owner, parent)
{
    _types = QStringList({"阴影","点阴影","CSM","SSAO"});

    initData();
    setupUI();
}

SFLViewShadow::~SFLViewShadow(){

}

void SFLViewShadow::initData()
{

}

void SFLViewShadow::setupUI()
{

}

void SFLViewShadow::changeViewBy(int index)
{
    std::vector<SFLModelShadow::ShadowType> types = {
        SFLModelShadow::ShadowType::TypeShadow,
        SFLModelShadow::ShadowType::TypeShadowPoint,
        SFLModelShadow::ShadowType::TypeShadowCSM,
        SFLModelShadow::ShadowType::TypeShadowSSAO,
    };

    SFLModelShadow *model = static_cast<SFLModelShadow *>(_owner);
    model->type = types[index];

    emit needRender();
}
