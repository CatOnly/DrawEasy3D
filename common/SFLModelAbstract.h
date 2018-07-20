#ifndef SFLMODELABSTRACT_H
#define SFLMODELABSTRACT_H

#include "SFLDefine.h"
#include "SFLToolBtn.h"
#include <QDebug>

class SFLModelAbstract
{
public:
    static SFLModelAbstract *currentUseWidget;

    SFLModelAbstract();

    virtual ~SFLModelAbstract();
    virtual void render() = 0;

    QWidget *view();
    SFLToolBtn *toolBtn();

protected:
    QWidget *_view = nullptr;
    SFLToolBtn *_btn = nullptr;
};
#endif // SFLMODELABSTRACT_H
