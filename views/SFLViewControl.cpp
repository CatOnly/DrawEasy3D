#include "SFLViewControl.h"
#include "../common/SFLModelAbstract.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>

SFLViewControl::SFLViewControl(QWidget *parent):QDockWidget(parent)
{
    _titleLabel = new QLabel("标题");
    _containerLayout = new QVBoxLayout();
    _currentWidget = nullptr;

    setupUI();
}

void SFLViewControl::setupUI()
{
    setFixedWidth(300);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    QLabel *title = new QLabel("E-mail: l.tat@qq.com");
    setTitleBarWidget(title);
    title->setTextFormat(Qt::PlainText);
    title->setAlignment(Qt::AlignRight);
    title->setTextInteractionFlags(Qt::TextSelectableByMouse);
    title->setContentsMargins(20, 5, 20, 0);

    _titleLabel->setTextFormat(Qt::PlainText);
    _titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
    _titleLabel->setContentsMargins(10, 0, 20, 0);
    _containerLayout->addWidget(_titleLabel);

    QComboBox *kind = new QComboBox();
    QGridLayout *topLayout = new QGridLayout();
    _containerLayout->addLayout(topLayout);
    topLayout->setColumnStretch(0, 1);
    topLayout->setColumnStretch(1, 6);
    topLayout->addWidget(new QLabel("类型"), 0, 0);
    topLayout->addWidget(kind, 0, 1);
    topLayout->setContentsMargins(10, 0, 10, 0);

    _containerLayout->addWidget(_currentWidget);
    _containerLayout->addStretch();

    QPushButton *resetBtn = new QPushButton("重 置 相 机",this);
    _containerLayout->addWidget(resetBtn);

    QWidget *container = new QWidget(this);
    container->setLayout(_containerLayout);
    QDockWidget::setWidget(container);

    connect(resetBtn, &QPushButton::clicked, this, &SFLViewControl::resetCameraBtnClicked);
}

void SFLViewControl::setDelegate(SFLModelAbstract *delegate)
{
    if (delegate != nullptr && _delegate != delegate){
        _delegate = delegate;
        _titleLabel->setText(delegate->toolBtn()->text());
        QWidget *lastWidget = _currentWidget;
        _currentWidget = delegate->view();
        if (lastWidget != nullptr){
            _containerLayout->removeWidget(lastWidget);
            lastWidget->setParent(nullptr);
        }
        _containerLayout->insertWidget(2, _currentWidget);
    }
}

void SFLViewControl::resetCameraBtnClicked()
{
    emit resetCamera();
}
