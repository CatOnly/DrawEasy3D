#include "SFLViewLight.h"
#include <QDebug>
SFLViewLight::SFLViewLight(QWidget *parent) : QWidget(parent)
{

}
SFLViewLight::~SFLViewLight(){
    qDebug() << __func__;
}
