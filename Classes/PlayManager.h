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
	Block* _blockIsFalling;
	float _speedFall;
	float _timeCountRotate;
	float _intervalRotate;
	float _lengthEachSquare;
	Size _screenSize;
	Vec2 _origin;
	int _statusGame;
public:
	virtual ~PlayManager();
	static PlayManager* getInstance();

	void createGame();
	void createBlock();
	bool checkFillRow();
	void checkCreateBlock();
	bool checkAvaiableBlock(const Vec2& pos);
	bool canMove();
	void rotateBlocks();
	void rotatePlay();
	bool isRotatedPlay();
	bool isLose();
	void update(float dt);
	void pause();
	void reset();

	CC_SYNTHESIZE(cocos2d::Layer*, _currentLayer, CurrentLayer);
};

