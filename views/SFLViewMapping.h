#ifndef SFLVIEWMAPPING_H
#define SFLVIEWMAPPING_H

#include "../common/SFLViewAbstract.h"

class SFLVec1Editor;
class SFLVec3Editor;
class SFLSelectorLayout;
class SFLViewMapping:public SFLViewAbstract
{
public:
    enum LightType {
        typePointlight,
        typeSpotlight,
        typeMultiplylight
    };

    SFLViewMapping(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewMapping();

    void initDataCamera() override;
    void changeViewBy(int index) override;

    void setLightType(int index);
    void setLightColor(double r, double g, double b);
    void setLightSpotAngleInner(double value);
    void setLightSpotAngleOuter(double value);
    void setLightEmissionIntensity(double value);

protected:
    bool _isSpotLight = false;
    SFLSelectorLayout *_lightOption;
    SFLVec3Editor *_lightColor;
    SFLVec1Editor *_lightSpotAngleInner;
    SFLVec1Editor *_lightSpotAngleOuter;
    SFLVec1Editor *_lightEmitValue;

    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWMAPPING_H
