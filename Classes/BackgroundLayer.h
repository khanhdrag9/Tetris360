#pragma once
#include "Headers.h"

class BackgroundLayer : public LayerColor
{
    bool init() override;
    
public:
    CREATE_FUNC(BackgroundLayer);
};
