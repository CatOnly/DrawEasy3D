#include "MainWindow.h"
#include "./views/SFLViewRender.h"
#include "./views/SFLViewControl.h"
#include "./views/SFLToolBar.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _renderView  = new SFLViewRender(this);
    _controlView = new SFLViewControl(this);
    _toolBar = new SFLToolBar(this);

    setupUI();
    connect((SFLViewControl *)_controlView, &SFLViewControl::resetCamera, this, &MainWindow::resetCamera);
    auto renderObjects = _toolBar->renderObjects();
    for (auto iter = renderObjects->begin(); iter != renderObjects->end(); ++iter){
        SFLModelAbstract *model = *iter;
        connect(model->toolBtn(), &SFLToolBtn::clicked, this, &MainWindow::setCurrentModel);
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI()
{
    setCentralWidget(_renderView);
    addToolBar(Qt::TopToolBarArea, _toolBar);
    addDockWidget(Qt::RightDockWidgetArea, _controlView);

    QRect deskRect = QApplication::desktop()->availableGeometry();
    setGeometry((deskRect.width() - width()) * 0.5, (deskRect.height() - height()) * 0.5, width(), height());
    setFixedSize(_renderView->width() + _controlView->width(), _renderView->height());
    setWindowTitle("Keep Reading , Keep Writing , Keep Coding");
}

void MainWindow::resetCamera()
{
    qDebug() << __func__;
}

void MainWindow::setCurrentModel(SFLModelAbstract *model)
{
    if (model != nullptr){
        _controlView->setDelegate(model);
        _renderView->setDelegate(model);
        SFLModelAbstract::currentUseWidget = model;
    }
}
