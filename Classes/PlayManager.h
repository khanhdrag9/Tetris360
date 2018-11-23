#pragma once
#include "cocos2d.h"
#include <vector>
#include "Block.h"

USING_NS_CC;

class PlayManager
{
	PlayManager();
	
	static PlayManager* _instance;

	std::vector<Block*> _listBlock;
	Block* _blockIsFalling;
	float _timeCountRotate;
	float _intervalRotate;
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
	bool canMove();
	void rotateBlocks();
	void rotatePlay();
	bool isRotatedPlay();
	bool isLose();
	void pause();
	void reset();
};

