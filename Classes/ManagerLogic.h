#pragma once
#include "Headers.h"

class GridMap;
class Shape;
class Block;

class ManagerLogic : public Singleton<ManagerLogic> {
    unsigned int _score;
    Label *_label;

    list<int> _listRowDeleted;
    int _numRowFall;

public:
    ManagerLogic();

    void increScore(const int &incre);

    void initScore(Layer *layer, const Vec2 &pos, const float &size,
                   const Color3B &color = Color3B::YELLOW);

    void checkRowFull(GridMap& _gridMap);

    bool reSetupBlocksPos(GridMap& _gridMap, const int &row = -1);
};
