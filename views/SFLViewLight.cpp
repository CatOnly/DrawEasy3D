#include "SFLViewLight.h"
#include "../common/SFLVec1Editor.h"
#include "../common/SFLVec3Editor.h"
#include "../common/SFLSelectorLayout.h"
#include "../models/SFLModelLight.h"
#include <QLabel>
#include <QDebug>

SFLViewLight::SFLViewLight(SFLModelAbstract *owner, QWidget *parent) : SFLViewAbstract(owner, parent)
{
    _types = QStringList({"无光照","色彩光照","高氏光照 (Gouraud)", "冯氏光照 (Phong)", "Blinn-Phong"});

    _lightColor = new SFLVec3Editor("颜色");
    _materialColor = new SFLVec3Editor("颜色");
    _lightOption = new SFLSelectorLayout("光源");
    _lightOption->setSelections({"固定","旋转"});
    _materialOption = new SFLSelectorLayout("模型");
    _materialOption->setSelections({"固定","旋转"});

    _lightAmbient = new SFLVec3Editor("环境光");
    _lightDiffuse = new SFLVec3Editor("漫反射");
    _lightSpecular = new SFLVec3Editor("镜面反射");

    _materialAmbient = new SFLVec3Editor("环境光");
    _materialDiffuse = new SFLVec3Editor("漫反射");
    _materialSpecular = new SFLVec3Editor("镜面反射");
    _materialShininess = new SFLVec1Editor("镜面反射强度", SFLVec1Editor::typePosition);

    setupUI();
    initData();
}

SFLViewLight::~SFLViewLight()
{
    disconnect(_lightOption, &SFLSelectorLayout::selectChanged, this, &SFLViewLight::setIsRotateLight);
    disconnect(_materialOption, &SFLSelectorLayout::selectChanged, this, &SFLViewLight::setIsRotateModel);

    disconnect(_lightColor, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightColor);
    disconnect(_lightAmbient, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightAmbient);
    disconnect(_lightDiffuse, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightDiffuse);
    disconnect(_lightSpecular, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightSpecular);

    disconnect(_materialColor, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialColor);
    disconnect(_materialAmbient, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialAmbient);
    disconnect(_materialDiffuse, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialDiffuse);
    disconnect(_materialSpecular, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialSpecular);
    disconnect(_materialShininess, &SFLVec1Editor::changeValue, this, &SFLViewLight::setMaterialShininess);
}

void SFLViewLight::initData()
{
    _lightColor->setVec3Vals(1.0, 1.0, 1.0);
    _materialColor->setVec3Vals(1.0, 0.5, 0.31);

    _lightAmbient->setVec3Vals(0.2);
    _lightDiffuse->setVec3Vals(0.5);
    _lightSpecular->setVec3Vals(1.0);

    _materialAmbient->setVec3Vals(1.0, 0.5, 0.31);
    _materialDiffuse->setVec3Vals(1.0, 0.5, 0.31);
    _materialSpecular->setVec3Vals(0.5);
    _materialShininess->setValue(32.0);
}

void SFLViewLight::initDataCamera()
{
    SFLViewAbstract::initDataCamera();
    initData();
}

void SFLViewLight::setupUI()
{
    QLabel *labelLight = new QLabel("光照");
    labelLight->setContentsMargins(5, 5, 5, 0);
    QLabel *labelMaterial = new QLabel("材质");
    labelMaterial->setContentsMargins(5, 5, 5, 0);

    QVBoxLayout *layoutMain = static_cast<QVBoxLayout *>(layout());
    layoutMain->addWidget(labelLight);
    layoutMain->addLayout(_lightColor);
    layoutMain->addLayout(_lightOption);
    layoutMain->addLayout(_lightAmbient);
    layoutMain->addLayout(_lightDiffuse);
    layoutMain->addLayout(_lightSpecular);
    layoutMain->addWidget(labelMaterial);
    layoutMain->addLayout(_materialColor);
    layoutMain->addLayout(_materialOption);
    layoutMain->addLayout(_materialAmbient);
    layoutMain->addLayout(_materialDiffuse);
    layoutMain->addLayout(_materialSpecular);
    layoutMain->addLayout(_materialShininess);

    connect(_lightOption, &SFLSelectorLayout::selectChanged, this, &SFLViewLight::setIsRotateLight);
    connect(_materialOption, &SFLSelectorLayout::selectChanged, this, &SFLViewLight::setIsRotateModel);

    connect(_lightColor, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightColor);
    connect(_lightAmbient, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightAmbient);
    connect(_lightDiffuse, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightDiffuse);
    connect(_lightSpecular, &SFLVec3Editor::changeValue, this, &SFLViewLight::setLightSpecular);

    connect(_materialColor, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialColor);
    connect(_materialAmbient, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialAmbient);
    connect(_materialDiffuse, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialDiffuse);
    connect(_materialSpecular, &SFLVec3Editor::changeValue, this, &SFLViewLight::setMaterialSpecular);
    connect(_materialShininess, &SFLVec1Editor::changeValue, this, &SFLViewLight::setMaterialShininess);
}

void SFLViewLight::setIsRotateLight(int index)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->isRotateLight = (index != 0);

    emit needRender();
}
void SFLViewLight::setIsRotateModel(int index)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->isRotateModel = (index != 0);

    emit needRender();
}
void SFLViewLight::setLightColor(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->lightColor = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setLightAmbient(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->lightAmbient = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setLightDiffuse(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->lightDiffuse = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setLightSpecular(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->lightSpecular = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setMaterialColor(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->materialColor = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setMaterialAmbient(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->materialAmbient = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setMaterialDiffuse(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->materialDiffuse = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setMaterialSpecular(double r, double g, double b)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->materialSpecular = gm::vec3(r, g, b);

    emit needRender();
}
void SFLViewLight::setMaterialShininess(double r)
{
    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->materialShininess = r;

    emit needRender();
}

void  SFLViewLight::changeViewBy(int index)
{
    if (index < 2){
        _lightColor->show();
        _materialColor->show();

        _lightOption->hide();
        _lightAmbient->hide();
        _lightDiffuse->hide();
        _lightSpecular->hide();

        _materialOption->hide();
        _materialAmbient->hide();
        _materialDiffuse->hide();
        _materialSpecular->hide();
        _materialShininess->hide();
    } else {
        _lightColor->hide();
        _materialColor->hide();

        _lightOption->show();
        _lightAmbient->show();
        _lightDiffuse->show();
        _lightSpecular->show();

        _materialOption->show();
        _materialAmbient->show();
        _materialDiffuse->show();
        _materialSpecular->show();
        _materialShininess->show();
    }

    SFLModelLight::ShaderType type;
    switch (index) {
        case 0:
            type = SFLModelLight::typeColor;
            break;
        case 1:
            type = SFLModelLight::typeLight;
            break;
        case 2:
            type = SFLModelLight::typeModelGouraud;
            break;
        case 3:
            type = SFLModelLight::typeModelPhone;
            break;
        case 4:
            type = SFLModelLight::typeModelBlinnPhone;
            break;
        default:
            type = SFLModelLight::typeColor;
            break;
    }

    SFLModelLight *model = static_cast<SFLModelLight *>(_owner);
    model->type = type;

    emit needRender();
}
