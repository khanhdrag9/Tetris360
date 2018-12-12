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
		bool avaiablePos = true;

		//check newPos
		vector<Coord> newCoord;
		for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
		{
			auto& block = _shapeIsFalling->_blocks[i];
			int cx = _shapeIsFalling->_detail->referToInitLocationNodeBoard(0, i) + row;
			int cy = _shapeIsFalling->_detail->referToInitLocationNodeBoard(1, i) + col;

			if (cx >= 0 && cy >= 0 && cx < _tetrisMap->getGirdsBack().size() && cy < MAX_COL)
			{
				newCoord.push_back(Coord(cx, cy));
			}
			else
			{
				avaiablePos = false;
				break;
			}
		}

		if (avaiablePos)
		{
			//set all old pos -> false
			for (auto& block : _shapeIsFalling->_blocks)
			{
				Coord crd = block->_coord;
				if(!(crd == COORD_NONE))
					_tetrisMap->getGirdsBack()[crd.cx][crd.cy] = false;
			}

			for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
			{
				_shapeIsFalling->_blocks[i]->_coord = newCoord[i];
				_tetrisMap->getGirdsBack()[newCoord[i].cx][newCoord[i].cy] = true;
			}

			Vec2 newPos = _tetrisMap->getGirdsPosition()[row][col];
			_shapeIsFalling->_node->setPosition(newPos);
			_currentPos = pos(row, col);
		}
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
			
			_tetrisMap->getGirdsFont()[cx][cy] = block;
			block = nullptr;
		}

		BlockManager::getInstance()->releaseShape(_shapeIsFalling);
	}
}