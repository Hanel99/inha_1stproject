#pragma once
#include "Object.h"
#include "common.h"

class Enemy : public Object
{
public:
	Enemy();
	Enemy(EEnemyType enemytype, int enemynum, int hp, int x, int y);
	~Enemy();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	EEnemyType EnemyType;
	int EnemyNum;
	int HP;
	int ATK;
	int SPD;
	int SSPD;
	int EXP;
	CPoint center;
	float addDelta;
	float addDelta2;

	std::weak_ptr<Gdiplus::Image> enemyimg;
};

