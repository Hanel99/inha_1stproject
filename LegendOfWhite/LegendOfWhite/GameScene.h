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

public:
	std::weak_ptr<Gdiplus::Image> bgImg;
private:
	Player* player;
	Enemy* enemy;

	std::vector<Object*> objectVec;
};
