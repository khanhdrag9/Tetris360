#include "BlockPool.h"
#include "Block.h"

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
	return (int)_pool.size();
}

void BlockPool::collect(const shared_ptr<Block>& block)
{
	_pool.emplace_back(block);
}

void BlockPool::refresh()
{
    CCLOG("size pool before %d", (int)_pool.size());
    for(int i =0; i < _pool.size();)
    {
        shared_ptr<Block>& b = _pool[i];
        if(b == nullptr || b->_sprite == nullptr || b->_sprite == NULL)
        {
            _pool.erase(_pool.begin() + i);
        }
        else
        {
            ++i;
        }
    }
    CCLOG("size pool after %d", (int)_pool.size());
}
