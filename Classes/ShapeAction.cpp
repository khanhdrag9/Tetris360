#include "ShapeAction.h"
#include "Shape.h"
#include "GridMap.h"

ShapeAction::ShapeAction(const shared_ptr<GridMap>& grid) :
	_gridMap(grid)
{
}

int ShapeAction::run(shared_ptr<Shape>& shape)
{
	if (shape->_running == false)
	{
		shape->_running = true;
		int result = runAction(shape);
		shape->_running = false;
		return result;
	}
	return actionResult::COL_NONE;
}

int ShapeAction::runAction(shared_ptr<Shape>& shape)
{
	return actionResult::COL_NONE;
}

Fall::Fall(const shared_ptr<GridMap>& grid, const int& speed) :
	ShapeAction(grid),
	_speed(speed)
{
}

int Fall::runAction(shared_ptr<Shape>& shape)
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

		pos newPos = pos(shape->_position.row - _speed, shape->_position.col);
		if (check::checkAvaiablePos(_gridMap, newPos.row, newPos.col))
		{
			check::pushNewPosToBlock4(shape, posList);
			shape->setPosition(_gridMap, newPos);
			return actionResult::COL_NONE;
		}
		else
		{
			return actionResult::COL_HAS;
		}
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

int VerticalSlide::runAction(shared_ptr<Shape>& shape)
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

		pos newPos = pos(shape->_position.row, shape->_position.col);
		if (_direction == direction::LEFT) newPos.col -= 1;
		if (_direction == direction::RIGHT) newPos.col += 1;

		if (check::checkAvaiablePos(_gridMap, newPos.row, newPos.col))
		{
			check::pushNewPosToBlock4(shape, posList);
			shape->setPosition(_gridMap, newPos);
			return actionResult::COL_NONE;
		}
		else
		{ 
			if (_direction == direction::LEFT) return actionResult::COL_LEFT;
			if (_direction == direction::RIGHT) return actionResult::COL_RIGHT;
			return actionResult::COL_HAS;
		}
	}
	else
	{
		if (_direction == direction::LEFT) return actionResult::COL_LEFT;
		if (_direction == direction::RIGHT) return actionResult::COL_RIGHT;
	}

	return actionResult::COL_NONE;
}

Rotate::Rotate(const shared_ptr<GridMap>& grid, const float& angle) :
	ShapeAction(grid),
	_angle(angle)
{
}

int Rotate::runAction(shared_ptr<Shape>& shape)
{
	if (shape && shape->_position != pos_null && _gridMap)
	{
		float rotAngle = _angle;
		float p = shape->_node->getRotation();
		float curRot = (float)(int(p) % 360);
		int quotient = ceil(curRot / 90);

		if (curRot >= shape->_detail->getMaxAngle())
		{
		/*	shape->_node->setRotation(0.f);
			return actionResult::COL_NONE;*/
			rotAngle *= -1; 
		}
		
		int numberBlock = shape->_blocks.size();
		float newRot = curRot + rotAngle;

		list<pos> posList;

		for (int i = 0; i < numberBlock; i++)
		{
			int nRow = shape->_blocks[i]->_coord.row + shape->_detail->referToRotate(0, quotient * numberBlock + i);
			int nCol = shape->_blocks[i]->_coord.col + shape->_detail->referToRotate(1, quotient * numberBlock + i);

			if (check::checkAvaiablePos(_gridMap, nRow, nCol)) posList.push_back(pos(nRow, nCol));
			else return actionResult::COL_HAS;
		}

		check::pushNewPosToBlock4(shape, posList);
		shape->_node->setRotation(newRot);	

		return actionResult::COL_NONE;
	}
	else
	{
		return actionResult::COL_HAS;
	}
}