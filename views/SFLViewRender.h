#ifndef SFLVIEWRENDER_H
#define SFLVIEWRENDER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class SFLModelAbstract;
class SFLViewRender: public QOpenGLWidget,
                     public QOpenGLFunctions
{
public:
    SFLViewRender(QWidget *parent);
    void setDelegate(SFLModelAbstract *delegate);

protected:
    void paintGL() override;
    void initializeGL() override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    QPoint _currentPoint;
    SFLModelAbstract *_delegate = nullptr;
};

#endif // SFLVIEWRENDER_H
