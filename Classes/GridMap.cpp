#include "GridMap.h"
#include "Block.h"

GridMap::GridMap():
	_lengthBlock(0)
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
	for (int row = 0; row < _gridsBack.size(); row++)
	{
		bool isFull = all_of(_gridsFont[row].begin(), _gridsFont[row].end(), [](shared_ptr<Block>& b) {
			return b != nullptr;
		});
		if(isFull)
			rows.push_back(row);
	}
	return rows;
}

void GridMap::deleteRow(const int& row)
{
	for (auto& block : _gridsFont[row])
	{
		block->_sprite->removeFromParent();
		block = nullptr;
	}
}
