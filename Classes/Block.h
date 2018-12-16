#pragma once
#include "Headers.h"

class Block;

using Block4 = array<shared_ptr<Block>, 4>;

class Block
{
public:
	Sprite* _sprite;
	pos _coord;

	Block();
	Block(const char* fileOrFrame);
	virtual ~Block();
};