#include "SFLViewControl.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

SFLViewControl::SFLViewControl(QWidget *parent):QDockWidget(parent)
{
    _currentWidget = nullptr;
    _titleLabel = new QLabel("标题");
    _containerLayout = new QVBoxLayout();

    setupUI();
}

void SFLViewControl::setupUI()
{
    setFixedWidth(300);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    QLabel *title = new QLabel("E-mail: l.tat@qq.com");
    title->setTextFormat(Qt::PlainText);
    title->setAlignment(Qt::AlignRight);
    title->setTextInteractionFlags(Qt::TextSelectableByMouse);
    title->setContentsMargins(20, 5, 20, 0);
    setTitleBarWidget(title);

    _titleLabel->setTextFormat(Qt::PlainText);
    _titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
    _titleLabel->setContentsMargins(10, 0, 20, 0);

    QPushButton *resetBtn = new QPushButton("重 置 相 机",this);

    _containerLayout->addWidget(_titleLabel);
    _containerLayout->addStretch();
    _containerLayout->addWidget(resetBtn);

    QWidget *container = new QWidget(this);
    container->setLayout(_containerLayout);
    QDockWidget::setWidget(container);
}

void SFLViewControl::setWidget(const QString title, QWidget *w)
{
    _titleLabel->setText(title);
    if (w != nullptr){
        if (_currentWidget != nullptr){
            _containerLayout->removeWidget(_currentWidget);
        }
        _containerLayout->insertWidget(0, w);
        _currentWidget = w;
    }
}
