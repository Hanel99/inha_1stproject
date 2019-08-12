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
		, SPD(100)
		, SSPD(100)
		, CRI(0)
		, width(90)
		, height(90)
		, eplayerlook(ePlayerLook_Down)
	{

	}

	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	int HP;
	int ATK;
	int SPD;
	int SSPD;
	float CRI;

	int width;
	int height;
	EPlayerLook eplayerlook;
	std::weak_ptr<Gdiplus::Image> playerimg;
};