#ifndef SFLMODELMAPPING_H
#define SFLMODELMAPPING_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewMapping.h"

class SFLModelMapping: public SFLModelAbstract
{
public:
    SFLModelMapping():SFLModelAbstract(){
        _btn->setText("贴图");
        _view = new SFLViewMapping(this);
    }
    ~SFLModelMapping(){
        if (_hasInitialized){

        }
    }

    void initializeOpenGL() override {

    }

    void render() override {

    }

private:
};

#endif // SFLMODELMAPPING_H
