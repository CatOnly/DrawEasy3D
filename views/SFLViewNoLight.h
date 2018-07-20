#ifndef SFLVIEWNOLIGHT_H
#define SFLVIEWNOLIGHT_H

#include <QWidget>

class SFLViewNoLight : public QWidget
{
    Q_OBJECT
public:
    explicit SFLViewNoLight(QWidget *parent = nullptr);
    ~SFLViewNoLight();

signals:

public slots:


protected:
    void setupUI();
};

#endif // SFLVIEWNOLIGHT_H
