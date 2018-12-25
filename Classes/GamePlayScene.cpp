#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"
#include "ManagerLogic.h"
#include "BlockManager.h"
#include "ShapeAction.h"
#include "BackgroundLayer.h"

const pos GamePlayScene::_createPos = pos(MAX_ROW - 1, MAX_COL / 2);

GamePlayScene::GamePlayScene() :
    _speedFall(0.5f),
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
	auto layer = GamePlayScene::create();
    layer->_bgLayer = BackgroundLayer::create();
    layer->setupForBgLayer();
	
    scene->addChild(layer->_bgLayer, 0);
	scene->addChild(layer, 1);

	return scene;
}

bool GamePlayScene::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	_gridMap = make_shared<GridMap>();
#if ENABLE_GRID
	string pnumber;
	for (int row = 0; row < MAX_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			pnumber = to_string(row) + to_string(col);
			auto label = Label::createWithTTF(pnumber, FONT_ARIAL, 13);
			label->setPosition(_gridMap->getGirdsPosition()[row][col]);
			this->addChild(label);
		}
	}
#endif
    
    setPositionLayer();
	BlockManager::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->setLayer(this);
	createStartShape();
	createListener();

    this->scheduleUpdate();
	this->schedule(schedule_selector(GamePlayScene::updateShapeIsFalling), _speedFall);

	return true;
}

void GamePlayScene::setPositionLayer()
{
    _screenSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    float boardLenW = _gridMap->getLengthBlock() * MAX_COL;
    float boardLenH = _gridMap->getLengthBlock() * MAX_ROW;
    float px = 0.f, py = 0.f;
    if (boardLenW <= _screenSize.width)
    {
        px = (_screenSize.width - boardLenW) * 0.5f;
    }
    if (boardLenH <= _screenSize.height)
    {
        py = (_screenSize.height - boardLenH) * 0.5f;
    }
    this->setPosition(px + _origin.x, py + _origin.y);
    
    _boardSize = Size(boardLenW, boardLenH);
    _posBoard = Vec2(px, py);
    
    this->setContentSize(Size(_boardSize.width, _boardSize.height));
    this->setScale(0.9f);
    //set background gameplay
//    Sprite* bg = Sprite::create(BG_PATH, Rect(0, 0, boardLenW, boardLenH));
//    float ratioX = _boardSize.width / (float) bg->getBoundingBox().size.width;
//    float ratioY = _boardSize.height / (float) bg->getBoundingBox().size.height;
//    bg->setScale(ratioX, ratioY);
//
//    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
//    bg->setPosition(0, 0);
   // this->addChild(bg, 0);
}

void GamePlayScene::setupForBgLayer()
{
    Vec2 posScore;
    if(_gridMap->isVertical())
        posScore = Vec2(40 + _origin.x, _screenSize.height * 0.5f + _origin.y);
    else
        posScore = Vec2(_screenSize.width * 0.5f + _origin.x, _screenSize.height - 40 + _origin.y);
        
        
    ManagerLogic::getInstance()->initScore(_bgLayer, posScore, 75.f, Color3B::RED);
}

void GamePlayScene::createStartShape()
{
    auto shapeFalling = ShapeFactory::getInstance()->createShape();
	this->addChild(shapeFalling->_node);
	ShapeFactory::getInstance()->setShapePosition(_createPos);	//first position

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
    _startTime = chrono::high_resolution_clock::now();
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

    _endTime = chrono::high_resolution_clock::now();
    
    float coutTime = chrono::duration_cast<chrono::milliseconds>(_endTime - _startTime).count();
    CCLOG("coutime on release touch : %f", coutTime);
    
	if (rangeW <= lenghtBlock * 0.75f && rangeH <= lenghtBlock * 0.75f)
	{
		ShapeFactory::getInstance()->setActionShape(actiontype::ROTATE);
		ShapeFactory::getInstance()->updateShape();
	}
    else if(coutTime <= 700.f && rangeH > lenghtBlock * 2.f && rangeW < lenghtBlock * 0.75)
    {
        ShapeFactory::getInstance()->setActionShape(actiontype::FALLNOW);
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
		ShapeFactory::getInstance()->setShapePosition(_createPos);

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
        
        ManagerLogic::getInstance()->increScore(1);
        
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
