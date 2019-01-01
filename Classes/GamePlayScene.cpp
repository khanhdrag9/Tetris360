#include "GamePlayScene.h"
#include "ShapeFactory.h"
#include "Block.h"
#include "Shape.h"
#include "GridMap.h"
#include "ManagerLogic.h"
#include "BlockManager.h"
#include "ShapeAction.h"
#include "BackgroundLayer.h"

const float GamePlayScene::_ratioMove = 0.85f;


GamePlayScene::GamePlayScene() :
    _speedFall(0.5f),
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
	
    scene->addChild(layer, z::scene);
    scene->addChild(layer->_bgLayer, z::background);

	return scene;
}

bool GamePlayScene::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	_gridMap = make_shared<GridMap>();
    this->addChild(_gridMap->getNode(), z::item);
 //   _gridMap->setDirectionFall(direction::LEFT);
#if ENABLE_GRID
	string pnumber;
	for (int row = 0; row < _gridMap->getSize().row; row++)
	{
		for (int col = 0; col < _gridMap->getSize().col; col++)
		{
			pnumber = to_string(row) + to_string(col);
			auto label = Label::createWithTTF(pnumber, FONT_ARIAL, 13);
			label->setPosition(_gridMap->getGirdsPosition()[row][col]);
			this->addChild(label);
		}
	}
#endif
    _screenSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    
    setPositionLayer();
	BlockManager::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->init(_gridMap);
	ShapeFactory::getInstance()->setLayer(this);
	createStartShape();
	createListener();

    this->scheduleUpdate();
	this->schedule(schedule_selector(GamePlayScene::updateShapeIsFalling), _speedFall);
	
	this->schedule(schedule_selector(GamePlayScene::rotateBoard), 30.f);

	return true;
}

void GamePlayScene::setPositionLayer()
{
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
    
    _boardSize = Rect(px + _origin.x, py + _origin.y, boardLenW, boardLenH);
    //_boardSize = Size(boardLenW, boardLenH);
    _posBoard = Vec2(px, py);
    
    this->setContentSize(Size(_boardSize.size.width, _boardSize.size.height));
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
//    Vec2 posScore;
//    if(_gridMap->isVertical())
//        posScore = Vec2(40 + _origin.x, _screenSize.height * 0.5f + _origin.y);
//    else
//        posScore = Vec2(_screenSize.width * 0.5f + _origin.x, _screenSize.height - 40 + _origin.y);
//        
//        
//    ManagerLogic::getInstance()->initScore(_bgLayer, posScore, 75.f, Color3B::RED);
    
    _bgLayer->initSoild(_boardSize);
}

void GamePlayScene::createStartShape()
{
	auto sboard = _gridMap->getSize();
	_createPos = pos(sboard.row - 1, sboard.col / 2);
    auto shapeFalling = ShapeFactory::getInstance()->createShape();
	this->addChild(shapeFalling->_node, z::item);
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

	if (range < 0 && abs(range) >= lenghtBlock * _ratioMove)
	{
		ShapeFactory::getInstance()->setActionShape(actiontype::SLIDE_LEFT);
		ShapeFactory::getInstance()->updateShape();
		_touchBegin = touchPos;
	}
	else if (range > 0 && abs(range) >= lenghtBlock * _ratioMove)
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
    //CCLOG("coutime on release touch : %f", coutTime);
    
	if (rangeW <= lenghtBlock * _ratioMove && rangeH <= lenghtBlock * _ratioMove)
	{
		ShapeFactory::getInstance()->setActionShape(actiontype::ROTATE);
		ShapeFactory::getInstance()->updateShape();
	}
    else if(coutTime <= 700.f && rangeH > lenghtBlock * 2.f && rangeW < lenghtBlock * _ratioMove)
    {
        ShapeFactory::getInstance()->setActionShape(actiontype::FALLNOW);
        ShapeFactory::getInstance()->updateShape();
    }
    
	_touchRelease = Vec2();
}


void GamePlayScene::update(float dt)
{
    if(ShapeFactory::_pause)
    {
        for(auto& block : BlockManager::getInstance()->getBlockPool())
        {
            auto pos = _gridMap->getNode()->convertToWorldSpace(block->_sprite->getPosition());
            if(!_boardSize.containsPoint(pos))
                block->_sprite->setVisible(false);
            else
                block->_sprite->setVisible(true);
        }
    }
}

void GamePlayScene::updateShapeIsFalling(float)
{
	ShapeFactory::getInstance()->setActionShape(actiontype::FALL);
	if (ShapeFactory::getInstance()->updateShape() == actionResult::COL_BOTTOM)
	{
		ShapeFactory::getInstance()->releaseShape();
		//checkRowFull();
		ManagerLogic::getInstance()->checkRowFull(*_gridMap);

		ShapeFactory::getInstance()->createShape();
		ShapeFactory::getInstance()->setShapePosition(_createPos);
        
	}

}


void GamePlayScene::rotateBoard(float)
{
    _gridMap->rotateBoard(this);
    
}
