#pragma once
#include "Headers.h"

class BackgrourdLayer : public LayerColor
{
    bool init() override;
    
public:
    CREATE_FUNC(BackgrourdLayer);
};
