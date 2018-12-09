#include "Block.h"

Block::Block()
{
}

Block::Block(const char* fileOrFrame)
{
	_sprite = Sprite::create(fileOrFrame);
	if (!_sprite)
		_sprite = Sprite::createWithSpriteFrameName(fileOrFrame);
}

Block::~Block()
{
}
