#pragma once

#include "Headers.h"

class GamePlayScene : public Layer
{
public:
	GamePlayScene();
	virtual ~GamePlayScene();

	static Scene* createScene();

	CREATE_FUNC(GamePlayScene);

private:
	bool init()		override;
	void update(float dt);

	void createStartShape();
};