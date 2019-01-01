#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void BackgroundLayer::initSoild(const Rect& boardRect)
{
//    Size sc = Director::getInstance()->getVisibleSize();
//    
//    Sprite* bg = Sprite::create(BGPLAY_PATH);
//    bg->setPosition(sc * 0.5f);
//    this->addChild(bg);
}
