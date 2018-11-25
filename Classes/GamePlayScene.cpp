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


	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::onTouchMove, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GamePlayScene::onTouchEnd, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->scheduleUpdate();

	return true;
}

void GamePlayScene::update(float dt)
{
	_manager->update(dt);
}


void GamePlayScene::updateTime(float dt)
{
	// TODO: Add your implementation code here.
}


bool GamePlayScene::onTouchBegan(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	auto space = iTouch->getLocation() - _manager->_blockIsFalling->getPosition();
	_manager->setSpaceBeginTouch(space);
	return true;
}


void GamePlayScene::onTouchMove(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	if (_manager->_blockIsFalling)
	{
		auto newPX = iTouch->getLocation().x - _manager->getSpaceBeginTouch().x;
		_manager->_blockIsFalling->setPositionX(newPX);
	}
}


void GamePlayScene::onTouchEnd(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	_manager->setSpaceBeginTouch(Vec2(0.f, 0.f));
}
