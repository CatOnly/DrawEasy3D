#ifndef SFLVIEWPOSTPROCESSING_H
#define SFLVIEWPOSTPROCESSING_H

#include "../common/SFLViewAbstract.h"

class SFLViewPostprocessing:public SFLViewAbstract
{
public:
    SFLViewPostprocessing(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewPostprocessing();

    void changeViewBy(int index) override;

protected:
    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWPOSTPROCESSING_H
