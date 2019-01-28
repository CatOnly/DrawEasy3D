#include "SFLViewLoadModel.h"
#include "../models/SFLModelLoadModel.h"
#include "../common/SFLSelectorLayout.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>

#define LABEL_TEXT_DEFAULT "无"
#define LABEL_TEXT_MODEL "注意：所有模型文件资源必须在同一文件夹下！"
#define LABEL_TEXT_MESH "格式：{ points: { {x:0.0f, y:0.0f}, {x:1.0f, y:1.0f} } }"

SFLViewLoadModel::SFLViewLoadModel(SFLModelAbstract *owner, QWidget *parent):SFLViewAbstract(owner, parent)
{
    _types = QStringList({"OBJ 类型的模型", "Json 类型顶点 Mesh"});
    _drawType = new SFLSelectorLayout("绘制方式");
    _drawType->setSelections(QStringList({"填充","线条"}));
    _drawShader = new SFLSelectorLayout("附加绘制");
    _drawShader->setSelections(QStringList({"无", "白色纹理", "爆破", "法向量"}));
    _faceCulling = new SFLSelectorLayout("背面剔除");
    _faceCulling->setSelections(QStringList({"关闭","开启"}));
    _labelInfo = nullptr;
    _labelModel = new QLabel(LABEL_TEXT_DEFAULT);
    _loadModelBtn = new QPushButton("选择文件");

    initData();
    setupUI();
}

SFLViewLoadModel::~SFLViewLoadModel() {
    disconnect(_loadModelBtn, &QPushButton::clicked, this, &SFLViewLoadModel::loadFile);
    disconnect(_drawType, &SFLSelectorLayout::selectChanged, this, &SFLViewLoadModel::enableDrawLine);
}

void SFLViewLoadModel::initData()
{
    _srcType = LoadSRCModelObj;
}

void SFLViewLoadModel::setupUI()
{
    QLabel *labelTitle = new QLabel("文件名：");
    QHBoxLayout *layoutH = new QHBoxLayout();
    layoutH->addWidget(labelTitle, 2);
    layoutH->addWidget(_labelModel, 6);
    _labelInfo = new QLabel(LABEL_TEXT_MODEL);
    _labelInfo->setStyleSheet("color:rgb(100, 100, 100); font-size:11px;");

    QVBoxLayout *layoutMain = static_cast<QVBoxLayout *>(layout());
    layoutMain->addLayout(layoutH);
    layoutMain->addLayout(_drawType);
    layoutMain->addLayout(_drawShader);
    layoutMain->addLayout(_faceCulling);
    layoutMain->addWidget(_loadModelBtn);
    layoutMain->addWidget(_labelInfo);

    connect(_loadModelBtn, &QPushButton::clicked, this, &SFLViewLoadModel::loadFile);
    connect(_drawType, &SFLSelectorLayout::selectChanged, this, &SFLViewLoadModel::enableDrawLine);
    connect(_drawShader, &SFLSelectorLayout::selectChanged, this, &SFLViewLoadModel::selectorShaderIndex);
    connect(_faceCulling, &SFLSelectorLayout::selectChanged, this, &SFLViewLoadModel::enableFaceCulling);
}

void SFLViewLoadModel::loadFile()
{
    const char* fileTypes[] = {
        "Document files (*.obj)",
        "Document files (*.json)"
    };

    QString filepath = QFileDialog::getOpenFileName(
        this,
        "Open Document",
        QDir::homePath(),
        fileTypes[_srcType]
    );

    if (!filepath.isNull()){
        bool isLoadSuccess;
        const char *path = filepath.toStdString().c_str();
        SFLModelLoadModel *model = static_cast<SFLModelLoadModel *>(_owner);
        switch (_srcType) {
        case LoadSRCModelObj:
            isLoadSuccess = model->loadModel(path);
            break;
        case LoadSRCMeshJson:
            isLoadSuccess = model->loadMeshJson(path);
            break;
        default:
            break;
        }

        if (isLoadSuccess) {
            _labelModel->setText(QFileInfo(filepath).fileName());
        } else {
            _labelModel->setText(LABEL_TEXT_DEFAULT);
        }

        emit needRender();
    }
}

void SFLViewLoadModel::enableDrawLine(int index)
{
    SFLModelLoadModel *model = static_cast<SFLModelLoadModel *>(_owner);
    model->enableDrawLine(index != 0);

    emit needRender();
}

void SFLViewLoadModel::enableFaceCulling(int index)
{
    SFLModelLoadModel *model = static_cast<SFLModelLoadModel *>(_owner);
    model->enableFaceCulling(index != 0);

    emit needRender();
}

void SFLViewLoadModel::selectorShaderIndex(int index)
{
    SFLModelLoadModel *model = static_cast<SFLModelLoadModel *>(_owner);
    model->setAttachEffectType(index);

    emit needRender();
}

void SFLViewLoadModel::changeViewBy(int index)
{
    _srcType = LoadSRC(index);
    switch (index) {
    case LoadSRCModelObj:
        _labelInfo->setText(LABEL_TEXT_MODEL);
        break;
    case LoadSRCMeshJson:
        _labelInfo->setText(LABEL_TEXT_MESH);
        break;
    default:
        break;
    }
}
