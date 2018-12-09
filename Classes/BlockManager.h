#pragma once
#include "Headers.h"

class BlockPool;
class Shape;

class BlockManager
{
	static unique_ptr<BlockManager> instance;

public:
	static unique_ptr<BlockManager>& getInstance();

	void releaseShape(shared_ptr<Shape>& shape);
};