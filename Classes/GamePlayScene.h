#pragma once

#include "Headers.h"

class GamePlayScene : public Layer
{
	enum direction {
		NONE,
		LEFT,
		RIGHT,
		DOWN
	};
	int _direction;

	Size _screenSize;
	Vec2 _origin;

	Vec2 _touchBegin;
	Vec2 _touchDirection;

	float _startTime;
	float _endTime;
public:
	GamePlayScene();
	virtual ~GamePlayScene();

	static Scene* createScene();

	CREATE_FUNC(GamePlayScene);

private:
	bool init()		override;
	void update(float dt);

	void createStartShape();
	void createListener();

	bool touchBegan(Touch* touch, Event* event);
	void touchMoved(Touch* touch, Event* event);
	void touchEnded(Touch* touch, Event* event);

	void updateShapeIsFalling(float);
};