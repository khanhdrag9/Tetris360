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
	int run(shared_ptr<Shape>& shape);

protected:
	virtual int runAction(shared_ptr<Shape>& shape);
};

class Fall : public ShapeAction
{
	int _speed;
public:
	Fall(const shared_ptr<GridMap>& grid, const int& speed = 1);
private:
	int runAction(shared_ptr<Shape>& shape) override;
};

class FallImmediately : public ShapeAction
{
public:
    FallImmediately(const shared_ptr<GridMap>& grid);
private:
    int runAction(shared_ptr<Shape>& shape) override;
};

class VerticalSlide : public ShapeAction
{
	int _direction;
public:
	VerticalSlide(const shared_ptr<GridMap>& grid, const int& direct);
private:
	int runAction(shared_ptr<Shape>& shape) override;
};

class Rotate : public ShapeAction
{
	float _angle;
public:
	Rotate(const shared_ptr<GridMap>& grid, const float& angle);
private:
	int runAction(shared_ptr<Shape>& shape) override;
    list<pos> canRotateInAroudPos(shared_ptr<Shape>& shape, const int& quotient);
    list<pos> canRotate(const shared_ptr<Shape>& shape, const pos& p, const int& quotient);
};
