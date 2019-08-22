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

	void SceneSetting();
	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void UIRender(Gdiplus::Graphics* MemG);

	void SetStartPos(float x, float y);
	void SendLButtonDown(UINT nFlags, CPoint point);
	void SendRButtonDown(UINT nFlags, CPoint point);
	void ReturnBulletFromGameScene(Bullet* b);
	void BulletCollCheck(Bullet* b);
	void IsPlayerColl(Player* p, float Delta);

	void EnemyPattern1(Enemy* it);
	void EnemyPattern2(Enemy* it);
	void EnemyPattern3(Enemy* it);
	void EnemyPattern4(Enemy* it);
	void EnemyPattern5(Enemy* it);


	std::weak_ptr<Gdiplus::Image> bgImg;
	std::weak_ptr<Gdiplus::Image> tabImg;
	std::weak_ptr<Gdiplus::Image> uibgImg;
	std::weak_ptr<Gdiplus::Image> stagebgImg;

private:
	Player* player;
	Enemy* enemy;
	NextStage* nextStageBoard;
	bool isAllEnemyDead;

	std::vector<Wall*> wallVec;
	std::vector<Bullet*> bulletVec;
	std::vector<Enemy*> enemyVec;
	Gdiplus::Bitmap* bm;
	Gdiplus::Bitmap* bm2;

	int pattern = 0;
	int p2x = 7;
	int p2y = 1;
	bool p2xup = false;
	bool p2yup = true;

	int p4x = 31;
	int p4y = 1;
	bool p4xup = false;
	bool p4yup = true;



};
