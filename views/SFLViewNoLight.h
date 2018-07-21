#ifndef SFLVIEWNOLIGHT_H
#define SFLVIEWNOLIGHT_H

#include "../common/SFLViewAbstract.h"

class SFLVec3Editor;
class SFLViewNoLight : public SFLViewAbstract
{
    Q_OBJECT
public:
    explicit SFLViewNoLight(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewNoLight();

    void changeViewBy(int index) override;

protected:
    SFLVec3Editor *_vec3Color;

    void setupUI();
};

#endif // SFLVIEWNOLIGHT_H
