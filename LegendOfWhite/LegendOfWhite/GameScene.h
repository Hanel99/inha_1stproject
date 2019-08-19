#pragma once
#include "Scene.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Wall.h"
#include "NextStage.h"

class GameScene : public Scene
{
public:
	GameScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void StringRender(Gdiplus::Graphics* MemG);

	void SetStartPos(float x, float y);
	void SendLButtonDown(UINT nFlags, CPoint point);
	void SendRButtonDown(UINT nFlags, CPoint point);
	void ReturnBulletFromGameScene(Bullet* b);
	void BulletCollCheck(Bullet* b);
	void IsPlayerColl(Player* p);

public:
	std::weak_ptr<Gdiplus::Image> bgImg;
private:
	Player* player;
	Enemy* enemy;
	NextStage* nextStageBoard;
	bool isAllEnemyDead;
	float addDelta;
	float addDelta2;

	std::vector<Wall*> wallVec;
	std::vector<Bullet*> bulletVec;
	std::vector<Enemy*> enemyVec;
};
