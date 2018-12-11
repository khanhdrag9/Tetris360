#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"

GamePlayScene::GamePlayScene()
{

}

GamePlayScene::~GamePlayScene()
{

}

Scene* GamePlayScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = GamePlayScene::create();
	
	scene->addChild(layer);

	return scene;
}

bool GamePlayScene::init()
{
	if (!Layer::init())
		return false;


#if ENABLE_GRID
	shared_ptr<GridMap> gridMap = make_shared<GridMap>();
	string pnumber;
	for (int row = 0; row < MAX_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			pnumber = to_string(row) + to_string(col);
			auto label = Label::createWithTTF(pnumber, FONT_ARIAL, 20);
			label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			label->setPosition(gridMap->getGirdsPosition()[row][col]);
			this->addChild(label);
		}
	}
#endif

	createStartShape();
	createListener();

	this->scheduleUpdate();

	return true;
}

void GamePlayScene::createStartShape()
{
	this->addChild(ShapeFactory::getInstance()->createShape()->_node);
	ShapeFactory::getInstance()->setShapePosition(19, 5);
}

void GamePlayScene::createListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GamePlayScene::touchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GamePlayScene::touchBegan(Touch* touch, Event* event)
{

	return true;
}

void GamePlayScene::touchMoved(Touch* touch, Event* event)
{

}

void GamePlayScene::touchEnded(Touch* touch, Event* event)
{

}

float t = 0.f;
int i = 3;

void GamePlayScene::update(float dt)
{
	t += dt;
	if (dt > 0.2f)
	{
		dt = 0.f;
		
		if (ShapeFactory::getInstance()->getShapeIsFalling())
		{
			auto currentPos = ShapeFactory::getInstance()->getCurrentPos();
			if (currentPos.row == 1)
			{
				ShapeFactory::getInstance()->createShape();
				ShapeFactory::getInstance()->releaseShape();
				auto r = ShapeFactory::getInstance()->getTetrisMap()->findRowFull();
				for (auto i : r)
					ShapeFactory::getInstance()->getTetrisMap()->deleteRow(i);
				ShapeFactory::getInstance()->setShapePosition(i, 5);
				i += 2;
			}
			else
			{
				ShapeFactory::getInstance()->setShapePosition(currentPos.row - 1, currentPos.col);
				
			}
		}
	}
}