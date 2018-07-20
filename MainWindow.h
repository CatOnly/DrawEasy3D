#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SFLToolBar;
class SFLViewControl;
class SFLViewRender;
class SFLModelAbstract;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    SFLViewRender  *_renderView;
    SFLViewControl *_controlView;
    SFLToolBar     *_toolBar;

    void setupUI();
    void resetCamera();
    void setCurrentModel(SFLModelAbstract *model);
};

#endif // MAINWINDOW_H
