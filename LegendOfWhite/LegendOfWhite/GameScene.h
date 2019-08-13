#pragma once
#include "Scene.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class GameScene : public Scene
{
public:
	GameScene();


	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	void SetStartPos(int x, int y);
	void SetStartPos(CPoint cp);

public:
	std::weak_ptr<Gdiplus::Image> bgImg;
private:
	Player* player;
	Enemy* enemy;
	Bullet* bul;
	std::vector<Object*> objectVec;
};
