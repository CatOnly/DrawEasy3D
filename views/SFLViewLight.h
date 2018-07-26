#ifndef SFLVIEWLIGHT_H
#define SFLVIEWLIGHT_H

#include "../common/SFLViewAbstract.h"

class SFLVec1Editor;
class SFLVec3Editor;
class SFLSelectorLayout;
class SFLViewLight : public SFLViewAbstract
{
    Q_OBJECT
public:
    explicit SFLViewLight(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewLight();

    void initData() override;
    void changeViewBy(int index) override;

    void setIsRotateLight(int index);
    void setIsRotateModel(int index);

    void setLightColor(double r, double g, double b);
    void setLightAmbient(double r, double g, double b);
    void setLightDiffuse(double r, double g, double b);
    void setLightSpecular(double r, double g, double b);

    void setMaterialColor(double r, double g, double b);
    void setMaterialAmbient(double r, double g, double b);
    void setMaterialDiffuse(double r, double g, double b);
    void setMaterialSpecular(double r, double g, double b);
    void setMaterialShininess(double r);

protected:
    SFLSelectorLayout *_lightOption;
    SFLVec3Editor *_lightColor;
    SFLVec3Editor *_lightAmbient; // 环境光
    SFLVec3Editor *_lightDiffuse; // 漫反射
    SFLVec3Editor *_lightSpecular;// 镜面反射

    SFLSelectorLayout *_materialOption;
    SFLVec3Editor *_materialColor;
    SFLVec3Editor *_materialAmbient;
    SFLVec3Editor *_materialDiffuse;
    SFLVec3Editor *_materialSpecular;
    SFLVec1Editor *_materialShininess;

    void setupUI() override;
};

#endif // SFLVIEWLIGHT_H
