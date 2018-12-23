#pragma once

#include "Headers.h"

class GridMap;

class GamePlayScene : public Layer
{
	Size _screenSize;
	Vec2 _origin;

	Vec2 _touchBegin;
	Vec2 _touchRelease;

	shared_ptr<GridMap> _gridMap;

	list<int> _listRowDeleted;

    int _numRowFall;
	bool _checkRow;
	float _speedFall;
	float _startTime;
	float _endTime;
public:
	const Vec2 touchNULL = Vec2(-1.f, -1.f);

	GamePlayScene();
	virtual ~GamePlayScene();

	static Scene* createScene();

	CREATE_FUNC(GamePlayScene);

private:
	bool init()		override;
	void update(float dt);      override

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
