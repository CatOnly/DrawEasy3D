#include "SFLViewLoadModel.h"
#include "../models/SFLModelLoadModel.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>

#define LABEL_TEXT_DEFAULT "无"

SFLViewLoadModel::SFLViewLoadModel(SFLModelAbstract *owner, QWidget *parent):SFLViewAbstract(owner, parent)
{
    _types = QStringList({"请添加 OBJ 类型的模型"});
    _labelModel = new QLabel(LABEL_TEXT_DEFAULT);
    _loadModelBtn = new QPushButton("重新添加模型");

    initData();
    setupUI();
}

SFLViewLoadModel::~SFLViewLoadModel(){
    disconnect(_loadModelBtn, &QPushButton::clicked, this, &SFLViewLoadModel::loadModel);
}

void SFLViewLoadModel::initData()
{

}

void SFLViewLoadModel::setupUI()
{
    QLabel *labelTitle = new QLabel("模型名：");
    QHBoxLayout *layoutH = new QHBoxLayout();
    layoutH->addWidget(labelTitle, 2);
    layoutH->addWidget(_labelModel, 6);
    QLabel *labelInfo = new QLabel("注意：所有模型文件资源必须在同一文件夹下！");
    labelInfo->setStyleSheet("color:rgb(100, 100, 100); font-size:11px;");

    QVBoxLayout *layoutMain = static_cast<QVBoxLayout *>(layout());
    layoutMain->addLayout(layoutH);
    layoutMain->addWidget(labelInfo);
    layoutMain->addWidget(_loadModelBtn);

    connect(_loadModelBtn, &QPushButton::clicked, this, &SFLViewLoadModel::loadModel);
}

void SFLViewLoadModel::loadModel(){
    QString filepath = QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::homePath(),
                "Document files (*.obj)"
                );
    if (!filepath.isNull()){
        SFLModelLoadModel *model = static_cast<SFLModelLoadModel *>(_owner);
        if (model->loadModel(filepath.toStdString().c_str())) {
            _labelModel->setText(QFileInfo(filepath).fileName());
        } else {
            _labelModel->setText(LABEL_TEXT_DEFAULT);
        }
    }
}

void SFLViewLoadModel::changeViewBy(int index)
{

}
