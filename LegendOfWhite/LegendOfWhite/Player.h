#pragma once
#include "Object.h"
#include "common.h"

class Player : public Object
{
public:
	Player()
		: Object(EObjectType::eObjectType_Player)
		, HP(3)
		, ATK(1)
		, SPD(300)
		, SSPD(100)
		, CRI(0.0f)
		, LV(1)
		, EXP(0)
		, skillPoint(0)
		, eplayerlook(ePlayerLook_Down)
		, addDelta(0)
	{
		width = 60;
		height = 60;
		r = 20;
		center.x = GetX() + 30;
		center.y = GetY() + 30;
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	int LV;
	int EXP;
	int skillPoint;

	int HP;
	int ATK;
	int SPD;
	int SSPD;
	float CRI;
	CPoint center;

	float addDelta;

	EPlayerLook eplayerlook;
	std::weak_ptr<Gdiplus::Image> playerimg;
};