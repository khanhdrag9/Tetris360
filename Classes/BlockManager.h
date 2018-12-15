#pragma once
#include "Headers.h"

class Block;
class BlockPool;
class Shape;
class GridMap;

class BlockManager
{
	static unique_ptr<BlockManager> instance;

	shared_ptr<GridMap> _gridMap;
public:
	static unique_ptr<BlockManager>& getInstance();

	void init(const shared_ptr<GridMap> gridMap);
	void releaseShape(shared_ptr<Shape>& shape);
	void moveBlock(shared_ptr<Block>& block ,const pos& newPos);

};