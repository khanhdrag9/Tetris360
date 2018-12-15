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

void BlockManager::moveBlock(shared_ptr<Block>& block, const pos& newPos)
{
	Coord oldPos = Coord(block->_coord);
	
	//set new pos
	Vec2 newRealPos = _gridMap->getGirdsPosition()[newPos.row][newPos.col];
	block->_coord = Coord(newPos.row, newPos.col);
	block->_sprite->setPosition(newRealPos);

	_gridMap->getGirdsFont()[newPos.row][newPos.col] = block;
	_gridMap->getGirdsBack()[newPos.row][newPos.col] = true;

	//handle old pos on gird
	_gridMap->getGirdsFont()[oldPos.cx][oldPos.cy] = nullptr;
	_gridMap->getGirdsBack()[oldPos.cx][oldPos.cy] = false;
}
