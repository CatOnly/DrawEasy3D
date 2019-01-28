#ifndef SFLVIEWLOADMODEL_H
#define SFLVIEWLOADMODEL_H

#include "../common/SFLViewAbstract.h"

class QLabel;
class QPushButton;
class SFLSelectorLayout;
class SFLViewLoadModel:public SFLViewAbstract
{
public:
    enum LoadSRC{
        LoadSRCModelObj,
        LoadSRCMeshJson
    };

    SFLViewLoadModel(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewLoadModel();

    void changeViewBy(int index) override;
    void loadFile();
    void enableDrawLine(int index);
    void enableFaceCulling(int index);
    void selectorShaderIndex(int index);

protected:
    void setupUI() override;
    void initData() override;

private:
    QLabel *_labelInfo;
    QLabel *_labelModel;
    QPushButton *_loadModelBtn;
    SFLSelectorLayout *_drawType;
    SFLSelectorLayout *_drawShader;
    SFLSelectorLayout *_faceCulling;
    LoadSRC _srcType;
};

#endif // SFLVIEWLOADMODEL_H
