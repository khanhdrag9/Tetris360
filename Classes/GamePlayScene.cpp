#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"
#include "ManagerLogic.h"

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


	shared_ptr<GridMap> gridMap = make_shared<GridMap>();
#if ENABLE_GRID
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

	ShapeFactory::getInstance()->init(gridMap);
	ShapeFactory::getInstance()->setLayer(this);
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

	ManagerLogic::getInstance()->setGridMap(ShapeFactory::getInstance()->getTetrisMap());
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
	//auto shapeFalling = ShapeFactory::getInstance()->getShapeIsFalling();
	//if (shapeFalling)
	//{
	//	//calculate touch Pos
	//	Vec2 posTouch = touch->getLocation();
	//	if (posTouch.x > _touchBegin.x)
	//	{
	//		_touchDirection = posTouch;
	//		_touchBegin = _touchDirection;
	//		_direction = RIGHT;
	//	}
	//	else if (posTouch.x < _touchBegin.x)
	//	{
	//		_touchDirection = posTouch;
	//		_touchBegin = _touchDirection;
	//		_direction = LEFT;
	//	}
	//}
	if (_touchBegin == touchNULL)_touchBegin = touch->getLocation();
	_touchMove = touch->getLocation();
}


void GamePlayScene::touchEnded(Touch* touch, Event* event)
{
	refreshTouch();
}


void GamePlayScene::update(float dt)
{
	
}

void GamePlayScene::updateShapeIsFalling(float)
{
	if (ShapeFactory::getInstance()->getShapeIsFalling())
	{
		pos curPos = ShapeFactory::getInstance()->getCurrentPos();

		bool canLeft = true;
		bool canRight = true;
		bool canBLeft = true;
		bool canBRight = true;
		bool canDown = true;
		bool colBottmEdge = false;
		auto collision = ManagerLogic::getInstance()->checkCollision(ShapeFactory::getInstance()->getShapeIsFalling());
		for (auto& c : collision)
		{
			if (c == ManagerLogic::collision::LEFT)canLeft = false;
			else if (c == ManagerLogic::collision::RIGHT)canRight = false;
			else if (c == ManagerLogic::collision::BOTTOM)canDown = false;
			else if (c == ManagerLogic::collision::BOTTOM_LEFT)canBLeft = false;
			else if (c == ManagerLogic::collision::BOTTOM_RIGHT)canBRight = false;
			else if (c == ManagerLogic::collision::BOTTOM_EDGE)colBottmEdge = true;
		}

		//calculate direction
		if (_touchMove != touchNULL && _touchBegin != touchNULL)
		{
			if (_touchMove.x > _touchBegin.x)
			{
				_touchDirection = _touchMove;
				_touchBegin = _touchDirection;
				_direction = RIGHT;
			}
			else if (_touchMove.x < _touchBegin.x)
			{
				_touchDirection = _touchMove;
				_touchBegin = _touchDirection;
				_direction = LEFT;
			}
		}

		switch (_direction)
		{
		case NONE:
			ShapeFactory::getInstance()->setShapePosition(curPos.row, curPos.col);
			break;
		case LEFT:
			if (canLeft && canDown)
			{
				ShapeFactory::getInstance()->setShapePosition(curPos.row, curPos.col - 1);
			}
			break;
		case RIGHT:
			if (canRight && canDown)
			{
				ShapeFactory::getInstance()->setShapePosition(curPos.row, curPos.col + 1);
			}
			break;
		case DOWN:
			break;
		default:
			break;
		}

		if(canDown)
			if ((_direction == LEFT && canLeft && !canBLeft) || (_direction == RIGHT && canRight && !canBRight))
				canDown = false;

		if (canDown && !colBottmEdge)
		{
				ShapeFactory::getInstance()->setShapePosition(curPos.row - 1, ShapeFactory::getInstance()->getCurrentPos().col);
		}

		//collision with Edge
		if (colBottmEdge || !canDown)
		{
			//create new Shape
			ShapeFactory::getInstance()->releaseShape();
			ShapeFactory::getInstance()->createShape();
			ShapeFactory::getInstance()->setShapePosition(19, 5);
			refreshTouch();
		}
	}
}

void GamePlayScene::refreshTouch()
{
	_direction = DOWN;
	_touchBegin = touchNULL;
	_touchDirection = touchNULL;
	_touchMove = touchNULL;
}