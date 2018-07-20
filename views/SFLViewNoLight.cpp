#include "SFLViewNoLight.h"
#include <QHBoxLayout>
#include <QGridLayout>

#include <QLabel>
#include <QDoubleSpinBox>
#include <QDebug>

SFLViewNoLight::SFLViewNoLight(QWidget *parent) : QWidget(parent)
{
    setupUI();
}
SFLViewNoLight::~SFLViewNoLight(){
    qDebug() << __func__;
}

void SFLViewNoLight::setupUI()
{
    QHBoxLayout *layoutMain = new QHBoxLayout(this);
    setLayout(layoutMain);
    QGridLayout *cell = new QGridLayout(this);
    layoutMain->addLayout(cell);
    cell->setColumnStretch(0, 2);
    cell->setColumnStretch(1, 2);
    cell->setColumnStretch(2, 2);
    cell->setColumnStretch(3, 2);

    QLabel *label = new QLabel("颜色");
    QDoubleSpinBox *x = new QDoubleSpinBox(this);
    x->setRange(0, 1);  // 范围
    x->setDecimals(1);  // 精度
    x->setSingleStep(0.1);

    QDoubleSpinBox *y = new QDoubleSpinBox(this);
    y->setRange(0, 1);  // 范围
    y->setDecimals(1);  // 精度
    y->setSingleStep(0.1);

    QDoubleSpinBox *z = new QDoubleSpinBox(this);
    z->setRange(0, 1);  // 范围
    z->setDecimals(1);  // 精度
    z->setSingleStep(0.1);

    cell->addWidget(label, 1, 0);
    cell->addWidget(x, 1, 1);
    cell->addWidget(y, 1, 2);
    cell->addWidget(z, 1, 3);
}
