#include "BlockPool.h"

BlockPool* BlockPool::instance = new BlockPool();

BlockPool* BlockPool::getInstance()
{
	return instance;
}

BlockPool::BlockPool()
{
}
 
int BlockPool::size() const
{
	return _pool.size();
}

void BlockPool::collect(const shared_ptr<Block>& block)
{
	_pool.emplace_back(block);
}