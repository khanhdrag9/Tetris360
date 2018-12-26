#pragma once

#include "Headers.h"

class Block;

using grids_back = array<array<bool, MAX_COL>, MAX_ROW + ABOVE_ROW>;
using grids_font = array<array<shared_ptr<Block>, MAX_COL>, MAX_ROW + ABOVE_ROW>;
using grids_posi = array<array<Vec2, MAX_COL>, MAX_ROW + ABOVE_ROW>;


//struct boardGame
//{
//	float minX;
//	float minY;
//	float maxX;
//	float maxY;
//	float width;
//	float height;
//};

class GridMap
{
	Size _screenSize;
	Vec2 _origin;

	float _lengthBlock;

	grids_back _gridsBack;
	grids_font _gridsFont;
	grids_posi _gridsPosi;

	//boardGame _board;
	//Node* _node;
    bool _isVertical;
	int _directionFall;
public:
	GridMap();
	virtual ~GridMap();

	void init();

	grids_back& getGirdsBack() { return _gridsBack; }
	grids_font& getGirdsFont() { return _gridsFont; }
	const grids_posi& getGirdsPosition() const { return _gridsPosi; }
	const float& getLengthBlock() const { return _lengthBlock; }
	//Node* getNode() { return _node; }
	
//private:
	list<int> findRowFull();
	void deleteRow(const int& row);
    bool isVertical() const {return _isVertical; }
	inline int getDirectionFall() const { return _directionFall; }
	void setDirectionFall(const int& direct);
};
