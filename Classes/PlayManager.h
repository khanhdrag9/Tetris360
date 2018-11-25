#pragma once
#include "cocos2d.h"
#include <vector>
#include "Block.h"

USING_NS_CC;

class PlayManager
{
	PlayManager();
	
	static PlayManager* _instance;

	std::vector<Square*> _listSquares;
	std::vector<Vec2> _listColumn;
	float _speedFall;
	float _timeCountRotate;
	float _intervalRotate;
	float _lengthEachSquare;
	Size _screenSize;
	Vec2 _origin;
	int _statusGame;
public:
	enum typeCollision {
		NONE,
		BOTTOM_EDGE,
		RIGHT_EDGE,
		LEFT_EDGE,
		OTHER_BLOCK
	}typeCollision;


	virtual ~PlayManager();
	static PlayManager* getInstance();

	void createGame();
	void createBlock();
	void putBlockToList();	//put squares of block to list
	bool checkFillRow();
	void checkCreateBlock();
	bool checkAvaiableBlock(const Vec2& pos);
	int canMove(const cocos2d::Vec2& newPos, 
		const cocos2d::Size& sizeBlock = cocos2d::Size(0.f, 0.f), 
		const cocos2d::Vec2& ratioAnchor = cocos2d::Vec2(0.f, 0.f));
	void rotateBlocks();
	void rotatePlay();
	bool isRotatedPlay();
	bool isLose();
	void update(float dt);
	void pause();
	void reset();

	Block* _blockIsFalling;
	CC_SYNTHESIZE(cocos2d::Vec2, _spaceBeginTouch, SpaceBeginTouch);
	CC_SYNTHESIZE(cocos2d::Layer*, _currentLayer, CurrentLayer);
};

