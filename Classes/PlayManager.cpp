#include "PlayManager.h"
#include "Defines.h"
#include <time.h>

PlayManager* PlayManager::_instance = new PlayManager();

PlayManager::PlayManager():
	_timeCountRotate(0.0f),
	_intervalRotate(0.0f),
	_statusGame(0),
	_blockIsFalling(nullptr),
	_lengthEachSquare(0.0f),
	_speedFall(SPEED_FALL_ORIGN)
{
	
}


PlayManager::~PlayManager()
{
	for (auto x : _listSquares)
		if (x) CC_SAFE_DELETE(x);
	_listSquares.clear();
	_listColumn.clear();
}

PlayManager* PlayManager::getInstance()
{
	return _instance;
}

void PlayManager::createGame()
{
	srand(time(NULL));

	_screenSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	_lengthEachSquare = _screenSize.width / NUMBER_BLOCK_ROW;

	float px = _lengthEachSquare;
	float py = 0;
	for (int i = 0; i < NUMBER_BLOCK_ROW - 1; i++)
	{
		_listColumn.push_back(Vec2(px, py));
		px += _lengthEachSquare;
	}
}

void PlayManager::update(float dt)
{
	if (_blockIsFalling)
	{
		auto newPos = _blockIsFalling->getPosition() + Vec2(0, -_speedFall);
		if (canMove(newPos) == typeCollision::BOTTOM_EDGE)
		{
			newPos.y = _blockIsFalling->getSize().height * _blockIsFalling->getRatioAnchor().y;
			_blockIsFalling->setPosition(newPos);
			_blockIsFalling = nullptr;
			createBlock();
		}
		else
		{
			_blockIsFalling->setPosition(newPos);
		}
	}

	checkCreateBlock();
}

void PlayManager::createBlock()
{
	if (_currentLayer)
	{
		Block* block = Block::create(Vec2(0, 0), Block::typeBlock::O, _lengthEachSquare);
		_blockIsFalling = block;
		_currentLayer->addChild(block);

		int ran = rand() % (_listColumn.size());
		Vec2 blockPos = Vec2(_listColumn[ran].x, _screenSize.height + block->getSize().height);
		block->setPosition(blockPos);
	}
}

bool PlayManager::checkAvaiableBlock(const Vec2& pos)
{
	
	return false;
}

bool PlayManager::checkFillRow()
{
	// TODO: Add your implementation code here.
	return false;
}

void PlayManager::checkCreateBlock()
{
	
}

int PlayManager::canMove(const cocos2d::Vec2& newPos)
{
	if (_blockIsFalling)
	{
		auto posBlockFalling = newPos;
		auto sizeBlockFalling = _blockIsFalling->getSize();
		auto ratioAnchorBlockFalling = _blockIsFalling->getRatioAnchor();

		//auto minX = sizeBlockFalling.width * ratioAnchorBlockFalling.x;
		//auto maxX = _screenSize.width - minX;
		auto minY = sizeBlockFalling.height * ratioAnchorBlockFalling.y;

		//check with bottom edge
		if (posBlockFalling.y <= minY)
		{
			return typeCollision::BOTTOM_EDGE;
		}
		//check with other square

	}
	
	return typeCollision::NONE;
}


void PlayManager::rotateBlocks()
{
	// TODO: Add your implementation code here.
}


void PlayManager::rotatePlay()
{
	// TODO: Add your implementation code here.
}


bool PlayManager::isRotatedPlay()
{
	// TODO: Add your implementation code here.
	return false;
}


bool PlayManager::isLose()
{
	// TODO: Add your implementation code here.
	return false;
}


void PlayManager::pause()
{
	// TODO: Add your implementation code here.
}


void PlayManager::reset()
{
	// TODO: Add your implementation code here.
}
