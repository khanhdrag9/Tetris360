#include "ShapeFactory.h"
#include "Shape.h"
#include "GridMap.h"
#include "BlockManager.h"

ShapeFactory* ShapeFactory::instance = new ShapeFactory();

ShapeFactory* ShapeFactory::getInstance()
{
	return instance;
}

ShapeFactory::ShapeFactory() :
	_shapeIsFalling(nullptr)
{
	
}

void ShapeFactory::init()
{
	_tetrisMap = make_shared<GridMap>();
}

void ShapeFactory::init(const shared_ptr<GridMap>& gridMap)
{
	_tetrisMap = gridMap;
	_shapeIsFalling = make_shared<Shape>();
}

void ShapeFactory::setLayer(Layer* layer)
{
	_currentLayer = layer;
}

shared_ptr<Shape>& ShapeFactory::createShape()
{
	float lenghtBlock = _tetrisMap->getLengthBlock();
	_shapeIsFalling->_detail = make_unique<OShape>();

	for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
	{
		_shapeIsFalling->_blocks[i] = make_shared<Block>(BLOCK_PATH);
		_shapeIsFalling->_blocks[i]->_sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		float scale = lenghtBlock / (float)(_shapeIsFalling->_blocks[i]->_sprite->getBoundingBox().size.width);
		_shapeIsFalling->_blocks[i]->_sprite->setScale(scale);

		float px = _shapeIsFalling->_detail->referToInitLocationNodeBoard(0, i);
		float py = _shapeIsFalling->_detail->referToInitLocationNodeBoard(1, i);
		_shapeIsFalling->_blocks[i]->_sprite->setPosition(lenghtBlock * px, lenghtBlock * py);
		_shapeIsFalling->_node->addChild(_shapeIsFalling->_blocks[i]->_sprite);
	}

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

			block->_sprite->retain();
			block->_sprite->removeFromParent();
			_currentLayer->addChild(block->_sprite);
			block->_sprite->autorelease();

			block->_sprite->setPosition(_tetrisMap->getGirdsPosition()[cx][cy].x, _tetrisMap->getGirdsPosition()[cx][cy].y);
		}

		BlockManager::getInstance()->releaseShape(_shapeIsFalling);
	}
}