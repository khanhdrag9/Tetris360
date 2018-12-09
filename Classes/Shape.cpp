#include "Shape.h"
#include "ConfigDetailShape.h"

Shape::Shape()
{
	_node = Node::create();
}

// O
const int& OShape::referToInitCoordBoard(const int& row, const int& col) { return crd::O[row][col]; }
const int& OShape::referToInitLocationNodeBoard(const int& row, const int& col) { return loc::O[row][col]; }