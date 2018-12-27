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
//    if (_directionFall == direction::DOWN)
//    {
		for (int row = 0; row < _gridsBack.size(); row++)
		{
			bool isFull = all_of(_gridsFont[row].begin(), _gridsFont[row].end(), [](shared_ptr<Block>& b) {
				return b != nullptr;
			});
			if (isFull)
				rows.push_back(row);
		}
//    }
//    else // if hozi
//    {
//        for (int row = 0; row < MAX_COL; row++)
//        {
//            bool isFull = true;
//            for (int col = 0; col < MAX_ROW; col++)
//            {
//                if (_gridsFont[row][col] == nullptr)
//                {
//                    isFull = false;
//                    break;
//                }
//            }
//            if (isFull)rows.push_back(row);
//        }
//    }

	return rows;
}

void GridMap::deleteRow(const int& row)
{
//    if (_directionFall == direction::DOWN)
//    {
		for (auto& block : _gridsFont[row])
		{
			block->_sprite->removeFromParent();
			block = nullptr;
		}
//    }
//    else
//    {
//        for (int i = 0; i < MAX_ROW; i++)
//        {
//            _gridsFont[row][i]->_sprite->removeFromParent();
//            _gridsFont[row][i] = nullptr;
//        }
//    }
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
	auto cBack = _gridsBack.cloneGrid();
	auto cFont = _gridsFont.cloneGrid();
	auto cPosi = _gridsPosi.cloneGrid();

    std::swap(_row, _col);
	initGirds(_row + ABOVE_ROW, _col);
	int realNewRow = _row + ABOVE_ROW;

    if(_directionFall == direction::DOWN)
    {
		

    }
    else if(_directionFall == direction::LEFT)
    {
        for(int nr = 0; nr < _row; nr++)
        {
            for(int nc = 0; nc < _col; nc++)
            {
                _gridsBack[nr][nc] = cBack[nc][nr];
                _gridsFont[nr][nc] = cFont[nc][nr];
                _gridsPosi[nr][nc] = cPosi[nc][nr];
            }
        }
        
        //above row
        float pX = _lengthBlock * _row;
        float pY = _lengthBlock * 0.5f;
        
        float increValue = _lengthBlock;
        for (int row = _row; row < realNewRow; row++)
        {
            for (int col = 0; col < _col; col++)
            {
                //_gridsBack[row][col] = false;
                //_gridsFont[row][col] = nullptr;
                _gridsPosi[row][col] = Vec2(pX, pY);
                
                pY += increValue;
            }
            pX += increValue;
            //pX = _lengthBlock * 0.5f + _origin.x;
            pY = _lengthBlock * 0.5f;
        }
        
    }
    else if(_directionFall == direction::RIGHT)
    {
        
    }
}

const array<int, 2> GridMap::getNumberDirect() const
{
    int i1 = (_directionFall == direction::DOWN ? 0 : 1);
    int i2 = (_directionFall == direction::DOWN ? 1 : 0);
    
    return array<int, 2>{i1, i2};
}
