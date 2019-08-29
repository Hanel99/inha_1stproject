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
	~GameScene();

	void SceneSetting();
	virtual void Init()override;
	virtual void Release() override;
	virtual void Update(float Delta)override;
	virtual void Render(Gdiplus::Graphics* MemG)override;
	void SendLButtonDown(UINT nFlags, CPoint point)override;
	virtual void SendRButtonDown(UINT nFlags, CPoint point)override;

	void UIRender(Gdiplus::Graphics* MemG);
	void SetStartPos(float x, float y);	
	void ReturnBulletFromGameScene(Bullet* b);
	void BulletCollCheck(Bullet* b);
	void IsPlayerColl(Player* p, float Delta);

	Gdiplus::SolidBrush* B;
	Gdiplus::SolidBrush* B_Exp;
	Gdiplus::SolidBrush* B_Chapter;
	Gdiplus::Font* F_24;
	Gdiplus::Font* F_30;


	void EnemyPattern1(Enemy* it);
	void EnemyPattern2(Enemy* it);
	void EnemyPattern3(Enemy* it);
	void EnemyPattern4(Enemy* it);
	void EnemyPattern5(Enemy* it);
	void EnemyPattern6(Enemy* it);

	std::weak_ptr<Gdiplus::Image> bgImg;
	std::weak_ptr<Gdiplus::Image> tabImg;
	std::weak_ptr<Gdiplus::Image> uibgImg;

private:
	Player* player;
	Enemy* enemy;
	NextStage* nextStageBoard;
	bool isAllEnemyDead;

	std::vector<Wall*> wallVec;
	std::vector<Bullet*> bulletVec;
	std::vector<Enemy*> enemyVec;
	Gdiplus::Bitmap* bm;

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