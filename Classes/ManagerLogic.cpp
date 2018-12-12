#include "ManagerLogic.h"
#include "GridMap.h"
#include "Shape.h"

void ManagerLogic::setGridMap(const shared_ptr<GridMap>& gridMap)
{
	_gridMap = gridMap;
}

list<int> ManagerLogic::checkCollision(const shared_ptr<Shape>& shape)
{
	list<int> listCollision;
	if (shape)
	{
		auto grid = _gridMap->getGirdsFont();
		for (int ig = 0; ig < grid.size(); ig++)
		{
			//check other block
			for (int ib = 0; ib < shape->_blocks.size(); ib++)
			{
				Coord cor = shape->_blocks[ib]->_coord;
				int left = cor.cy - 1;
				int right = cor.cy + 1;
				int down = cor.cx - 1;
				int bottomEdge = 0;

				if(left < 0)listCollision.push_back(collision::LEFT);
				else if (grid[cor.cx][left])listCollision.push_back(collision::LEFT);

				if(right > MAX_COL - 1)listCollision.push_back(collision::RIGHT);
				else if (grid[cor.cx][right])listCollision.push_back(collision::RIGHT);

				if(down < 0)listCollision.push_back(collision::BOTTOM);
				else if (grid[down][cor.cy])listCollision.push_back(collision::BOTTOM);

				//with bottom edge
				if (cor.cx == bottomEdge)listCollision.push_back(collision::BOTTOM_EDGE);
			}
		}
	}
	return listCollision;
}