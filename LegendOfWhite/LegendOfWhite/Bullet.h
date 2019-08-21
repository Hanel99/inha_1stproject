#pragma once
#include "Object.h"
#include "GameData.h"

#define DefaultSPD 500

class Bullet : public Object
{
public:
	Bullet()
		: Object(EObjectType::eObjectType_PBullet)
		, SPD(DefaultSPD)
		, damage(1)
		, SPDY(1)
		, SPDX(1)
	{
		width = 20;
		height = 20;
		r = width/2;
		center.x = GetX() + r;
		center.y = GetY() + r;
	}
	Bullet(int px, int py, int clickx, int clicky, EObjectType type)
		: Object(type)
		, damage(GameData::GetInstance()->player->ATK)
		, SPD(DefaultSPD)
	{
		width = 20;
		height = 20;
		SPDSet(px, py, clickx, clicky);
		SetX(px);
		SetY(py);		
		r = width / 2;
		center.x = GetX() + r;
		center.y = GetY() + r;
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SPDSet(int px, int py, int clickx, int clicky);
	void BulletInit(int px, int py, int clickx, int clicky, EObjectType type);
	void BulletReset();
	CPoint center;

	Gdiplus::Rect* rec;

private:
	int damage;
	int SPD;
	float SPDX;
	float SPDY;
	bool updown = false;

	std::weak_ptr<Gdiplus::Image> bulletimg;
};