#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player()
		: Object(EObjectType::eObjectType_Player)
		, HP(3)
		, ATK(1)
		, SPD(100)
		, SSPD(100)
		, CRI(0)
	{

	}

	void Update(float Delta) override;

	int HP;
	int ATK;
	int SPD;
	int SSPD;
	float CRI;
};