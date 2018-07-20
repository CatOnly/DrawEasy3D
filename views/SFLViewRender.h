#ifndef SFLVIEWRENDER_H
#define SFLVIEWRENDER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class SFLViewRender: public QOpenGLWidget,
                     public QOpenGLFunctions
{
public:
    SFLViewRender(QWidget *parent);

protected:
    void paintGL() override;
    void initializeGL() override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SFLVIEWRENDER_H
