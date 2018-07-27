#ifndef SFLMODELLIGHTCASTER_H
#define SFLMODELLIGHTCASTER_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewLightCaster.h"

class SFLModelLightCaster: public SFLModelAbstract {

public:
    SFLModelLightCaster():SFLModelAbstract(){
        _btn->setText("投光物");
        _view = new SFLViewLightCaster(this);
    }
    ~SFLModelLightCaster(){
        if (_hasInitialized){

        }
    }

    void initializeOpenGL() override{

    }

    void render() override{

    }

private:

};

#endif // SFLMODELLIGHTCASTER_H
