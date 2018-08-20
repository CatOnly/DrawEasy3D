#ifndef SFLVIEWPOSTPROCESSING_H
#define SFLVIEWPOSTPROCESSING_H

#include "../common/SFLViewAbstract.h"

class SFLVec1Editor;
class SFLViewPostprocessing:public SFLViewAbstract
{
public:
    SFLViewPostprocessing(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewPostprocessing();

public slots:
    void setRadius(double radius);
    void setParam(double radius);
    void changeViewBy(int index) override;

protected:
    SFLVec1Editor *_radiusEditor;
    SFLVec1Editor *_paramEditor;

    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWPOSTPROCESSING_H
