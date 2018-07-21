#include "SFLVec1Editor.h"
#include <QLabel>
#include <QDoubleSpinBox>

SFLVec1Editor::SFLVec1Editor(const QString title, QWidget *parent):QHBoxLayout(parent){
    _titleLabel = new QLabel(title);
    _doubleSpineBox = new QDoubleSpinBox();

    setupUI();
}

SFLVec1Editor::~SFLVec1Editor()
{
    void (QDoubleSpinBox::*funPtr)(double);
    funPtr = &QDoubleSpinBox::valueChanged;
    disconnect(_doubleSpineBox, funPtr, this, &SFLVec1Editor::onValueChanged);
}

void SFLVec1Editor::setupUI(){
    _titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    _titleLabel->setTextFormat(Qt::PlainText);
    _titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);

    addWidget(_titleLabel, 2);
    addWidget(_doubleSpineBox, 6);

    void (QDoubleSpinBox::*funPtr)(double);
    funPtr = &QDoubleSpinBox::valueChanged;
    connect(_doubleSpineBox, funPtr, this, &SFLVec1Editor::onValueChanged);
}

void SFLVec1Editor::setValue(double value){
    _doubleSpineBox->setValue(value);
}

void SFLVec1Editor::setSuffix(QString sufffix){
    _doubleSpineBox->setSuffix(sufffix);
}

void SFLVec1Editor::onValueChanged(double value){
    emit changeValue(value);
}
