#pragma once
#include "Headers.h"

class GridMap;
class Shape;
class Block;

class ManagerLogic : public Singleton<ManagerLogic>
{

	shared_ptr<GridMap> _gridMap;

public:
	enum collision
	{
		NONE,
		BOTTOM_EDGE,
		BOTTOM,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		LEFT,
		RIGHT
	};

	void setGridMap(const shared_ptr<GridMap>& gridMap);
	list<int> checkCollision(const shared_ptr<Shape>& shape);
	list<int> checkCollisionBlock(const shared_ptr<Block>& block);
	bool checkCollisionBottom(const shared_ptr<Block>& block);

};