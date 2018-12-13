#include "BlockManager.h"
#include "BlockPool.h"
#include "Shape.h"

unique_ptr<BlockManager> BlockManager::instance = make_unique<BlockManager>();

unique_ptr<BlockManager>& BlockManager::getInstance()
{
	return instance;
}

void BlockManager::releaseShape(shared_ptr<Shape>& shape)
{
	if (shape)
	{
		for (auto& block : shape->_blocks)
		{
			BlockPool::getInstance()->collect(block);
		}

		shape->_node->autorelease();
		shape = nullptr;
	}
}
