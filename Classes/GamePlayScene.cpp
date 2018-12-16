#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"
#include "ManagerLogic.h"
#include "BlockManager.h"
#include "ShapeAction.h"

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

	srand(time(NULL));

	_gridMap = make_shared<GridMap>();
#if ENABLE_GRID
	string pnumber;
	for (int row = 0; row < MAX_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			pnumber = to_string(row) + to_string(col);
			auto label = Label::createWithTTF(pnumber, FONT_ARIAL, 20);
			label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			label->setPosition(_gridMap->getGirdsPosition()[row][col]);
			this->addChild(label);
		}
	}
#endif

	BlockManager::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->init(_gridMap);
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
	ShapeFactory::getInstance()->setShapePosition(19, 5);	//first position
	_direction = DOWN;

	ManagerLogic::getInstance()->setGridMap(_gridMap);
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


void GamePlayScene::update(float dt)
{
	
}

void GamePlayScene::updateShapeIsFalling(float)
{
	ShapeFactory::getInstance()->updateShape();
}

void GamePlayScene::rotateShape()
{
	
}

void GamePlayScene::checkRowFull()
{
	_listRowDeleted = _gridMap->findRowFull();
	if (_listRowDeleted.size() <= 0)return;

	while (_listRowDeleted.size() > 0)
	{
		int row = *(_listRowDeleted.begin());
		_gridMap->deleteRow(row);
		if (reSetupBlocksPos(row))
		{
			_listRowDeleted.pop_front();
			bool avableDrop = all_of(_listRowDeleted.begin(), _listRowDeleted.end(), [](int& row) {
				row--;
				return row >= 0;
			});
			if (!avableDrop)break;
		}
	}

	checkRowFull();
}

bool GamePlayScene::reSetupBlocksPos(const int& row)
{
	if (row == -1)
	{
		if (_listRowDeleted.size() > 0)
		{
			//feature optimize code...
			
		}
		return false;
	}
	else if(row >= 0)
	{
		int aboveRow = row + 1;
		while (aboveRow <= MAX_ROW)
		{
			for (auto& block : _gridMap->getGirdsFont()[aboveRow])
			{
				if (block)
				{
					pos newPos = pos(block->_coord.row - 1, block->_coord.col);
					BlockManager::getInstance()->moveBlock(block, newPos);
				}
			}
			aboveRow++;
		}
		return true;
	}

	return false;
}

void GamePlayScene::refreshTouch()
{
	_direction = DOWN;
	_touchBegin = touchNULL;
	_touchDirection = touchNULL;
	_touchMove = touchNULL;
}