#pragma once
#include "cocos2d.h"
#include "Square.h"

class Block :
	public cocos2d::Node
{
public:
	Block();
	virtual ~Block();
	static Block* create(int type);
	void MoveBy(const cocos2d::Vec2& iPos);
	void RotateBy(float iAngle);

	CC_SYNTHESIZE(float, _sideLength, SideLength);
	CC_SYNTHESIZE(int, _type, Type);
	CC_SYNTHESIZE(std::vector<Square*>, _listSquare, ListSquare);
};

