#include "ManagerLogic.h"

ManagerLogic::ManagerLogic():
    _score(0),
    _label(nullptr)
{
}

void ManagerLogic::initScore(Layer* layer, const Vec2& pos, const float& size, const Color3B &color)
{
    _label = Label::createWithTTF(std::to_string(_score), FONT_ARIAL, size);
    _label->setPosition(pos);
    _label->setColor(color);
    layer->addChild(_label);
}

void ManagerLogic::increScore(const int &incre)
{
    _score++;
    if(_label)
        _label->setString(std::to_string(_score));
}
