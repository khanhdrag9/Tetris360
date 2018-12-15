#pragma once

//of Cocos
#include "cocos2d.h"
USING_NS_CC;

//of C++
#include <iostream>

#include <array>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;

//of game
#include "Defines.h"
#include "Supports.h"

struct pos
{
	int row;
	int col;
	pos() : row(-1), col(-1) {}
	pos(int r, int c) : row(r), col(c) {}
	void operator=(pos& pos)
	{
		row = pos.row;
		col = pos.col;
	}
};
