#pragma once

#include "Headers.h"

class Block;

//using grids_back = array<array<bool, MAX_COL>, MAX_ROW + ABOVE_ROW>;
//using grids_font = array<array<shared_ptr<Block>, MAX_COL>, MAX_ROW + ABOVE_ROW>;
//using grids_posi = array<array<Vec2, MAX_COL>, MAX_ROW + ABOVE_ROW>;

class grids_back : public grid<bool>
{
public:
    grids_back(){}
    void init(const int& row, const int& col);
};

class grids_font : public grid<shared_ptr<Block>>
{
public:
    grids_font(){}
    void init(const int& row, const int& col);
};

class grids_posi : public grid<Vec2>
{
public:
    grids_posi(){}
    void init(const int& row, const int& col);
};

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
    
    int _row;
    int _col;
    
private:
    void initGirds(const int& row, const int& col);
    void rotateBoard();
    
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
