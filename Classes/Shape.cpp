#include "Shape.h"
#include "ConfigDetailShape.h"
#include "GridMap.h"

Shape::Shape()
{
	_node = Node::create();
}

void Shape::setPosition(const shared_ptr<GridMap>& grid, const pos& newPos)
{
	_position = newPos;
	_node->setPosition(grid->getGirdsPosition()[newPos.row][newPos.col]);
}

// O
OShape::OShape() { _maxAngle = 0.f; }
const int& OShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& OShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::O[row][col]; }
const int& OShape::referToRotate(const int& row, const int& col) { return rot::O[row][col]; }

// I
IShape::IShape() { _maxAngle = 90.f; }
const int& IShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& IShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::I[row][col]; }
const int& IShape::referToRotate(const int& row, const int& col) { return rot::I[row][col]; }

// L
LShape::LShape() { _maxAngle = 270.f; }
const int& LShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& LShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::L[row][col]; }
const int& LShape::referToRotate(const int& row, const int& col) { return rot::O[row][col]; }

// T
TShape::TShape() { _maxAngle = 270.f; }
const int& TShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& TShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::T[row][col]; }
const int& TShape::referToRotate(const int& row, const int& col) { return rot::O[row][col]; }
