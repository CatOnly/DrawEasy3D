#ifndef SFLVIEWCONTROL_H
#define SFLVIEWCONTROL_H

#include <QDockWidget>

class QLabel;
class QVBoxLayout;
class SFLViewControl: public QDockWidget
{
    Q_OBJECT

public:
    SFLViewControl(QWidget *parent = Q_NULLPTR);
    void setWidget(const QString title, QWidget *w);

private:
    QLabel *_titleLabel;
    QWidget *_currentWidget;
    QVBoxLayout *_containerLayout;

    void setupUI();
};

#endif // SFLVIEWCONTROL_H
