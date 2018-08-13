#ifndef SFLVIEWLOADMODEL_H
#define SFLVIEWLOADMODEL_H

#include "../common/SFLViewAbstract.h"

class QLabel;
class QPushButton;
class SFLViewLoadModel:public SFLViewAbstract
{
public:
    SFLViewLoadModel(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewLoadModel();

    void changeViewBy(int index) override;
    void loadModel();

protected:
    QLabel *_labelModel;
    QPushButton *_loadModelBtn;

    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWLOADMODEL_H
