#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"

GamePlayScene::GamePlayScene():
	_direction(0),
	_startTime(0.f),
	_endTime(0.f)
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
	this->schedule(schedule_selector(GamePlayScene::updateShapeIsFalling), 0.3);

	return true;
}

void GamePlayScene::createStartShape()
{
	_screenSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	this->addChild(ShapeFactory::getInstance()->createShape()->_node);
	ShapeFactory::getInstance()->setShapePosition(19, 5);
	_direction = DOWN;
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
	_touchBegin = touch->getLocation();
	return true;
}

void GamePlayScene::touchMoved(Touch* touch, Event* event)
{
	auto shapeFalling = ShapeFactory::getInstance()->getShapeIsFalling();
	if (shapeFalling)
	{
		//calculate touch Pos
		Vec2 posTouch = touch->getLocation();
		if (posTouch.x > _touchBegin.x)
		{
			_touchDirection = posTouch;
			_touchBegin = _touchDirection;
			_direction = RIGHT;
		}
		else if (posTouch.x < _touchBegin.x)
		{
			_touchDirection = posTouch;
			_touchBegin = _touchDirection;
			_direction = LEFT;
		}
	}
}

void GamePlayScene::touchEnded(Touch* touch, Event* event)
{
	_direction = DOWN;
	_touchBegin = Vec2(-1.f, -1.f);
	_touchDirection = Vec2(-1.f, -1.f);
}


void GamePlayScene::update(float dt)
{
	
}

void GamePlayScene::updateShapeIsFalling(float)
{
	if (ShapeFactory::getInstance()->getShapeIsFalling())
	{
		pos curPos = ShapeFactory::getInstance()->getCurrentPos();
		switch (_direction)
		{
		case NONE:
			ShapeFactory::getInstance()->setShapePosition(curPos.row, curPos.col);
			break;
		case LEFT:
			ShapeFactory::getInstance()->setShapePosition(curPos.row - 1, curPos.col - 1);
			break;
		case RIGHT:
			ShapeFactory::getInstance()->setShapePosition(curPos.row - 1, curPos.col + 1);
			break;
		case DOWN:
			ShapeFactory::getInstance()->setShapePosition(curPos.row - 1, curPos.col);
			break;
		default:
			break;
		}
	}
}