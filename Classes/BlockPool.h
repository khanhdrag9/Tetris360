#pragma once
#include "Headers.h"

class Block;

class BlockPool
{
	BlockPool();
	static BlockPool* instance;

	list<shared_ptr<Block>> _pool;
public:
	static BlockPool* getInstance();

	int size() const;
	void collect(const shared_ptr<Block>& block);
};
