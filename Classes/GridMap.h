#pragma once

#include "Headers.h"

class Block;


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

struct boardGame
{
    float minX;
    float minY;
    float maxX;
    float maxY;
    float width;
    float height;
    
    boardGame(){}
    boardGame(float iminX, float iminY, float imaxX, float imaxY, float iwidth, float iheight):
        minX(iminX),
        minY(iminY),
        maxX(imaxX),
        maxY(imaxY),
        width(iwidth),
        height(iheight)
    {
        
    }
};

class GridMap
{
	Size _screenSize;
	Vec2 _origin;
    pos _axis;

	float _lengthBlock;

	grids_back _gridsBack;
	grids_font _gridsFont;
	grids_posi _gridsPosi;

	unique_ptr<boardGame> _board;
    Node* _currentLayer;
	Node* _node;
    bool _isVertical;
    
    int _row;
    int _col;
    
private:
    void initGirds(const int& row, const int& col);
    void releaseSpriteInNode();
    
public:
	GridMap();
	virtual ~GridMap();

	void init();
    void rotateBoard(Node* layer);

	grids_back& getGirdsBack() { return _gridsBack; }
	grids_font& getGirdsFont() { return _gridsFont; }
	const grids_posi& getGirdsPosition() const { return _gridsPosi; }
	const float& getLengthBlock() const { return _lengthBlock; }
	Node* getNode() { return _node; }
	
//private:
	list<int> findRowFull();
	void deleteRow(const int& row);
    bool isVertical() const {return _isVertical; }
	const pos getSize() const { return pos(_row, _col); }
    unique_ptr<boardGame>& getBoard(){return _board;}

	static int _bottom;
	static int _left;
	static int _right;
};
