#ifndef SFLTOOLBAR_H
#define SFLTOOLBAR_H

#include <QToolBar>

class SFLToolBar: public QToolBar
{
public:
    SFLToolBar(QWidget *parent);

    void clickPlay();

private:
    bool _isPlaying;
    QAction *_actPlay;

    void setupUI();
};

#endif // SFLTOOLBAR_H
