#pragma once
#include "Scene.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"

class GameScene : public Scene
{
public:
	GameScene();

	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

private:
	Player* player;
	Enemy* enemy;

	std::vector<Object*> objectVec;
};
