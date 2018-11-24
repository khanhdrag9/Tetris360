#pragma once
#include "cocos2d.h"
class Square :
	public cocos2d::Sprite
{
public:
	Square();
	virtual ~Square();
	static Square* createSquare(const char* filePath, cocos2d::Vec2 anchor = cocos2d::Vec2::ANCHOR_MIDDLE);
	static Square* createSquareWithNameFrame(const char* nameFrame, cocos2d::Vec2 anchor = cocos2d::Vec2::ANCHOR_MIDDLE);

	CC_SYNTHESIZE(cocos2d::Vec2, _anchorWorldPoint, AnchorWorldPoint);
};

