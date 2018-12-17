#include "ShapeAction.h"
#include "Shape.h"
#include "GridMap.h"

ShapeAction::ShapeAction(const shared_ptr<GridMap>& grid) :
	_gridMap(grid)
{
}

Fall::Fall(const shared_ptr<GridMap>& grid, const int& speed) :
	ShapeAction(grid),
	_speed(speed)
{
}

int Fall::run(shared_ptr<Shape>& shape)
{
	if (shape && shape->_position != pos_null &&_gridMap)
	{	
		if (_speed == 0)return true;

		list<pos> posList;

		for (int i = 0; i < shape->_blocks.size(); i++)
		{
			int nRow = shape->_blocks[i]->_coord.row - _speed;
			int nCol = shape->_blocks[i]->_coord.col;

			if (check::checkAvaiablePos(_gridMap, nRow, nCol))posList.push_back(pos(nRow, nCol));
			else return actionResult::COL_BOTTOM;
		}

		check::pushNewPosToBlock4(shape, posList);

		pos newPos = pos(shape->_position.row - _speed, shape->_position.col);
		shape->setPosition(_gridMap, newPos);

		return actionResult::COL_NONE;
	}
	else
	{
		return actionResult::COL_BOTTOM;
	}
}

VerticalSlide::VerticalSlide(const shared_ptr<GridMap>& grid, const int& direct) :
	ShapeAction(grid),
	_direction(direct)
{
}

int VerticalSlide::run(shared_ptr<Shape>& shape)
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
			else
			{
				if (_direction == direction::LEFT) return actionResult::COL_LEFT;
				if (_direction == direction::RIGHT) return actionResult::COL_RIGHT;
			}
		}

		check::pushNewPosToBlock4(shape, posList);

		pos newPos = pos(shape->_position.row, shape->_position.col);
		if (_direction == direction::LEFT) newPos.col -= 1;
		if (_direction == direction::RIGHT) newPos.col += 1;
		
		shape->setPosition(_gridMap, newPos);

		return actionResult::COL_NONE;
	}
	else
	{
		if (_direction == direction::LEFT) return actionResult::COL_LEFT;
		if (_direction == direction::RIGHT) return actionResult::COL_RIGHT;
	}
}