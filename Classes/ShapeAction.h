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
	virtual bool run(shared_ptr<Shape>& shape) = 0;
};

class Fall : public ShapeAction
{
	int _speed;
public:
	Fall(const shared_ptr<GridMap>& grid, const int& speed = 1);
	bool run(shared_ptr<Shape>& shape) override;
};

class VerticalSlide : public ShapeAction
{
	int _direction;
public:
	VerticalSlide(const shared_ptr<GridMap>& grid, const int& direct);
	bool run(shared_ptr<Shape>& shape) override;
};