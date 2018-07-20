#include "SFLToolBar.h"
#include <QMenu>
#include <QToolButton>

#define ICON_PLAY ":/play.png"
#define ICON_PAUSE ":/pause.png"
#define ICON_PLAY_TXT "播放"
#define ICON_PAUSE_TXT "停止"

SFLToolBar::SFLToolBar(QWidget *parent):QToolBar(parent)
{
    _isPlaying = false;
    _actPlay = addAction(QIcon(QString(ICON_PLAY)), QString(ICON_PLAY_TXT), this, &SFLToolBar::clickPlay);

    setupUI();
}

void SFLToolBar::setupUI()
{
    setMovable(false);
    setFloatable(false);
    setIconSize(QSize(18, 18));
    setToolButtonStyle(Qt::ToolButtonIconOnly);

    QMenu *menu = new QMenu(this);
    menu->setTearOffEnabled(false);
    menu->addAction("颜色");
    menu->addAction("冯氏光照模型（Phone Illumination）");

    QToolButton *btn = new QToolButton(this);
    btn->setText("光照");
    btn->setArrowType(Qt::NoArrow);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setMenu(menu);

    addWidget(btn);
}

void SFLToolBar::clickPlay()
{
    _isPlaying = !_isPlaying;

    _actPlay->setIcon(QIcon(QString(_isPlaying ? ICON_PAUSE :ICON_PLAY )));
    _actPlay->setIconText(QString(_isPlaying ? ICON_PAUSE_TXT : ICON_PLAY_TXT));
}
