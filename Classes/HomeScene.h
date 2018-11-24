#pragma once
#include "cocos2d.h"

class HomeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	void goToPlay();

	CREATE_FUNC(HomeScene);
};