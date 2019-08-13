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
		//, width(128)
		//, height(128)
		, eplayerlook(ePlayerLook_Down)
	{
		width = 128;
		height = 128;
	}

	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	int HP;
	int ATK;
	int SPD;
	int SSPD;
	float CRI;

	EPlayerLook eplayerlook;
	std::weak_ptr<Gdiplus::Image> playerimg;
};