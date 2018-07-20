#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget     *_renderView;
    QDockWidget *_controlView;
    QToolBar    *_toolBar;

    void setupUI();
};

#endif // MAINWINDOW_H
