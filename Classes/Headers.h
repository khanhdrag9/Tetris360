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
#include "Template.h"

struct pos
{
	int row;
	int col;
	pos() : row(-1), col(-1) {}
	pos(const pos& pos) : row(pos.row), col(pos.col) {}
	pos(int r, int c) : row(r), col(c) {}
	void operator=(const pos& pos)
	{
		row = pos.row;
		col = pos.col;
	}
	bool operator!=(pos& pos)
	{
		return (row != pos.row || col != pos.col);
	}
};
#define pos_null pos(-1, -1)

enum direction {
	NONE,
	LEFT,
	RIGHT,
	DOWN
};

enum actiontype {
	STAND,
	FALL,
	SLIDE_LEFT,
	SLIDE_RIGHT,
};

enum actionResult {
	COL_NONE,
	COL_LEFT,
	COL_RIGHT,
	COL_BOTTOM
};
