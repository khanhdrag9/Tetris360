#include "ShapeAction.h"
#include "Shape.h"
#include "GridMap.h"

ShapeAction::ShapeAction(const shared_ptr<GridMap>& grid) :
	_gridMap(grid)
{
}

Fall::Fall(const shared_ptr<GridMap>& grid) : ShapeAction(grid){}

bool Fall::run(shared_ptr<Shape>& shape)
{
	if (shape && shape->_position != pos_null &&_gridMap)
	{	
		list<pos> posList;

		for (int i = 0; i < shape->_blocks.size(); i++)
		{
			int nRow = shape->_blocks[i]->_coord.row - 1;
			int nCol = shape->_blocks[i]->_coord.col;

			if (check::checkAvaiablePos(_gridMap, nRow, nCol))posList.push_back(pos(nRow, nCol));
			else return false;
		}

		check::pushNewPosToBlock4(shape, posList);

		pos newPos = pos(shape->_position.row - 1, shape->_position.col);
		shape->setPosition(_gridMap, newPos);

		return true;
	}
	else
	{
		return false;
	}
}

VerticalSlide::VerticalSlide(const shared_ptr<GridMap>& grid, const int& direct) :
	ShapeAction(grid),
	_direction(direct)
{
}

bool VerticalSlide::run(shared_ptr<Shape>& shape)
{
	if (shape && shape->_position != pos_null && _gridMap)
	{
		list<pos> posList;

		for (int i = 0; i < shape->_blocks.size(); i++)
		{
			int nRow = shape->_blocks[i]->_coord.row;
			int nCol = shape->_blocks[i]->_coord.col;
			if (_direction == direction::LEFT) nCol -= 1;
			if (_direction == direction::RIGHT) nCol += 1;
				
			if (check::checkAvaiablePos(_gridMap, nRow, nCol))posList.push_back(pos(nRow, nCol));
			else return false;
		}

		check::pushNewPosToBlock4(shape, posList);

		pos newPos = pos(shape->_position.row, shape->_position.col);
		if (_direction == direction::LEFT) newPos.col -= 1;
		if (_direction == direction::RIGHT) newPos.col += 1;
		
		shape->setPosition(_gridMap, newPos);
	}
	else
	{
		return false;
	}
}