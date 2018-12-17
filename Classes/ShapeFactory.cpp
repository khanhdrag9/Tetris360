#include "ShapeFactory.h"
#include "Shape.h"
#include "GridMap.h"
#include "ShapeAction.h"
#include "BlockManager.h"

ShapeFactory* ShapeFactory::instance = new ShapeFactory();
pos ShapeFactory::posNull = pos(-1, -1);

ShapeFactory* ShapeFactory::getInstance()
{
	return instance;
}

ShapeFactory::ShapeFactory() :
	_shapeIsFalling(nullptr),
	_currentLayer(nullptr),
	_toAngle(0.f),
	_targetAngle(0.f)
{
	
}

void ShapeFactory::init()
{
	_tetrisMap = make_shared<GridMap>();
	_shapeAction = make_shared<Fall>(_tetrisMap);
	_shapeIsFalling = make_shared<Shape>();
}

void ShapeFactory::init(const shared_ptr<GridMap>& gridMap)
{
	_tetrisMap = gridMap;
	_shapeAction = make_shared<Fall>(_tetrisMap);
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
		detail = make_unique<IShape>();
		break;
	case typeShape::T :
		detail = make_unique<IShape>();
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

void ShapeFactory::updateShape()
{
	if (_shapeIsFalling && _shapeAction);
	_shapeAction->run(_shapeIsFalling);
}

void ShapeFactory::setShapePosition(const int& row, const int& col)
{
	if (_shapeIsFalling)
	{
		bool avaiablePos = true;

		int increRowValue = row - _shapeIsFalling->_position.row;
		int increColValue = col - _shapeIsFalling->_position.col;

		//check newPos
		vector<pos> newCoord;
		for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
		{
			int c, r;
			if (_shapeIsFalling->_position != posNull)
			{
				c = _shapeIsFalling->_blocks[i]->_coord.col + increColValue;
				r = _shapeIsFalling->_blocks[i]->_coord.row + increRowValue;
			}
			else
			{
				c = _shapeIsFalling->_detail->referToInitLocationNodeBoard(0, i) + col;
				r = _shapeIsFalling->_detail->referToInitLocationNodeBoard(1, i) + row;
			}

			if (c >= 0 && r >= 0 && r < _tetrisMap->getGirdsBack().size() && c < MAX_COL)
			{
				if (_tetrisMap->getGirdsFont()[r][c])
				{
					avaiablePos = false;
					break;
				}
				else
				{
					newCoord.push_back(pos(r, c));
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
				pos crd = block->_coord;
				if(crd != pos_null)
					_tetrisMap->getGirdsBack()[crd.row][crd.col] = false;
			}

			for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
			{
				_shapeIsFalling->_blocks[i]->_coord = newCoord[i];
				_tetrisMap->getGirdsBack()[newCoord[i].row][newCoord[i].col] = true;
			}

			Vec2 newPos = _tetrisMap->getGirdsPosition()[row][col];
			_shapeIsFalling->_node->setPosition(newPos);
			_shapeIsFalling->_position = pos(row, col);
	
		}
	}
}

void ShapeFactory::setToRotateBlock(const float& angle)
{
	if (_shapeIsFalling)
	{
		float curRot = _shapeIsFalling->_node->getRotation();
		if (_targetAngle != curRot)
		{
			//_shapeIsFalling->_node->setRotation(_targetAngle);
		}
		else
		{
			_toAngle = angle;
			_targetAngle = _shapeIsFalling->_node->getRotation() + _toAngle;
		}
	}
}

void ShapeFactory::rotateBlock()
{
	
}

shared_ptr<Shape> ShapeFactory::getShapeIsFalling() const
{
	return _shapeIsFalling;
}

pos ShapeFactory::getCurrentPos() const
{
	return _shapeIsFalling->_position;
}

void ShapeFactory::releaseShape()
{
	if (_shapeIsFalling)
	{
		_shapeIsFalling->_node->setRotation(0.f);
		for (auto& block : _shapeIsFalling->_blocks)
		{
			int cx = block->_coord.row;
			int cy = block->_coord.col;

			_tetrisMap->getGirdsFont()[cx][cy] = block;

			block->_sprite->retain();
			block->_sprite->removeFromParentAndCleanup(true);
			_currentLayer->addChild(block->_sprite);
			block->_sprite->autorelease();

			block->_sprite->setPosition(_tetrisMap->getGirdsPosition()[cx][cy].x, _tetrisMap->getGirdsPosition()[cx][cy].y);
		}

		BlockManager::getInstance()->releaseShape(_shapeIsFalling);
		_shapeIsFalling->_position = posNull;
		_targetAngle = 0.f;
		_toAngle = 0.f;
	}
}