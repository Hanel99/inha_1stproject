#pragma once
#include "Object.h"
#include "common.h"

class Enemy : public Object
{
public:
	Enemy()
		: Object(EObjectType::eObjectType_Enemy)
		, EnemyType(EEnemyType::eEnemyType_Bird)
		, EnemyNum(0)
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
		, SSPD(100)
	{

	}

	void Update(float Delta) override;

	EEnemyType EnemyType;
	int EnemyNum;
	int HP;
	int ATK;
	int SPD;
	int SSPD;
};

