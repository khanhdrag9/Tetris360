#include "BackgrourdLayer.h"

bool BackgrourdLayer::init()
{
    if(!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    
    return true;
}
