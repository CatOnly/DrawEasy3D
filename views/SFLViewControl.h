#ifndef SFLVIEWCONTROL_H
#define SFLVIEWCONTROL_H

#include <QDockWidget>

class QLabel;
class QVBoxLayout;
class SFLModelAbstract;
class SFLViewControl: public QDockWidget
{
    Q_OBJECT

public:
    SFLViewControl(QWidget *parent = Q_NULLPTR);
    void setDelegate(SFLModelAbstract *delegate);

signals:
    void resetCamera();

public slots:
    void resetCameraBtnClicked();

private:
    QLabel *_titleLabel;
    QWidget *_currentWidget;
    QVBoxLayout *_containerLayout;

    SFLModelAbstract *_delegate = nullptr;

    void setupUI();
};

#endif // SFLVIEWCONTROL_H
