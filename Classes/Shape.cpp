#include "Shape.h"
#include "ConfigDetailShape.h"
#include "GridMap.h"

Shape::Shape():_running(false)
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
IShape::IShape() { _maxAngle = 360.f; }
const int& IShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& IShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::I[row][col]; }
const int& IShape::referToRotate(const int& row, const int& col) { return rot::I[row][col]; }

// L
LShape::LShape() { _maxAngle = 360.f; }
const int& LShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& LShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::L[row][col]; }
const int& LShape::referToRotate(const int& row, const int& col) { return rot::L[row][col]; }

// T
TShape::TShape() { _maxAngle = 360.f; }
const int& TShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& TShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::T[row][col]; }
const int& TShape::referToRotate(const int& row, const int& col) { return rot::T[row][col]; }

// J
JShape::JShape() { _maxAngle = 360.f; }
const int& JShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& JShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::J[row][col]; }
const int& JShape::referToRotate(const int& row, const int& col) { return rot::J[row][col]; }

// S
SShape::SShape() { _maxAngle = 360.f; }
const int& SShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& SShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::S[row][col]; }
const int& SShape::referToRotate(const int& row, const int& col) { return rot::S[row][col]; }
