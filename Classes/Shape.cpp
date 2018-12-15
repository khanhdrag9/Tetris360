#include "Shape.h"
#include "ConfigDetailShape.h"

Shape::Shape()
{
	_node = Node::create();
}

// O
const int& OShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& OShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::O[row][col]; }

// I
const int& IShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& IShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::I[row][col]; }

// L
const int& LShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& LShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::L[row][col]; }

// T
const int& TShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& TShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::T[row][col]; }
