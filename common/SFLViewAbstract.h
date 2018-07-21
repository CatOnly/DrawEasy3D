#ifndef SFLVIEWABSTRACT_H
#define SFLVIEWABSTRACT_H

#include <QWidget>

class SFLModelAbstract;
class SFLViewAbstract:public QWidget
{
public:
    explicit SFLViewAbstract(SFLModelAbstract *owner, QWidget *parent = nullptr):QWidget(parent) {
        _owner = owner;
    }

    virtual void changeViewBy(int index) = 0;

    QStringList types(){
        return _types;
    }

protected:
    QStringList _types;
    SFLModelAbstract *_owner;
};
#endif // SFLVIEWABSTRACT_H
