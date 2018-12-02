#pragma once
#include "cocos2d.h"
class Square :
	public cocos2d::Sprite
{
public:
	Square();
	virtual ~Square();
	static Square* createSquare(const char* filePath, cocos2d::Vec2 pos = cocos2d::Vec2(0.f, 0.f));
	static Square* createSquareWithNameFrame(const char* nameFrame, cocos2d::Vec2 pos = cocos2d::Vec2(0.f, 0.f));

	CC_SYNTHESIZE(cocos2d::Vec2, _postionWorld, PositionWorld);
};

