#ifndef SFLMODELSNOLIGHT_H
#define SFLMODELSNOLIGHT_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewNoLight.h"

class SFLModelNoLight: public SFLModelAbstract
{
public:
    SFLModelNoLight():SFLModelAbstract(){
        _view = new SFLViewNoLight();
        _btn->setText("无光照");
    }

    void render(){
        glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
    }

protected:

};

#endif // SFLMODELSNOLIGHT_H
