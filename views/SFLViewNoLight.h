#ifndef SFLVIEWNOLIGHT_H
#define SFLVIEWNOLIGHT_H

#include "../common/SFLViewAbstract.h"

class SFLVec1Editor;
class SFLVec3Editor;
class SFLSelectorLayout;
class SFLViewNoLight : public SFLViewAbstract
{
    Q_OBJECT
public:
    explicit SFLViewNoLight(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewNoLight();

public slots:
    void changeViewBy(int index) override;
    void setIsOnlyDrawLine(int index);
    void setIsRightDir(int index);
    void setColorWeight(double weight);

protected:
    SFLSelectorLayout *_drawType;
    SFLSelectorLayout *_direction;
    SFLVec1Editor *_colorWeight;
    SFLVec3Editor *_scale;
    SFLVec3Editor *_rotate;
    SFLVec3Editor *_move;

    void setupUI();
};

#endif // SFLVIEWNOLIGHT_H
