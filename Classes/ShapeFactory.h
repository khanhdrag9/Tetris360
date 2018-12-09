#pragma once
#include "Headers.h"

class Shape;
class GridMap;

class ShapeFactory
{
	static ShapeFactory* instance;

	shared_ptr<Shape> _shapeIsFalling;
	shared_ptr<GridMap> _tetrisMap;

	ShapeFactory();
public:
	static ShapeFactory* getInstance();

	shared_ptr<Shape>& createShape();
	void setShapePosition(const int& row, const int& col);
	

	void setLayer(Layer* layer);
};