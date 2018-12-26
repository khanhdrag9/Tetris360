#pragma once

//of Cocos
#include "cocos2d.h"
USING_NS_CC;

//of C++
#include <iostream>

#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <chrono>

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
	bool operator!=(const pos& pos)
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
	ROTATE,
    FALLNOW
};

enum actionResult {
	COL_NONE,
	COL_HAS,
	COL_LEFT,
	COL_RIGHT,
	COL_BOTTOM
};

template <typename T>
class grid
{
protected:
    vector<vector<T>> _grids;
    
public:
    vector<T>& operator[](const int& index)
    {
        return _grids[index];
    }
    
    const vector<T>& operator[](const int& index) const
    {
        return _grids[index];
    }
    
    size_t size() const //number row
    {
        return _grids.size();
    }
    
    size_t numberCol() const
    {
        return _grids[0].size();
    }
    
    vector<vector<T>> cloneGrid()
    {
        auto clone(_grids);
        return clone;
    }
};
