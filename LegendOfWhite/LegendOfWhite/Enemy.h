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
		, HP(1)
		, ATK(1)
		, SPD(1)
		, SSPD(1)
	{

	}
	Enemy(EEnemyType enemytype, int enemynum, int hp)
		: Object(EObjectType::eObjectType_Enemy)
		, EnemyType(enemytype)
		, EnemyNum(enemynum)
		, HP(hp)
		, ATK(1)
		, SPD(100)
		, SSPD(10)
	{

	}

	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	EEnemyType EnemyType;
	int EnemyNum;
	int HP;
	int ATK;
	int SPD;
	int SSPD;
};
