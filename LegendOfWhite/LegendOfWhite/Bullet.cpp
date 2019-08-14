#include "pch.h"
#include "Object.h"
#include "Bullet.h"

void Bullet::Update(float Delta)
{
	SetX(GetX() + Delta * SPDX * SPD);
	SetY(GetY() + Delta * SPDY * SPD);
}

void Bullet::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	bulletimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bullet.png"));

	temp.DrawImage(bulletimg.lock().get(),
		rect, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 20, 20);

	MemG->DrawImage(&bm, screenPosRect);
}

void Bullet::SPDSet(int px, int py, int clickx, int clicky)
{
	float length = sqrtf(pow(abs(clickx - px), 2) + pow(abs(clicky - py), 2));
	SPDX = abs(clickx - px) / length;
	SPDY = abs(clicky - py) / length;

	if (clickx < px)
		SPDX = -SPDX;
	if (clicky < py)
		SPDY = -SPDY;
	
}

void Bullet::BulletInit(int px, int py, int clickx, int clicky)
{
	damage = GameData::GetInstance()->player->ATK;
	SetX(px);
	SetY(py);
	SPDSet(px, py, clickx, clicky);	
}

void Bullet::BulletReset()
{
	damage = 1;
	SetX(1);
	SetY(1);
	SPDX = 1;
	SPDY = 1;
}


