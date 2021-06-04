#ifndef SFLVIEWSHADOW_H
#define SFLVIEWSHADOW_H

#include "../common/SFLViewAbstract.h"

class SFLViewShadow:public SFLViewAbstract
{
public:
    SFLViewShadow(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewShadow();

public slots:
    void changeViewBy(int index) override;

protected:
    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWSHADOW_H
