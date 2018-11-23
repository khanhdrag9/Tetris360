#pragma once
#include "cocos2d.h"
class Square :
	public cocos2d::Sprite
{
public:
	Square();
	virtual ~Square();
	static Square* createSquare();
	static Square* createSquareWithNameFrame();

	CC_SYNTHESIZE(cocos2d::Vec2, _anchorWorldPoint, AnchorWorldPoint);
};

