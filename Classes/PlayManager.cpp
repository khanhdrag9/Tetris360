#include "PlayManager.h"
#include "Defines.h"
#include <time.h>

PlayManager* PlayManager::_instance = new PlayManager();

PlayManager::PlayManager() :
	_timeCountRotate(0.0f),
	_intervalRotate(0.0f),
	_statusGame(0),
	_blockIsFalling(nullptr),
	_lengthEachSquare(0.0f),
	_speedFall(SPEED_FALL_ORIGN),
	_currentPosIndex(-1),
	_beginTouch(Vec2(-1.f, -1.f)),
	_previousTouchMove(Vec2(-1.f, -1.f)),
	_directionBlockMove(0),
	_currentLayer(nullptr)
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
		moveBlockFalling(_directionBlockMove);

		auto sizeBlockFalling = _blockIsFalling->getSize();
		auto ratioAnchorBlockFalling = _blockIsFalling->getRatioAnchor();

		auto newPos = _blockIsFalling->getPosition() + Vec2(0, -_speedFall);
		//int checkMove = canMove(newPos, sizeBlockFalling, ratioAnchorBlockFalling);
		int checkMove = canMove(newPos);

		if (checkMove == typeCollision::BOTTOM_EDGE)
		{
			newPos.y = sizeBlockFalling.height * ratioAnchorBlockFalling.y;

			int checkMoveEdge = canMove(Vec2(newPos.x, newPos.y * 2));
			if (checkMoveEdge == typeCollision::RIGHT_EDGE)
			{
				_blockIsFalling->stopAllActionsByTag(typeMove::MOVE);
				newPos.x = _listColumn[NUMBER_BLOCK_ROW - 2].x;
			}
			else if (checkMoveEdge == typeCollision::LEFT_EDGE)
			{
				_blockIsFalling->stopAllActionsByTag(typeMove::MOVE);
				newPos.x = _listColumn[0].x;
			}

			_blockIsFalling->setPosition(newPos);
			putBlockToList();
			createBlock();
		}
		else if (checkMove == typeCollision::RIGHT_EDGE)
		{
			newPos.x = _listColumn[NUMBER_BLOCK_ROW - 2].x;
			_blockIsFalling->setPosition(newPos);
		}
		else if (checkMove == typeCollision::LEFT_EDGE)
		{
			newPos.x = _listColumn[0].x;
			_blockIsFalling->setPosition(newPos);
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

		_currentPosIndex = rand() % (_listColumn.size());

		Vec2 blockPos = Vec2(_listColumn[_currentPosIndex].x, _screenSize.height + block->getSize().height);
		block->setPosition(blockPos);
	}
}

void PlayManager::putBlockToList()
{
	for (auto x : _blockIsFalling->getListSquare())
	{	
		auto pos = _blockIsFalling->convertToWorldSpace(x->getPosition());
		
		_listSquares.push_back(x);
		x->setPositionWorld(pos);
	}

	for (int i = _listSquares.size() - 4; i < _listSquares.size(); i++)
	{
		auto pos = _listSquares[i]->getPosition();
		CCLOG("%f - %f", pos.x, pos.y);
	}
	_blockIsFalling = nullptr;
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

int PlayManager::canMove(const cocos2d::Vec2& newPos, const cocos2d::Size& sizeBlock, const cocos2d::Vec2& ratioAnchor)
{
	if (_blockIsFalling)
	{
		auto posBlockFalling = newPos;
		Size psizeBlock;
		Vec2 pratioAnchor;

		if (sizeBlock.width == 0.f && sizeBlock.height == 0.f)
			psizeBlock = _blockIsFalling->getSize();
		else
			psizeBlock = sizeBlock;

		if (ratioAnchor == Vec2(0.f, 0.f))
			pratioAnchor = _blockIsFalling->getRatioAnchor();
		else
			pratioAnchor = ratioAnchor;

		auto minX = psizeBlock.width * pratioAnchor.x;
		auto maxX = _screenSize.width - minX;
		auto minY = psizeBlock.height * pratioAnchor.y;

		//check with edges
		if (posBlockFalling.y <= minY)
		{
			return typeCollision::BOTTOM_EDGE;
		}
		else if(posBlockFalling.x >= maxX)
		{
			return typeCollision::RIGHT_EDGE;
		}
		else if (posBlockFalling.x <= minX)
		{
			return typeCollision::LEFT_EDGE;
		}
		//check with other square
		else
		{
			for (auto squares : _listSquares)
			{

			}
		}
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

void PlayManager::moveBlockFalling(int typeMove, int number)
{
	if (_blockIsFalling->getNumberOfRunningActionsByTag(typeMove::MOVE) <= 0)
	{
		Action* action;
		switch (typeMove)
		{
		case typeMove::LEFT:
			action = MoveBy::create(TIME_MOVE, Vec2(-_lengthEachSquare, 0.f));
			//_blockIsFalling->setPositionX(_blockIsFalling->getPositionX() - 5);
			break;
		case typeMove::RIGHT:
			action = MoveBy::create(TIME_MOVE, Vec2(_lengthEachSquare, 0.f));
		//	_blockIsFalling->setPositionX(_blockIsFalling->getPositionX() + 5);
			break;
		case typeMove::DOWN:
			break;
		default:
			action = nullptr;
			break;
		}

		if (action)
		{
			action->setTag(typeMove::MOVE);
			_blockIsFalling->runAction(action);
		}
	}
}