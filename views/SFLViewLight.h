#ifndef SFLVIEWLIGHT_H
#define SFLVIEWLIGHT_H

#include "../common/SFLViewAbstract.h"

class SFLViewLight : public SFLViewAbstract
{
    Q_OBJECT
public:
    explicit SFLViewLight(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewLight();

    void changeViewBy(int index);
};

#endif // SFLVIEWLIGHT_H
