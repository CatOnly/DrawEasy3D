#include "SFLViewNoLight.h"
#include "../common/SFLVec3Editor.h"
#include <QHBoxLayout>

SFLViewNoLight::SFLViewNoLight(SFLModelAbstract *owner, QWidget *parent) : SFLViewAbstract(owner, parent)
{
    _types = QStringList({"色彩着色","纹理贴图"});
    _vec3Color = new SFLVec3Editor("颜色");

    setupUI();
}
SFLViewNoLight::~SFLViewNoLight(){

}

void SFLViewNoLight::setupUI()
{
    QHBoxLayout *layoutMain = new QHBoxLayout(this);
    setLayout(layoutMain);
    layoutMain->setContentsMargins(0,0,0,0);
    layoutMain->addLayout(_vec3Color);
}

void SFLViewNoLight::changeViewBy(int index)
{

}
