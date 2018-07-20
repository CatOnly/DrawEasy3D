#ifndef SFLTOOLBAR_H
#define SFLTOOLBAR_H

#include <QToolBar>
#include <QToolButton>
#include "../common/SFLModelAbstract.h"

using namespace std;

class SFLToolBar: public QToolBar
{
public:
    SFLToolBar(QWidget *parent);
    ~SFLToolBar();

    void clickPlay();
    vector<SFLModelAbstract *> *renderObjects();

private:
    bool _isPlaying;
    QAction *_actPlay = nullptr;
    vector<SFLModelAbstract *> *_renderObjects = nullptr;

    void initData();
    void setupUI();
};

#endif // SFLTOOLBAR_H
