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
	_shapeIsFalling = make_shared<Shape>();
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

void ShapeFactory::getRandomTypeShape(unique_ptr<DetailShape>& detail)
{
	int ran = rand() % typeShape::NONE;
	switch (ran)
	{
	case typeShape::O :
		detail = make_unique<OShape>();
		break;
	case typeShape::I :
		detail = make_unique<IShape>();
		break;
	case typeShape::L :
		detail = make_unique<LShape>();
		break;
	case typeShape::T :
		detail = make_unique<TShape>();
		break;

	default:
		detail = make_unique<OShape>();
		break;
	}
}

shared_ptr<Shape>& ShapeFactory::createShape()
{
	float lenghtBlock = _tetrisMap->getLengthBlock();
	getRandomTypeShape(_shapeIsFalling->_detail);

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
			int c = _shapeIsFalling->_detail->referToInitLocationNodeBoard(0, i) + col;
			int r = _shapeIsFalling->_detail->referToInitLocationNodeBoard(1, i) + row;

			if (c >= 0 && r >= 0 && r < _tetrisMap->getGirdsBack().size() && c < MAX_COL)
			{
				if (_tetrisMap->getGirdsFont()[r][c])
				{
					avaiablePos = false;
				}
				else
				{
					newCoord.push_back(Coord(r, c));
				}
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
			block->_sprite->removeFromParentAndCleanup(true);
			_currentLayer->addChild(block->_sprite);
			block->_sprite->autorelease();

			block->_sprite->setPosition(_tetrisMap->getGirdsPosition()[cx][cy].x, _tetrisMap->getGirdsPosition()[cx][cy].y);
		}

		BlockManager::getInstance()->releaseShape(_shapeIsFalling);
		_currentPos = pos();
	}
}