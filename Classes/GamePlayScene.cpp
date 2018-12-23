#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"
#include "ManagerLogic.h"
#include "BlockManager.h"
#include "ShapeAction.h"

GamePlayScene::GamePlayScene() :
	_startTime(0.f),
	_endTime(0.f),
	_speedFall(0.3f),
    _numRowFall(0),
	_gridMap(nullptr)
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

	_screenSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	float boardLen = _gridMap->getLengthBlock() * MAX_COL;
	if (boardLen <= _screenSize.width)
	{
		float rangeFrom0 = (_screenSize.width - boardLen) * 0.5f;

		this->setPosition(rangeFrom0, 0);
	}

	BlockManager::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->setLayer(this);
	createStartShape();
	createListener();

    this->scheduleUpdate();
	this->schedule(schedule_selector(GamePlayScene::updateShapeIsFalling), _speedFall);

	return true;
}

void GamePlayScene::createStartShape()
{
    auto shapeFalling = ShapeFactory::getInstance()->createShape();
	this->addChild(shapeFalling->_node);
	ShapeFactory::getInstance()->setShapePosition(pos(19, 5));	//first position

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
	_touchBegin = touch->getLocation();
	_touchRelease = touch->getLocation();
	return true;
}

void GamePlayScene::touchMoved(Touch* touch, Event* event)
{
	Vec2 touchPos = touch->getLocation();
	float range = touchPos.x - _touchBegin.x;
	float lenghtBlock = _gridMap->getLengthBlock();

	if (range < 0 && abs(range) >= lenghtBlock * 0.75f)
	{
		ShapeFactory::getInstance()->setActionShape(actiontype::SLIDE_LEFT);
		ShapeFactory::getInstance()->updateShape();
		_touchBegin = touchPos;
	}
	else if (range > 0 && abs(range) >= lenghtBlock * 0.75f)
	{
		ShapeFactory::getInstance()->setActionShape(actiontype::SLIDE_RIGHT);
		ShapeFactory::getInstance()->updateShape();
		_touchBegin = touchPos;
	}
}


void GamePlayScene::touchEnded(Touch* touch, Event* event)
{
	Vec2 touchPos = touch->getLocation();
	float rangeW = abs(touchPos.x - _touchRelease.x);
	float rangeH = abs(touchPos.y - _touchRelease.y);
	float lenghtBlock = _gridMap->getLengthBlock();

	if (rangeW <= lenghtBlock * 0.75f && rangeH <= lenghtBlock * 0.75f)
	{
		ShapeFactory::getInstance()->setActionShape(actiontype::ROTATE);
		ShapeFactory::getInstance()->updateShape();
	}

	_touchRelease = Vec2();
}


void GamePlayScene::update(float dt)
{
	
}

void GamePlayScene::updateShapeIsFalling(float)
{
	ShapeFactory::getInstance()->setActionShape(actiontype::FALL);
	if (ShapeFactory::getInstance()->updateShape() == actionResult::COL_BOTTOM)
	{
		ShapeFactory::getInstance()->releaseShape();
		checkRowFull();

		ShapeFactory::getInstance()->createShape();
		ShapeFactory::getInstance()->setShapePosition(pos(19, 5));

	}

}

void GamePlayScene::checkRowFull()
{
	_listRowDeleted = _gridMap->findRowFull();
	if (_listRowDeleted.size() <= 0)
    {
        if(_numRowFall > 0)
        {

            _numRowFall = 0;
        }
        
        return;
    }

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
        
        _numRowFall++;
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
