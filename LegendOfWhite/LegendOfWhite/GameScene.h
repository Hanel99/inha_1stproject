#pragma once
#include "Scene.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Wall.h"

class GameScene : public Scene
{
public:
	GameScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	void SetStartPos(float x, float y);
	void SendLButtonDown(UINT nFlags, CPoint point);
	void ReturnBulletFromGameScene(Bullet* b);

public:
	std::weak_ptr<Gdiplus::Image> bgImg;
private:
	Player* player;
	Enemy* enemy;

	Wall* border;
	std::vector<Wall*> wallVec;
	std::vector<Bullet*> bulletVec;
	std::vector<Object*> objectVec;
};
