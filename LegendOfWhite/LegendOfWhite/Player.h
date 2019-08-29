#pragma once
#include "Object.h"
#include "common.h"

class Player : public Object
{
public:
	Player();
	~Player();

	void Init();
	void Release();

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
	Gdiplus::Rect* rec;

	bool issafe = false;
	EPlayerLook eplayerlook;
	std::weak_ptr<Gdiplus::Image> playerimg;
};