#pragma once
#include "Headers.h"

class BackgroundLayer : public Layer
{
    bool init() override;
    
public:
    CREATE_FUNC(BackgroundLayer);
    void initSoild(const Rect& boardRect);
};
