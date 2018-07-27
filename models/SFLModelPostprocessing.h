#ifndef SFLMODELPOSTPROCESSING_H
#define SFLMODELPOSTPROCESSING_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewPostprocessing.h"

class SFLModelPostprocessing: public SFLModelAbstract
{
public:
    SFLModelPostprocessing():SFLModelAbstract(){
        _btn->setText("后处理");
        _view = new SFLViewPostprocessing(this);
    }

    ~SFLModelPostprocessing(){
        if (_hasInitialized){

        }
    }

    void initializeOpenGL() override {

    }

    void render() override {

    }

private:
};

#endif // SFLMODELPOSTPROCESSING_H
