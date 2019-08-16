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
		, canmove(true)
	{
		width = 128;
		height = 128;
		center.x = GetX() + width / 2;
		center.y = GetY() + height / 2;
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
	bool canmove;

	EPlayerLook eplayerlook;
	std::weak_ptr<Gdiplus::Image> playerimg;
};