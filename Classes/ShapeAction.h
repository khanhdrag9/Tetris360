#include "Headers.h"

class Shape;
class GridMap;

class ShapeAction
{
protected:
	shared_ptr<GridMap> _gridMap;

public:
	ShapeAction(const shared_ptr<GridMap>& grid);
	virtual ~ShapeAction(){}
	virtual int run(shared_ptr<Shape>& shape) = 0;
};

class Fall : public ShapeAction
{
	int _speed;
public:
	Fall(const shared_ptr<GridMap>& grid, const int& speed = 1);
	int run(shared_ptr<Shape>& shape) override;
};

class VerticalSlide : public ShapeAction
{
	int _direction;
public:
	VerticalSlide(const shared_ptr<GridMap>& grid, const int& direct);
	int run(shared_ptr<Shape>& shape) override;
};

class Rotate : public ShapeAction
{
	float _angle;
public:
	Rotate(const shared_ptr<GridMap>& grid, const float& angle);
	int run(shared_ptr<Shape>& shape) override;
};