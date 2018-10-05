#include "SFLViewPostprocessing.h"
#include "../common/SFLVec1Editor.h"
#include "../models/SFLModelPostprocessing.h"

SFLViewPostprocessing::SFLViewPostprocessing(SFLModelAbstract *owner, QWidget *parent):SFLViewAbstract(owner, parent)
{
    _types = QStringList({"原图","边缘检测","美颜","矢量风格"});
    _radiusEditor = new SFLVec1Editor("采样范围", SFLVec1Editor::typePosition);
    _paramEditor = new SFLVec1Editor("参数", SFLVec1Editor::typePosition);

    initData();
    setupUI();
}

SFLViewPostprocessing::~SFLViewPostprocessing(){
    disconnect(_radiusEditor, &SFLVec1Editor::changeValue, this, &SFLViewPostprocessing::setRadius);
    disconnect(_paramEditor, &SFLVec1Editor::changeValue, this, &SFLViewPostprocessing::setParam);
}

void SFLViewPostprocessing::initData()
{
    _radiusEditor->setValue(1.0);
    _paramEditor->setValue(5.0);
}

void SFLViewPostprocessing::setupUI()
{
    QVBoxLayout *layoutMain = static_cast<QVBoxLayout *>(layout());
    layoutMain->addLayout(_radiusEditor);
    layoutMain->addLayout(_paramEditor);

    connect(_radiusEditor, &SFLVec1Editor::changeValue, this, &SFLViewPostprocessing::setRadius);
    connect(_paramEditor, &SFLVec1Editor::changeValue, this, &SFLViewPostprocessing::setParam);
}

void SFLViewPostprocessing::changeViewBy(int index)
{
    SFLModelPostprocessing *model = static_cast<SFLModelPostprocessing *>(_owner);
    model->type = SFLModelPostprocessing::ProcessType(index);

    emit needRender();
}

void SFLViewPostprocessing::setRadius(double radius)
{
    SFLModelPostprocessing *model = static_cast<SFLModelPostprocessing *>(_owner);
    model->radius = radius;

    emit needRender();
}

void SFLViewPostprocessing::setParam(double value)
{
    SFLModelPostprocessing *model = static_cast<SFLModelPostprocessing *>(_owner);
    model->param = value;

    emit needRender();
}
