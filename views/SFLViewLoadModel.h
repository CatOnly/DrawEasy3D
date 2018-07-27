#ifndef SFLVIEWLOADMODEL_H
#define SFLVIEWLOADMODEL_H

#include "../common/SFLViewAbstract.h"

class SFLViewLoadModel:public SFLViewAbstract
{
public:
    SFLViewLoadModel(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewLoadModel();

    void changeViewBy(int index) override;

protected:
    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWLOADMODEL_H
