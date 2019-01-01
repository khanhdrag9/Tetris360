#include "ManagerLogic.h"
#include "GridMap.h"
#include "BlockManager.h"
#include "Block.h"

ManagerLogic::ManagerLogic():
    _score(0),
    _label(nullptr),
    _numRowFall(0)
{
}

void ManagerLogic::initScore(Layer* layer, const Vec2& pos, const float& size, const Color3B &color)
{
    _label = Label::createWithTTF(std::to_string(_score), FONT_ARIAL, size);
    _label->setPosition(pos);
    _label->setColor(color);
    layer->addChild(_label);
}

void ManagerLogic::increScore(const int &incre)
{
    _score++;
    if(_label)
        _label->setString(std::to_string(_score));
}

void ManagerLogic::checkRowFull(GridMap& _gridMap)
{
    _listRowDeleted = _gridMap.findRowFull();
    if (_listRowDeleted.size() <= 0)
    {
        if(_numRowFall > 0)
        {
            BlockManager::getInstance()->refreshPool();
            _numRowFall = 0;
        }

        return;
    }

    while (_listRowDeleted.size() > 0)
    {
        int row = *(_listRowDeleted.begin());
        _gridMap.deleteRow(row);

        //incre score

        if (reSetupBlocksPos(_gridMap, row))
        {
            _listRowDeleted.pop_front();
            bool avableDrop = all_of(_listRowDeleted.begin(), _listRowDeleted.end(), [](int& row) {
                row--;
                return row >= 0;
            });
            if (!avableDrop)break;
        }

        _numRowFall++;
    }

    checkRowFull(_gridMap);
}

bool ManagerLogic::reSetupBlocksPos(GridMap& _gridMap, const int &row)
{
    if (row == -1)
    {
        if (_listRowDeleted.size() > 0)
        {
            //feature optimize code...

        }
        return false;
    }
    else if(row >= 0)
    {
        int aboveRow = row + 1;
        while (aboveRow <= _gridMap.getSize().row)
        {
            for (auto& block : _gridMap.getGirdsFont()[aboveRow])
            {
                if (block)
                {
                    pos newPos = pos(block->_coord.row - 1, block->_coord.col);
                    BlockManager::getInstance()->moveBlock(block, newPos);

                }
            }
            aboveRow++;
        }
        return true;
    }

    return false;
}