#include "Square.h"

Square::Square()
{
}


Square::~Square()
{
}


Square* Square::createSquare(const char* filePath, cocos2d::Vec2 anchor)
{
	Square* sprite = new Square();
	if (sprite && sprite->initWithFile(filePath))
	{
		sprite->setAnchorWorldPoint(anchor);
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}


Square* Square::createSquareWithNameFrame(const char* nameFrame, cocos2d::Vec2 anchor)
{
	Square* sprite = new Square();
	if (sprite && sprite->initWithSpriteFrameName(nameFrame))
	{
		sprite->setAnchorWorldPoint(anchor);
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}
