#include "PlayManager.h"
#include "Defines.h"
#include <time.h>

PlayManager* PlayManager::_instance = new PlayManager();

PlayManager::PlayManager():
	_timeCountRotate(0.0f),
	_intervalRotate(0.0f),
	_statusGame(0),
	_blockIsFalling(nullptr),
	_lengthEachSquare(0.0f)
{
	
}


PlayManager::~PlayManager()
{
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
		_blockIsFalling->MoveBy(Vec2(0, -2.f));
	}

	checkCreateBlock();
}

void PlayManager::createBlock()
{
	Block* block= Block::create(Vec2(0, 0), Block::typeBlock::O, _lengthEachSquare);
	if (_currentLayer)
	{
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


bool PlayManager::canMove()
{
	
	return false;
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
