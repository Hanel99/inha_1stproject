#include "pch.h"
#include "Object.h"
#include "Bullet.h"

Bullet::Bullet()
	: Object(EObjectType::eObjectType_PBullet)
	, SPD(DefaultSPD)
	, SPDY(1)
	, SPDX(1)
{
	width = 20;
	height = 20;
	r = width / 2;
	center.x = GetX() + r;
	center.y = GetY() + r;
}

Bullet::Bullet(int px, int py, int clickx, int clicky, EObjectType type, int spd)
	: Object(type)
	, SPD(spd)
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

void Bullet::Update(float Delta)
{
	SetX(GetX() + Delta * SPDX * SPD);
	SetY(GetY() + Delta * SPDY * SPD);
	center.x = GetX() + r;
	center.y = GetY() + r;
}

void Bullet::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, 40, 40);

	if (center.x < 0 ||
		center.x > WIDTH ||
		center.y < 0 ||
		center.y > HEIGHT)
	{
		return;
	}

	if (this->Objtype == eObjectType_PBullet)
	{
		if (isCritical)
		{
			P = new Gdiplus::SolidBrush(Gdiplus::Color(0, 10, 40));
		}
		else
		{
			P = new Gdiplus::SolidBrush(Gdiplus::Color(80, 200, 200));
		}
	}
	else if (this->Objtype == eObjectType_EBullet)
	{
		P = new Gdiplus::SolidBrush(Gdiplus::Color(255, 73, 73));
	}

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	MemG->FillEllipse(P, (int)(GetX()), (int)(GetY()), width, height);
}

void Bullet::SPDSet(int px, int py, int clickx, int clicky)
{
	float length = sqrtf(pow(abs(clickx - px), 2) + pow(abs(clicky - py), 2));
	if (length < DBL_EPSILON)
	{
		int a = 0;;
		++a;
	}
	SPDX = abs(clickx - px) / length;
	SPDY = abs(clicky - py) / length;

	if (clickx < px)
		SPDX = -SPDX;
	if (clicky < py)
		SPDY = -SPDY;
}

void Bullet::BulletInit(int px, int py, int clickx, int clicky, EObjectType type, int spd)
{
	Objtype = type;
	if (type == eObjectType_EBullet)
		SPD = spd;
	else
		SPD = GameData::GetInstance()->player->SSPD;
	SetX(px);
	SetY(py);
	SPDSet(px, py, clickx, clicky);
	center.x = GetX() + r;
	center.y = GetY() + r;
}

void Bullet::BulletReset()
{
	SetX(10);
	SetY(10);
	SPDX = 0;
	SPDY = 0;
	SPD = 0;
	isCritical = false;
}
