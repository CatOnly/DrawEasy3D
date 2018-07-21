#include "SFLSelectorLayout.h"
#include <QLabel>
#include <QComboBox>

SFLSelectorLayout::SFLSelectorLayout(const QString title, QWidget *parent):QHBoxLayout(parent)
{
    _titleLabel = new QLabel(title);
    _comboBox = new QComboBox();

    setupUI();
}
SFLSelectorLayout::~SFLSelectorLayout()
{
    void (QComboBox::*funPtr)(int);
    funPtr = &QComboBox::currentIndexChanged;
    disconnect(_comboBox, funPtr, this, &SFLSelectorLayout::onSelectChanged);
}

void SFLSelectorLayout::setupUI()
{
    _titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    _titleLabel->setTextFormat(Qt::PlainText);
    _titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);

    addWidget(_titleLabel, 2);
    addWidget(_comboBox, 6);

    void (QComboBox::*funPtr)(int);
    funPtr = &QComboBox::currentIndexChanged;
    connect(_comboBox, funPtr, this, &SFLSelectorLayout::onSelectChanged);
}

void SFLSelectorLayout::setSelections(QStringList list)
{
    _comboBox->clear();
    _comboBox->addItems(list);
}

void SFLSelectorLayout::onSelectChanged(int index)
{
    emit selectChanged(index);
}
