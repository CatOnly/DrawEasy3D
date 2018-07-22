#include "SFLViewNoLight.h"
#include "../models/SFLModelNoLight.h"
#include "../common/SFLSelectorLayout.h"
#include "../common/SFLVec1Editor.h"
#include "../common/SFLVec3Editor.h"
#include <QVBoxLayout>

SFLViewNoLight::SFLViewNoLight(SFLModelAbstract *owner, QWidget *parent) : SFLViewAbstract(owner, parent)
{
    _types = QStringList({"顶点着色","纹理贴图","变换","透视"});
    _drawType = new SFLSelectorLayout("绘制方式");
    _drawType->setSelections(QStringList({"填充","线条"}));
    _direction = new SFLSelectorLayout("纹理方向");
    _direction->setSelections(QStringList({"默认","修正"}));
    _colorWeight = new SFLVec1Editor("颜色比重");
    _scale = new SFLVec3Editor("缩放");
    _rotate = new SFLVec3Editor("旋转");
    _move = new SFLVec3Editor("位移");

    setupUI();
}
SFLViewNoLight::~SFLViewNoLight(){

}

void SFLViewNoLight::setupUI()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    setLayout(layoutMain);
    layoutMain->setContentsMargins(0,0,0,0);
    layoutMain->addLayout(_drawType);
    layoutMain->addLayout(_direction);
    layoutMain->addLayout(_colorWeight);
    layoutMain->addLayout(_scale);
    layoutMain->addLayout(_rotate);
    layoutMain->addLayout(_move);

    connect(_drawType, &SFLSelectorLayout::selectChanged, this, &SFLViewNoLight::setIsOnlyDrawLine);
    connect(_direction, &SFLSelectorLayout::selectChanged, this, &SFLViewNoLight::setIsRightDir);
    connect(_colorWeight, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setColorWeight);
}

void SFLViewNoLight::setIsOnlyDrawLine(int index)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setIsOnlyDrawLine(index != 0);
}

void SFLViewNoLight::setIsRightDir(int index)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setHasRightDirection(index != 0);
}

void SFLViewNoLight::setColorWeight(double weight)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setMixColorWeight(weight);
}

void SFLViewNoLight::changeViewBy(int index)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    if (index == 0) {
        owner->setHasTexture(false);
        _direction->hide();
        _colorWeight->hide();
    } else {
        owner->setHasTexture(true);
        _direction->show();
        _colorWeight->show();
    }

    if (index > 1){
        _scale->show();
        _rotate->show();
        _move->show();
    } else {
        _scale->hide();
        _rotate->hide();
        _move->hide();
    }
}
