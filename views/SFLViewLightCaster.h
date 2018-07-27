#ifndef SFLVIEWLIGHTCASTER_H
#define SFLVIEWLIGHTCASTER_H

#include "../common/SFLViewAbstract.h"

class SFLViewLightCaster: public SFLViewAbstract
{
public:
    SFLViewLightCaster(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewLightCaster();

    void changeViewBy(int index) override;

protected:
    void setupUI() override;
    void initData() override;

};

#endif // SFLVIEWLIGHTCASTER_H
