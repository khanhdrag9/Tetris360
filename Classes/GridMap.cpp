#include "GridMap.h"
#include "Block.h"
#include "BlockManager.h"
#include "ShapeFactory.h"
#include "ManagerLogic.h"

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
    _currentLayer(nullptr)
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
    
	_node = Node::create();
    _axis = pos(GridMap::_bottom, _col / 2);
    
    initGirds(_row + ABOVE_ROW, _col);
    
//    GridMap::_left = 0;
//    GridMap::_right = _col - 1;
    
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
	for (int row = 0; row < _row + ABOVE_ROW; row++)
	{
		for (int col = 0; col < _col; col++)
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

    _node->setPosition(_gridsPosi[_axis.row][_axis.col]);
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
	for (int row = 0; row < _row; row++)
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
        block->_sprite = nullptr;
		block = nullptr;
	}
}


pos handleRotate(const pos& oldPos, const pos& axis)
{
    pos p = pos(oldPos.row - axis.row, oldPos.col - axis.col);
    
    pos result = pos(axis.row - p.col, axis.col + p.row);

    return result;
}

void GridMap::rotateBoard(Node* layer)
{
    _currentLayer = layer;

    _gridsFont.init(_row + ABOVE_ROW, _col);
    
    Vec2 _axisPos = _node->getPosition();
    for (auto& block : BlockManager::getInstance()->getBlockPool())
	{
        if(block)
        {
           // if(block->_sprite)
            {
            //calculate new pos
            //Vec2 oldPos = _gridsPosi[block->_coord.row][block->_coord.col];
            Vec2 oldPos = block->_sprite->getPosition();
            Vec2 posInNode = Vec2(oldPos - _axisPos);
            
            pos newPos = handleRotate(block->_coord, _axis);
            block->_coord = newPos;
            if(newPos.row >= 0 && newPos.row < _row + ABOVE_ROW && newPos.col >= 0 && newPos.col <= _col - 1)
            {
                _gridsFont[block->_coord.row][block->_coord.col] = block;
            }
            block->_sprite->setPosition(posInNode);
            block->_sprite->retain();
            block->_sprite->removeFromParentAndCleanup(true);
            _node->addChild(block->_sprite);
            block->_sprite->autorelease();
            }
            
        }
	}
    
    auto cb = CallFunc::create([this](){
        for (auto& block : BlockManager::getInstance()->getBlockPool())
        {
            if(block)
            {
                //calculate new pos
                Vec2 realPos;
                
                pos crd = block->_coord;
                if(crd.row >= 0 && crd.row < _row + ABOVE_ROW && crd.col >= 0 && crd.col <= _col - 1)
                {
                    realPos = _gridsPosi[block->_coord.row][block->_coord.col];
                   // block->_sprite->setVisible(true);
                }
                else
                {
                    //block->_sprite->setVisible(false);
                }
                
                
                block->_sprite->retain();
                block->_sprite->removeFromParentAndCleanup(true);
                block->_sprite->setPosition(realPos);
                _currentLayer->addChild(block->_sprite);
                block->_sprite->autorelease();
                
            }
        }
        
        _node->setRotation(0.f);
        ShapeFactory::_pause = false;

        ManagerLogic::getInstance()->checkRowFull(*this);

    });
    
    auto sequence = Sequence::createWithTwoActions(RotateBy::create(0.5f, 90.f), cb);
    _node->runAction(sequence);
    ShapeFactory::_pause = true;
}

void GridMap::releaseSpriteInNode()
{
    
}
