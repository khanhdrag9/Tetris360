#include "GridMap.h"
#include "Block.h"

GridMap::GridMap() :
	_lengthBlock(0),
	_directionFall(direction::DOWN)
{
	init();
}

GridMap::~GridMap()
{

}

void GridMap::init()
{
	_screenSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	//_node = Node::create();

	float sizeForW = float(_screenSize.width) / (float)(MAX_COL);
	float sizeForH = float(_screenSize.height) / (float)(MAX_ROW);

    if(sizeForW < sizeForW)
    {
        _lengthBlock = sizeForW;
        _isVertical = false;
    }
    else if(sizeForW >= sizeForH)
    {
        _lengthBlock = sizeForH;
        _isVertical = true;
    }

//    float pX = _lengthBlock * 0.5f  + _origin.x;
//    float pY = _lengthBlock * 0.5f + _origin.y;
    
    float pX = _lengthBlock * 0.5f;
    float pY = _lengthBlock * 0.5f;
    
	float increValue = _lengthBlock;
	for (int row = 0; row < MAX_ROW + ABOVE_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			_gridsBack[row][col] = false;
			_gridsFont[row][col] = nullptr;
			_gridsPosi[row][col] = Vec2(pX, pY);

			pX += increValue;
		}
		pY += increValue;
		//pX = _lengthBlock * 0.5f + _origin.x;
        pX = _lengthBlock * 0.5f;
	}

}

list<int> GridMap::findRowFull()
{
	list<int> rows;
	if (_directionFall == direction::DOWN)
	{
		for (int row = 0; row < _gridsBack.size(); row++)
		{
			bool isFull = all_of(_gridsFont[row].begin(), _gridsFont[row].end(), [](shared_ptr<Block>& b) {
				return b != nullptr;
			});
			if (isFull)
				rows.push_back(row);
		}
	}
	else // if hozi
	{
		for (int row = 0; row < MAX_COL; row++)
		{
			bool isFull = true;
			for (int col = 0; col < MAX_ROW; col++)
			{
				if (_gridsFont[row][col] == nullptr)
				{
					isFull = false;
					break;
				}
			}
			if (isFull)rows.push_back(row);
		}
	}

	return rows;
}

void GridMap::deleteRow(const int& row)
{
	if (_directionFall == direction::DOWN)
	{
		for (auto& block : _gridsFont[row])
		{
			block->_sprite->removeFromParent();
			block = nullptr;
		}
	}
	else
	{
		for (int i = 0; i < MAX_ROW; i++)
		{
			_gridsFont[row][i]->_sprite->removeFromParent();
			_gridsFont[row][i] = nullptr;
		}
	}
}

void GridMap::setDirectionFall(const int& direct)
{
	switch (direct)
	{
	case direction::DOWN:
		_directionFall = direction::DOWN;
		break;
	case direction::LEFT:
		_directionFall = direction::LEFT;
		break;
	case direction::RIGHT:
		_directionFall = direction::RIGHT;
		break;
	default:
		break;
	}
}
