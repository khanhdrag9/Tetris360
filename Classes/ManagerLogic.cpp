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
		auto grids = _gridMap->getGirdsFont();
		for (int ig = 0; ig < grids.size(); ig++)
		{
			//check other block
			for (int ib = 0; ib < shape->_blocks.size(); ib++)
			{
				//Coord cor = shape->_blocks[ib]->_coord;
				//int left = cor.col - 1;
				//int right = cor.col + 1;
				//int bottom = cor.row - 1;
				//pos b_left = pos(bottom, left);
				//pos b_right = pos(bottom, right);
				//int bottomEdge = 0;

				//if(left < 0)listCollision.push_back(collision::LEFT);
				//else if (grid[cor.row][left])listCollision.push_back(collision::LEFT);

				//if(right > MAX_COL - 1)listCollision.push_back(collision::RIGHT);
				//else if (grid[cor.row][right])listCollision.push_back(collision::RIGHT);

				//if (b_left.row > 0 && b_left.col > 0)
				//{
				//	if (grid[b_left.row][b_left.col])listCollision.push_back(collision::BOTTOM_LEFT);
				//}
				//if (b_right.row > 0 && b_right.col < MAX_COL)
				//{
				//	if (grid[b_right.row][b_right.col])listCollision.push_back(collision::BOTTOM_RIGHT);
				//}

				//if(bottom < 0)listCollision.push_back(collision::BOTTOM);
				//else if (grid[bottom][cor.col])listCollision.push_back(collision::BOTTOM);

				////with bottom edge
				//if (cor.row == bottomEdge)listCollision.push_back(collision::BOTTOM_EDGE);
				
				auto listCollisionBlock = checkCollisionBlock(shape->_blocks[ib]);
				for(int col : listCollisionBlock)
					listCollision.push_back(col);
			}
		}
	}
	return listCollision;
}

list<int> ManagerLogic::checkCollisionBlock(const shared_ptr<Block>& block)
{
	list<int> listCollision;
	grids_font grid = _gridMap->getGirdsFont();

	pos cor = block->_coord;
	int left = cor.col - 1;
	int right = cor.col + 1;
	int bottom = cor.row - 1;
	pos b_left = pos(bottom, left);
	pos b_right = pos(bottom, right);
	int bottomEdge = 0;

	if (left < 0 && cor.row >= 0)listCollision.push_back(collision::LEFT);
	else if (cor.row >= 0 && grid[cor.row][left])listCollision.push_back(collision::LEFT);

	if (right > MAX_COL - 1 && cor.row >= 0)listCollision.push_back(collision::RIGHT);
	else if (cor.row >= 0 && grid[cor.row][right])listCollision.push_back(collision::RIGHT);

	if (b_left.row > 0 && b_left.col > 0)
	{
		if (grid[b_left.row][b_left.col])listCollision.push_back(collision::BOTTOM_LEFT);
	}
	if (b_right.row > 0 && b_right.col < MAX_COL)
	{
		if (grid[b_right.row][b_right.col])listCollision.push_back(collision::BOTTOM_RIGHT);
	}

	if (bottom < 0)listCollision.push_back(collision::BOTTOM);
	else if (grid[bottom][cor.col])listCollision.push_back(collision::BOTTOM);

	//with bottom edge
	if (cor.row == bottomEdge)listCollision.push_back(collision::BOTTOM_EDGE);

	return listCollision;
}

bool ManagerLogic::checkCollisionBottom(const shared_ptr<Block>& block)
{
	grids_font grid = _gridMap->getGirdsFont();

	pos cor = block->_coord;
	int bottom = cor.row - 1;
	int bottomEdge = 0;

	bool isCol = (bottom < 0 || cor.row == bottomEdge || grid[bottom][cor.col]);

	return isCol;
}