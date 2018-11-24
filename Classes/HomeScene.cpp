#include "HomeScene.h"
#include "GamePlayScene.h"

cocos2d::Scene* HomeScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = HomeScene::create();
	scene->addChild(layer);
	return scene;
}

bool HomeScene::init()
{
	if (!Layer::init())
		return false;

	goToPlay();

	return true;
}

void HomeScene::goToPlay()
{
	auto scene = GamePlayScene::createScene();
	auto trans = cocos2d::TransitionFade::create(0.7f, scene);
	cocos2d::Director::getInstance()->replaceScene(trans);
}