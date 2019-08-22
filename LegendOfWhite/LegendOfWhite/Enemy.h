#pragma once
#include "Object.h"
#include "common.h"

class Enemy : public Object
{
public:
	Enemy()
		: Object(EObjectType::eObjectType_Enemy)
		, EnemyType(EEnemyType::eEnemyType_Bird)
		, EnemyNum(1)
		, HP(10)
		, ATK(1)
		, SPD(1)
		, SSPD(1)
		, EXP(1000)
		, addDelta(0.0f)
		, addDelta2(0.0f)
	{
		SetX(500);
		SetY(500);
		width = 10;
		height = 10;
		r = width/2;
		center.x = GetX() + r;
		center.y = GetY() + r;
	}
	Enemy(EEnemyType enemytype, int enemynum, int hp, int x, int y)
		: Object(EObjectType::eObjectType_Enemy)
		, EnemyType(enemytype)
		, EnemyNum(enemynum)
		, HP(hp)
		, ATK(1)
		, SPD(100)
		, SSPD(10)
		, EXP(1000)
		, addDelta(0.0f)
		, addDelta2(0.0f)
	{
		SetX(x);
		SetY(y);
		if (enemytype == eEnemyType_Boss)
		{
			width = 140;
			height = 140;
		}
		else
		{
			width = 80;
			height = 80;
		}
		r = width / 2;
		center.x = GetX() + r;
		center.y = GetY() + r;
	}

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

