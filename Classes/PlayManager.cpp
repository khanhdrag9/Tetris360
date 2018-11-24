#include "PlayManager.h"
#include "Defines.h"

PlayManager* PlayManager::_instance = new PlayManager();

PlayManager::PlayManager():
	_timeCountRotate(0.0f),
	_intervalRotate(0.0f),
	_statusGame(0),
	_blockIsFalling(nullptr)
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
	// TODO: Add your implementation code here.
}


void PlayManager::createBlock()
{
	Block* test = Block::create(Vec2(400, 200), Block::typeBlock::O, 0);
	if (_currentLayer)
	{
		_currentLayer->addChild(test);
	}
}


bool PlayManager::checkFillRow()
{
	// TODO: Add your implementation code here.
	return false;
}


void PlayManager::checkCreateBlock()
{
	// TODO: Add your implementation code here.
}


bool PlayManager::canMove()
{
	// TODO: Add your implementation code here.
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
