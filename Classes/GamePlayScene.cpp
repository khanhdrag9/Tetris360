#include "GamePlayScene.h"
#include "Defines.h"

GamePlayScene::GamePlayScene():
	_manager(PlayManager::getInstance())
{

}


GamePlayScene::~GamePlayScene()
{
	delete _manager;
}


cocos2d::Scene* GamePlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePlayScene::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlayScene::init()
{
	if (!Layer::init())
		return false;

	_manager->setCurrentLayer(this);
	_manager->createGame();
	_manager->createBlock();


	return true;
}

void GamePlayScene::update(float dt)
{
	// TODO: Add your implementation code here.
}


void GamePlayScene::updateTime(float dt)
{
	// TODO: Add your implementation code here.
}


bool GamePlayScene::onTouchBegan(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	// TODO: Add your implementation code here.
	return false;
}


void GamePlayScene::onTouchMoved(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	// TODO: Add your implementation code here.
}


void GamePlayScene::onTouchEnd(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	// TODO: Add your implementation code here.
}
