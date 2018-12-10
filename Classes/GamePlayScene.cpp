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

	this->scheduleUpdate();

	return true;
}


void GamePlayScene::createStartShape()
{
	this->addChild(ShapeFactory::getInstance()->createShape()->_node);
	ShapeFactory::getInstance()->setShapePosition(15, 0);
}

void GamePlayScene::update(float dt)
{

}