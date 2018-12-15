#pragma once
#include "Headers.h"

class Shape;
class GridMap;

class ShapeFactory
{
	static ShapeFactory* instance;

	shared_ptr<Shape> _shapeIsFalling;
	pos _currentPos;

	shared_ptr<GridMap> _tetrisMap;
	Layer* _currentLayer;

	ShapeFactory();
public:
	static ShapeFactory* getInstance();

	void init();
	void init(const shared_ptr<GridMap>& gridMap);
	void setLayer(Layer* layer);
	shared_ptr<Shape>& createShape();
	void setShapePosition(const int& row, const int& col);
	shared_ptr<GridMap> getTetrisMap() const { return _tetrisMap; }
	shared_ptr<Shape> getShapeIsFalling() const;
	pos getCurrentPos() const;
	void releaseShape();

};