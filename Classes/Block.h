#pragma once
#include "Headers.h"

class Block;

using Block4 = array<shared_ptr<Block>, 4>;

struct Coord
{
	int cx, cy;
	Coord(): cx(-1), cy(-1){}
	Coord(int x, int y): cx(x), cy(y){}
	void operator=(const Coord& coord)
	{
		cx = coord.cx;
		cy = coord.cy;
	}
	bool operator==(const Coord& coord)
	{
		return (cx == coord.cx && cy == coord.cy);
	}
};

#define COORD_NONE Coord(-1, -1)

class Block
{
public:
	Sprite* _sprite;
	Coord _coord;

	Block();
	Block(const char* fileOrFrame);
	virtual ~Block();
};