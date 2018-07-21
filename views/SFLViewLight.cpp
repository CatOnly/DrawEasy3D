#include "SFLViewLight.h"
#include <QDebug>
SFLViewLight::SFLViewLight(SFLModelAbstract *owner, QWidget *parent) : SFLViewAbstract(owner, parent)
{
    _types = QStringList({"色彩光照","冯氏光照模型 (Phone Illumination)"});
}

SFLViewLight::~SFLViewLight()
{
    qDebug() << __func__;
}

void  SFLViewLight::changeViewBy(int index)
{

}
