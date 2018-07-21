#ifndef SFLVEC3EDITOR_H
#define SFLVEC3EDITOR_H

#include <QHBoxLayout>

class QLabel;
class QDoubleSpinBox;
class SFLVec3Editor: public QHBoxLayout
{
    Q_OBJECT

public:
    enum SFLVec3Type{
        vec3Color,
        vec3Position
    };

    explicit SFLVec3Editor(const QString title, SFLVec3Type type = vec3Color, QWidget *parent = nullptr);
    ~SFLVec3Editor();

    void setVec3Vals(double x, double y, double z);
    void setSuffix(QString sufffix);

signals:
    void changeValue(double x, double y, double z);

public slots:
    void onValueChangedX(double x);
    void onValueChangedY(double y);
    void onValueChangedZ(double z);

private:
    QLabel *_titleLabel;
    SFLVec3Type _type;
    QDoubleSpinBox* _widgetX;
    QDoubleSpinBox* _widgetY;
    QDoubleSpinBox* _widgetZ;

    void setupUI();

    QDoubleSpinBox* widgetPosition();
    QDoubleSpinBox* widgetColor();
};

#endif // SFLVEC3EDITOR_H
