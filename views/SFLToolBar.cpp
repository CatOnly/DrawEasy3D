#include "SFLToolBar.h"
#include <vector>
#include "../models/SFLModelNoLight.h"
#include "../models/SFLModelLight.h"
#include "../models/SFLModelMapping.h"
#include "../models/SFLModelLoadModel.h"
#include "../models/SFLModelPostprocessing.h"

#define ICON_PLAY ":/play.png"
#define ICON_PAUSE ":/pause.png"
#define ICON_PLAY_TXT "播放"
#define ICON_PAUSE_TXT "停止"

SFLToolBar::SFLToolBar(QWidget *parent):QToolBar(parent)
{
    _isPlaying = false;
//    _actPlay = addAction(QIcon(QString(ICON_PLAY)), QString(ICON_PLAY_TXT), this, &SFLToolBar::clickPlay);
    _renderObjects = new vector<SFLModelAbstract *>();

    initData();
    setupUI();
}

SFLToolBar::~SFLToolBar(){
    for(vector<SFLModelAbstract *>::iterator iter = _renderObjects->begin(); iter != _renderObjects->end(); ++iter){
        SFLModelAbstract *pointer = *iter;
        DELETE_SAFE(pointer)
    }
    DELETE_SAFE(_renderObjects)
}

void SFLToolBar::initData()
{
//    _renderObjects->push_back(new SFLModelNoLight());
//    _renderObjects->push_back(new SFLModelLight());
    _renderObjects->push_back(new SFLModelMapping());
//    _renderObjects->push_back(new SFLModelLoadModel());
//    _renderObjects->push_back(new SFLModelPostprocessing());
}

void SFLToolBar::setupUI()
{
    setMovable(false);
    setFloatable(false);
    setIconSize(QSize(18, 18));
    setToolButtonStyle(Qt::ToolButtonIconOnly);

    for (auto iter = _renderObjects->begin(); iter != _renderObjects->end(); ++iter) {
        addWidget((*iter)->toolBtn());
    }
}

void SFLToolBar::clickPlay()
{
    _isPlaying = !_isPlaying;

    _actPlay->setIcon(QIcon(QString(_isPlaying ? ICON_PAUSE :ICON_PLAY )));
    _actPlay->setIconText(QString(_isPlaying ? ICON_PAUSE_TXT : ICON_PLAY_TXT));
}
vector<SFLModelAbstract *> * SFLToolBar::renderObjects(){
    return _renderObjects;
}
