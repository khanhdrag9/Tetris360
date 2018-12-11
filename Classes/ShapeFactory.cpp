#include "ShapeFactory.h"
#include "Shape.h"
#include "GridMap.h"
#include "BlockManager.h"

ShapeFactory* ShapeFactory::instance = nullptr;

ShapeFactory* ShapeFactory::getInstance()
{
	if (!instance)
		instance = new ShapeFactory();
	return instance;
}

ShapeFactory::ShapeFactory() :
	_shapeIsFalling(nullptr)
{
	_tetrisMap = make_shared<GridMap>();
}

shared_ptr<Shape>& ShapeFactory::createShape()
{
	float lenghtBlock = _tetrisMap->getLengthBlock();
	shared_ptr<Shape> shape = make_shared<Shape>();
	shape->_detail = make_unique<OShape>();

	for (int i = 0; i < shape->_blocks.size(); i++)
	{
		shape->_blocks[i] = make_shared<Block>(BLOCK_PATH);
		shape->_blocks[i]->_sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		float scale = lenghtBlock / (float)(shape->_blocks[i]->_sprite->getBoundingBox().size.width);
		shape->_blocks[i]->_sprite->setScale(scale);

		float px = shape->_detail->referToInitLocationNodeBoard(0, i);
		float py = shape->_detail->referToInitLocationNodeBoard(1, i);
		shape->_blocks[i]->_sprite->setPosition(lenghtBlock * px, lenghtBlock * py);
		shape->_node->addChild(shape->_blocks[i]->_sprite);
	}

	_shapeIsFalling = shape;
	return _shapeIsFalling;
}

void ShapeFactory::setShapePosition(const int& row, const int& col)
{
	if (_shapeIsFalling)
	{
		for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
		{
			//handle old Coord
			if (!(_shapeIsFalling->_blocks[i]->_coord == COORD_NONE))
			{
				int cx = _shapeIsFalling->_blocks[i]->_coord.cx;
				int cy = _shapeIsFalling->_blocks[i]->_coord.cy;

				if(cx >= 0 && cy >= 0)
					_tetrisMap->getGirdsBack()[cx][cy] = false;
			}

			//change to new coord
			int cx = row + _shapeIsFalling->_detail->referToInitLocationNodeBoard(0, i);
			int cy = col + _shapeIsFalling->_detail->referToInitLocationNodeBoard(1, i);

			if (cx >= 0 && cy >= 0)
			{
				_shapeIsFalling->_blocks[i]->_coord = Coord(cx, cy);
				_tetrisMap->getGirdsBack()[cx][cy] = true;
			}
			else
			{
				_shapeIsFalling->_blocks[i]->_coord = COORD_NONE;
			}
		}

		Vec2 newPos = _tetrisMap->getGirdsPosition()[row][col];
		_shapeIsFalling->_node->setPosition(newPos);
		_currentPos = pos(row, col);
	}
}

shared_ptr<Shape> ShapeFactory::getShapeIsFalling() const
{
	return _shapeIsFalling;
}

pos ShapeFactory::getCurrentPos() const
{
	return _currentPos;
}

void ShapeFactory::releaseShape()
{
	if (_shapeIsFalling)
	{
		for (auto& block : _shapeIsFalling->_blocks)
		{
			int cx = block->_coord.cx;
			int cy = block->_coord.cy;
			
			_tetrisMap->getFontsBack()[cx][cy] = block;
			block = nullptr;
		}

		BlockManager::getInstance()->releaseShape(_shapeIsFalling);
	}
}