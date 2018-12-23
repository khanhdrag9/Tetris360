#pragma once
#include "Headers.h"

class Shape;
class GridMap;
struct pos;

class check
{
public:
	static bool checkAvaiablePos(const shared_ptr<GridMap>& grid, const int& row, const int& col);
	static void pushNewPosToBlock4(const shared_ptr<Shape>& shape, list<pos>& posList);
    static int getRandom(int start, int end);
};
