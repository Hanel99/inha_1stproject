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
		, eplayerlook(ePlayerLook_Down)
		, addDelta(0)
	{
		width = 128;
		height = 128;
		r = 20;
		center.x = GetX() + 50;
		center.y = GetY() + 50;
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

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