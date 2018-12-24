#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
    if(!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    
    return true;
}
