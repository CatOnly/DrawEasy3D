#ifndef SFLMODELLOADMODEL_H
#define SFLMODELLOADMODEL_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewLoadModel.h"

class SFLModelLoadModel: public SFLModelAbstract
{
public:
    SFLModelLoadModel():SFLModelAbstract(){
        _btn->setText("模型加载");
        _view = new SFLViewLoadModel(this);
    }
    ~SFLModelLoadModel(){
        if (_hasInitialized){

        }
    }

    void initializeOpenGL() override {

    }

    void render() override {

    }

private:
};
#endif // SFLMODELLOADMODEL_H
