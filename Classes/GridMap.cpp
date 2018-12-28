#include "GridMap.h"
#include "Block.h"

//grids
void grids_back::init(const int& row, const int& col)
{
    _grids.clear();
    
    vector<bool> vec;
    vec.resize(col, false);
    _grids.resize(row, vec);
    vec.clear();
}
void grids_font::init(const int& row, const int& col)
{
    _grids.clear();
    
    vector<shared_ptr<Block>> vec;
    vec.resize(col, nullptr);
    _grids.resize(row, vec);
    vec.clear();
}
void grids_posi::init(const int& row, const int& col)
{
    _grids.clear();
    
    vector<Vec2> vec;
    vec.resize(col, Vec2(-1.f, -1.f));
    _grids.resize(row, vec);
    vec.clear();
}


//map
int GridMap::_bottom = 10;
int GridMap::_left = 0;
int GridMap::_right = MAX_COL - 1;

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

    _row = MAX_ROW;
    _col = MAX_COL;
	//_node = Node::create();
    initGirds(_row + ABOVE_ROW, _col);
    
    
	float sizeForW = float(_screenSize.width) / (float)(MAX_COL);
	float sizeForH = float(_screenSize.height) / (float)(MAX_ROW);

    if(sizeForW < sizeForH)
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
			//_gridsBack[row][col] = false;
			//_gridsFont[row][col] = nullptr;
			_gridsPosi[row][col] = Vec2(pX, pY);

			pX += increValue;
		}
		pY += increValue;
		//pX = _lengthBlock * 0.5f + _origin.x;
        pX = _lengthBlock * 0.5f;
	}

}

void GridMap::initGirds(const int& row, const int& col)
{
    _gridsBack.init(row, col);
    _gridsFont.init(row, col);
    _gridsPosi.init(row, col);
}

list<int> GridMap::findRowFull()
{
	list<int> rows;
	for (int row = 0; row < _gridsBack.size(); row++)
	{
		bool isFull = all_of(_gridsFont[row].begin(), _gridsFont[row].end(), [](shared_ptr<Block>& b) {
			return b != nullptr;
		});
		if (isFull)
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

void GridMap::setDirectionFall(const int& direct)
{
    if(_directionFall == direct)
        return;
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
    
    rotateBoard();
}

void GridMap::rotateBoard()
{
	short axis = _col / 2;

	for (int i = 0; i < _row; i++)
	{
		for (auto& block : _gridsFont[i])
		{
			pos oldCrd = pos(block->_coord);
			//code something...

			
		}
	}
}
