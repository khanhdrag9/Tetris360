#pragma once
#include "Headers.h"

class Shape;
class GridMap;
class DetailShape;
class ShapeAction;

class ShapeFactory
{
	static ShapeFactory* instance;

	shared_ptr<Shape> _shapeIsFalling;
	pos _currentPos;
	float _toAngle;
	float _targetAngle;

	shared_ptr<GridMap> _tetrisMap;
	//shared_ptr<ShapeAction> _shapeAction;
	Layer* _currentLayer;

	ShapeFactory();
	void getRandomTypeShape(unique_ptr<DetailShape>& detail);
public:
	shared_ptr<ShapeAction> _shapeAction;
	enum typeShape
	{
		O,
		I,
		L,
		T,
		NONE
	};
	static pos posNull;

	static ShapeFactory* getInstance();

	void init();
	void init(const shared_ptr<GridMap>& gridMap);
	void setLayer(Layer* layer);
	shared_ptr<Shape>& createShape();
	void updateShape();
	void setShapePosition(const int& row, const int& col);
	void setToRotateBlock(const float& angle);
	void rotateBlock();
	shared_ptr<GridMap> getTetrisMap() const { return _tetrisMap; }
	shared_ptr<Shape> getShapeIsFalling() const;
	pos getCurrentPos() const;
	void releaseShape();

};