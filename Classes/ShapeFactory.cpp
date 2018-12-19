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
	_shapeAction = make_unique<Fall>(_tetrisMap, 1);
	_shapeIsFalling = make_shared<Shape>();
}

void ShapeFactory::init(const shared_ptr<GridMap>& gridMap)
{
	_tetrisMap = gridMap;
	_shapeAction = make_unique<Fall>(_tetrisMap);
	_shapeIsFalling = make_shared<Shape>();
}

void ShapeFactory::setLayer(Layer* layer)
{
	_currentLayer = layer;
}

void ShapeFactory::getRandomTypeShape(unique_ptr<DetailShape>& detail)
{
	int ran = rand() % typeShape::NONE;
	ran = typeShape::Z;
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
	case typeShape::J:
		detail = make_unique<JShape>();
		break;
	case typeShape::S:
		detail = make_unique<SShape>();
		break;
	case typeShape::Z:
		detail = make_unique<ZShape>();
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

int ShapeFactory::updateShape()
{
	if (_shapeIsFalling && _shapeAction);
	return _shapeAction->run(_shapeIsFalling);
}

bool ShapeFactory::setShapePosition(const pos& position)
{
	if (_shapeIsFalling)
	{
		//check newPos
		list<pos> posList;
		for (int i = 0; i < _shapeIsFalling->_blocks.size(); i++)
		{
			int c, r;
			c = _shapeIsFalling->_detail->referToInitLocationNodeBoard(0, i) + position.col;
			r = _shapeIsFalling->_detail->referToInitLocationNodeBoard(1, i) + position.row;

			if (check::checkAvaiablePos(_tetrisMap, r, c)) posList.push_back(pos(r, c));
			else return false;
		}

		//set all old pos -> false	
		for (auto& block : _shapeIsFalling->_blocks)
		{
			pos crd = block->_coord;
			if(crd != pos_null)
				_tetrisMap->getGirdsBack()[crd.row][crd.col] = false;
		}

		check::pushNewPosToBlock4(_shapeIsFalling, posList);

		_shapeIsFalling->setPosition(_tetrisMap, position);
	
	}
}

void ShapeFactory::setActionShape(const int& type)
{
	switch (type)
	{
	case actiontype::SLIDE_LEFT:
		_shapeAction = make_unique<VerticalSlide>(_tetrisMap, direction::LEFT);
		break;
	case actiontype::SLIDE_RIGHT:
		_shapeAction = make_unique<VerticalSlide>(_tetrisMap, direction::RIGHT);
		break;
	case actiontype::FALL:
		_shapeAction = make_unique<Fall>(_tetrisMap, 1);
		break;
	case actiontype::STAND:
		_shapeAction = make_unique<Fall>(_tetrisMap, 0);
		break;
	case actiontype::ROTATE:
		_shapeAction = make_unique<Rotate>(_tetrisMap, 90);
		break;
	default:
		_shapeAction = make_unique<Fall>(_tetrisMap, 0);
		break;
	}
}

void ShapeFactory::setToRotateBlock(const float& angle)
{
	
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