#pragma once

#include "Headers.h"

class GridMap;
class BackgroundLayer;

class GamePlayScene : public LayerColor
{
    BackgroundLayer* _bgLayer;
    
	Size _screenSize;
	Vec2 _origin;
    Size _boardSize;
    Vec2 _posBoard;

	Vec2 _touchBegin;
	Vec2 _touchRelease;

	shared_ptr<GridMap> _gridMap;

	list<int> _listRowDeleted;

    int _numRowFall;
	float _speedFall;
    
    chrono::steady_clock::time_point _startTime;
    chrono::steady_clock::time_point _endTime;
public:
	const Vec2 touchNULL = Vec2(-1.f, -1.f);

	GamePlayScene();
	virtual ~GamePlayScene();

	static Scene* createScene();

	CREATE_FUNC(GamePlayScene);

private:
    static const pos _createPos;
    
	bool init()		override;
    void update(float dt)      override;

    void setupForBgLayer();
    
    void setPositionLayer();
	void createStartShape();
	void createListener();

	bool touchBegan(Touch* touch, Event* event);
	void touchMoved(Touch* touch, Event* event);
	void touchEnded(Touch* touch, Event* event);

	void updateShapeIsFalling(float);
	void rotateShape();
	void refreshTouch();
	void checkRowFull();
	bool reSetupBlocksPos(const int& row = -1);
};
