#pragma once
#include "Headers.h"

class GridMap;
class Shape;

class ManagerLogic : public Singleton<ManagerLogic>
{

	shared_ptr<GridMap> _gridMap;

public:
	enum collision
	{
		NONE,
		BOTTOM_EDGE,
		BOTTOM,
		LEFT,
		RIGHT
	};

	void setGridMap(const shared_ptr<GridMap>& gridMap);
	list<int> checkCollision(const shared_ptr<Shape>& shape);

};