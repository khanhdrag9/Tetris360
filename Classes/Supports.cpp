#include "Supports.h"
#include "GridMap.h"
#include "Shape.h"
#include <random>

bool check::checkAvaiablePos(const shared_ptr<GridMap>& grid, const int& row, const int& col)
{
	if (row >= 0 && row < grid->getGirdsBack().size() && col >= 0 && col < grid->getSize().col)
	{
		if (grid->getGirdsFont()[row][col])
			return false;
		else
			return true;
	}
	else
	{
		return false;
	}
}

void check::pushNewPosToBlock4(const shared_ptr<Shape>& shape, list<pos>& posList)
{
	for (int i = 0; i < shape->_blocks.size(); i++)
	{
		shape->_blocks[i]->_coord = *(posList.begin());
		posList.pop_front();
	}
}

int check::getRandom(int start, int end)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(start, end - 1);
    
    return dist(mt);
}
