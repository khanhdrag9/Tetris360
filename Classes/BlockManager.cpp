#include "BlockManager.h"
#include "BlockPool.h"
#include "Shape.h"
#include "GridMap.h"

unique_ptr<BlockManager> BlockManager::instance = make_unique<BlockManager>();

unique_ptr<BlockManager>& BlockManager::getInstance()
{
	return instance;
}

void BlockManager::init(const shared_ptr<GridMap> gridMap)
{
	_gridMap = gridMap;
}

void BlockManager::releaseShape(shared_ptr<Shape>& shape)
{
	if (shape)
	{
		for (auto& block : shape->_blocks)
		{
			BlockPool::getInstance()->collect(block);
			block = nullptr;
		}
	}
}

vector<shared_ptr<Block>>& BlockManager::getBlockPool()
{
    return BlockPool::getInstance()->_pool;
}

void BlockManager::moveBlock(shared_ptr<Block> block, const pos& newPos)
{
	pos oldPos = pos(block->_coord);
	
	//set new pos
	Vec2 newRealPos = _gridMap->getGirdsPosition()[newPos.row][newPos.col];
	block->_coord = pos(newPos);
//    block->_sprite->setPosition(newRealPos);
    block->_sprite->stopAllActions();
    block->_sprite->runAction(MoveTo::create(0.15f, newRealPos)->clone());
    
	_gridMap->getGirdsFont()[newPos.row][newPos.col] = block;
	_gridMap->getGirdsBack()[newPos.row][newPos.col] = true;

	//handle old pos on gird
	_gridMap->getGirdsFont()[oldPos.row][oldPos.col] = nullptr;
	_gridMap->getGirdsBack()[oldPos.row][oldPos.col] = false;
}

void BlockManager::refreshPool()
{
    BlockPool::getInstance()->refresh();
}
