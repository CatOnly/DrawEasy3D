#ifndef SFLMODELABSTRACT_H
#define SFLMODELABSTRACT_H

#include "SFLDefine.h"
#include "SFLToolBtn.h"
#include "SFLViewAbstract.h"
#include <QOpenGLFunctions>

class SFLModelAbstract:public QOpenGLFunctions
{
public:
    static SFLModelAbstract *currentUseWidget;

    SFLModelAbstract();

    virtual ~SFLModelAbstract();
    virtual void render() = 0;
    void initializeOpenGLFunctions();

    SFLViewAbstract *view();
    SFLToolBtn *toolBtn();

protected:
    bool _hasInitialized = false;
    SFLViewAbstract *_view = nullptr;
    SFLToolBtn *_btn = nullptr;
};
#endif // SFLMODELABSTRACT_H
