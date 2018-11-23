#pragma once
#include "cocos2d.h"
#include "PlayManager.h"

class GamePlayScene :
	public cocos2d::Layer
{
public:
	GamePlayScene();
	virtual ~GamePlayScene();
	static cocos2d::Scene* createScene();
	bool init();
	void update(float dt) override;
	void updateTime(float dt);
	bool onTouchBegan(cocos2d::Touch* iTouch, cocos2d::Event* iEvent);
	void onTouchMoved(cocos2d::Touch* iTouch, cocos2d::Event* iEvent);
	void onTouchEnd(cocos2d::Touch* iTouch, cocos2d::Event* iEvent);
private:
	PlayManager* _manager;
};

