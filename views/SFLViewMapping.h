#ifndef SFLVIEWMAPPING_H
#define SFLVIEWMAPPING_H

#include "../common/SFLViewAbstract.h"

class SFLViewMapping:public SFLViewAbstract
{
public:
    SFLViewMapping(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewMapping();

    void changeViewBy(int index) override;

protected:
    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWMAPPING_H
