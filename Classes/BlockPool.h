#pragma once
#include "Headers.h"

class Block;

class BlockPool
{
	friend class BlockManager;

	BlockPool();
	static BlockPool* instance;

	list<shared_ptr<Block>> _pool;

	int size() const;
	void collect(const shared_ptr<Block>& block);
public:
	static BlockPool* getInstance();
};
