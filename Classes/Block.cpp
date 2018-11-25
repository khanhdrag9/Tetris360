#include "Block.h"
#include "Defines.h"

USING_NS_CC;

Block::Block()
{
	
}


Block::~Block()
{
	/*for (auto x : _listSquare)
		if (x)
			CC_SAFE_DELETE(x);
	_listSquare.clear();*/
}


Block* Block::create(cocos2d::Vec2 position, int type, float sideLength)
{
	Block* block = new (std::nothrow)Block();
	if (block && block->init(type, sideLength))
	{
		block->setPosition(position);
		block->autorelease();
		return block;
	}
	CC_SAFE_DELETE(block);
	return nullptr;
}

bool Block::init(int type, float sideLength)
{
	if (!Node::init())
		return false;

	_sideLength = sideLength;
	_type = type;

	int number = 0;
	cocos2d::Vec2* listVec = nullptr;

	switch (_type)
	{
	case typeBlock::O:
		number = 4;
		listVec = new cocos2d::Vec2[number]{
			cocos2d::Vec2(-1.f, -1.f),
			cocos2d::Vec2(1.f, -1.f),
			cocos2d::Vec2(1.f, 1.f),
			cocos2d::Vec2(-1.f, 1.f)
		};

		_size = Size(sideLength*2.f, sideLength*2.f);
		_ratioAnchor = Vec2(0.5f, 0.5f);
		break;
	case typeBlock::I:
		break;
	case typeBlock::L:
		break;
	case typeBlock::RL:
		break;
	case typeBlock::T:
		break;
	default:
		break;
	}
	createSquares(listVec, number);

	return true;
}

void Block::createSquares(cocos2d::Vec2* _listVec, int number)
{
	for (int i = 0; i < number; i++)
	{
		Square* square = Square::createSquare(SQUARE_FILE_PATH);

		auto newAnchor = Vec2(square->getAnchorPoint() - _listVec[i] / 2.f);
		square->setAnchorPoint(newAnchor);
		square->setPosition(0, 0);
		square->setScale(_sideLength / (float)square->getBoundingBox().size.width);

		_listSquare.push_back(square);
		this->addChild(square);
	}

	delete[]_listVec;
}

void Block::MoveBy(const cocos2d::Vec2& iPos)
{
	this->setPosition(this->getPosition() + iPos);
}


void Block::RotateBy(float iAngle)
{
	this->setRotation(this->getRotation() + iAngle);
}
