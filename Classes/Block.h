#pragma once
#include "cocos2d.h"
#include "Square.h"

class Block :
	public cocos2d::Node
{
	void createSquares(cocos2d::Vec2* _listVec, int number);
public:
	enum typeBlock {
		O = 1,
		I,
		L,
		RL,
		T
	} typeBlock;


	Block();
	virtual ~Block();
	static Block* create(cocos2d::Vec2 position, int type, float sideLength);
	bool init(int type, float sideLength);
	void MoveBy(const cocos2d::Vec2& iPos);
	void RotateBy(float iAngle);

	CC_SYNTHESIZE(cocos2d::Vec2, _ratioAnchor, RatioAnchor);
	CC_SYNTHESIZE(cocos2d::Size, _size, Size);
	CC_SYNTHESIZE(float, _sideLength, SideLength);
	CC_SYNTHESIZE(int, _type, Type);
	CC_SYNTHESIZE(std::vector<Square*>, _listSquare, ListSquare);
};

