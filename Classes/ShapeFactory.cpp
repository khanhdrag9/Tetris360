#include "ShapeFactory.h"
#include "Shape.h"
#include "GridMap.h"

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
		
	}
}