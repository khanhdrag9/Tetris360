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
	_manager->setBeginTouch(iTouch->getLocation());
	_manager->setPreviousTouchMove(iTouch->getLocation());

	return true;
}


void GamePlayScene::onTouchMove(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	if (_manager->_blockIsFalling)
	{
		auto touchPos = iTouch->getLocation();
		auto sideEachSquare = _manager->_blockIsFalling->getSideLength();

		if (_manager->getDirectionBlockMove() == 0)
		{
			if (touchPos.x < _manager->getBeginTouch().x - sideEachSquare)
			{
				_manager->setDirectionBlockMove(PlayManager::typeMove::LEFT);
			}
			else if (touchPos.x > _manager->getBeginTouch().x + sideEachSquare)
			{
				_manager->moveBlockFalling(PlayManager::typeMove::RIGHT);
			}
			_manager->setPreviousTouchMove(touchPos);
		}
		else if (_manager->getDirectionBlockMove() == PlayManager::typeMove::LEFT)
		{
			if (touchPos.x > _manager->getPreviousTouchMove().x + sideEachSquare)
			{
				_manager->moveBlockFalling(PlayManager::typeMove::RIGHT);
				_manager->setPreviousTouchMove(touchPos);
			}
		}
		else if (_manager->getDirectionBlockMove() == PlayManager::typeMove::RIGHT)
		{
			if (touchPos.x < _manager->getPreviousTouchMove().x - sideEachSquare)
			{
				_manager->moveBlockFalling(PlayManager::typeMove::LEFT);
				_manager->setPreviousTouchMove(touchPos);
			}
		}
	}
}


void GamePlayScene::onTouchEnd(cocos2d::Touch* iTouch, cocos2d::Event* iEvent)
{
	_manager->setDirectionBlockMove(0);
	_manager->setPreviousTouchMove(Vec2(-1.f, -1.f));
	_manager->setBeginTouch(Vec2(0.f,0.f));
}
