#include "SFLViewMapping.h"
#include "../common/SFLVec1Editor.h"
#include "../common/SFLVec3Editor.h"
#include "../common/SFLSelectorLayout.h"
#include "../models/SFLModelMapping.h"

SFLViewMapping::SFLViewMapping(SFLModelAbstract *owner, QWidget *parent):SFLViewAbstract(owner, parent)
{
    _types = QStringList({"普通贴图", "光照贴图"});

    _lightOption = new SFLSelectorLayout("光源");
    _lightOption->setSelections({"定向光", "点光源", "聚光灯", "混合光照"});

    _lightColor = new SFLVec3Editor("颜色");
    _lightSpotAngleInner = new SFLVec1Editor("内角", SFLVec1Editor::typePosition);
    _lightSpotAngleInner->setSuffix("º");
    _lightSpotAngleOuter = new SFLVec1Editor("外角", SFLVec1Editor::typePosition);
    _lightSpotAngleOuter->setSuffix("º");
    _lightEmitValue = new SFLVec1Editor("放射光强度");

    setupUI();
    initData();
}

SFLViewMapping::~SFLViewMapping(){
    disconnect(_lightOption, &SFLSelectorLayout::selectChanged, this, &SFLViewMapping::setLightType);
    disconnect(_lightColor, &SFLVec3Editor::changeValue, this, &SFLViewMapping::setLightColor);
    disconnect(_lightSpotAngleInner, &SFLVec1Editor::changeValue, this, &SFLViewMapping::setLightSpotAngleInner);
    disconnect(_lightSpotAngleOuter, &SFLVec1Editor::changeValue, this, &SFLViewMapping::setLightSpotAngleOuter);
    disconnect(_lightEmitValue, &SFLVec1Editor::changeValue, this, &SFLViewMapping::setLightEmissionIntensity);
}

void SFLViewMapping::initData()
{
    _lightColor->setVec3Vals(1.0);
    _lightEmitValue->setValue(0.0);
    _lightSpotAngleInner->setValue(12.5);
    _lightSpotAngleOuter->setValue(15.0);
}

void SFLViewMapping::initDataCamera()
{
    initData();
}

void SFLViewMapping::setupUI()
{
    QVBoxLayout *layoutMain = static_cast<QVBoxLayout *>(layout());
    layoutMain->addLayout(_lightOption);
    layoutMain->addLayout(_lightSpotAngleInner);
    layoutMain->addLayout(_lightSpotAngleOuter);
    layoutMain->addLayout(_lightEmitValue);
    layoutMain->addLayout(_lightColor);

    connect(_lightOption, &SFLSelectorLayout::selectChanged, this, &SFLViewMapping::setLightType);
    connect(_lightColor, &SFLVec3Editor::changeValue, this, &SFLViewMapping::setLightColor);
    connect(_lightSpotAngleInner, &SFLVec1Editor::changeValue, this, &SFLViewMapping::setLightSpotAngleInner);
    connect(_lightSpotAngleOuter, &SFLVec1Editor::changeValue, this, &SFLViewMapping::setLightSpotAngleOuter);
    connect(_lightEmitValue, &SFLVec1Editor::changeValue, this, &SFLViewMapping::setLightEmissionIntensity);
}

void SFLViewMapping::setLightType(int index)
{
    _isSpotLight = (index > 1);
    if (_isSpotLight){
        _lightSpotAngleInner->show();
        _lightSpotAngleOuter->show();
    } else {
        _lightSpotAngleInner->hide();
        _lightSpotAngleOuter->hide();
    }

    SFLModelMapping *model = static_cast<SFLModelMapping *>(_owner);
    switch (index) {
        case 0: model->type = SFLModelMapping::typeLightDir;break;
        case 1: model->type = SFLModelMapping::typeLightPoint;break;
        case 2: model->type = SFLModelMapping::typeLightSpot;break;
        case 3: model->type = SFLModelMapping::typeLightMulti;break;
    }

    emit needRender();
}

void SFLViewMapping::changeViewBy(int index)
{
    SFLModelMapping *model = static_cast<SFLModelMapping *>(_owner);

    switch (index) {
    case 0:
        _lightOption->hide();
        _lightEmitValue->hide();
        _lightColor->hide();
        model->type = SFLModelMapping::typeTex;
        break;
    case 1:
        _lightOption->show();
        _lightEmitValue->show();
        _lightColor->show();
        model->type = SFLModelMapping::typeLightDir;
        break;
    }

    if (index > 0 && _isSpotLight){
        _lightSpotAngleInner->show();
        _lightSpotAngleOuter->show();
    } else {
        _lightSpotAngleInner->hide();
        _lightSpotAngleOuter->hide();
    }

    emit needRender();
}

void SFLViewMapping::setLightColor(double r, double g, double b)
{
    SFLModelMapping *model = static_cast<SFLModelMapping *>(_owner);
    model->lightColor = glm::vec3(r, g, b);

    emit needRender();
}

void SFLViewMapping::setLightSpotAngleInner(double value)
{
    SFLModelMapping *model = static_cast<SFLModelMapping *>(_owner);
    model->spotAngleInner = value;

    emit needRender();
}

void SFLViewMapping::setLightSpotAngleOuter(double value)
{
    SFLModelMapping *model = static_cast<SFLModelMapping *>(_owner);
    model->spotAngleOuter = value;

    emit needRender();
}

void SFLViewMapping::setLightEmissionIntensity(double value)
{
    SFLModelMapping *model = static_cast<SFLModelMapping *>(_owner);
    model->emissionIntensity = value;

    emit needRender();
}
