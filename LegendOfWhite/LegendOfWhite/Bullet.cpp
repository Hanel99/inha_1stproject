#include "pch.h"
#include "Object.h"
#include "Bullet.h"

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

	Gdiplus::Bitmap bm(40, 40, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	
	bulletimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));
	if (this->Objtype == eObjectType_PBullet)
	{
		rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_PBullet);		
	}
	else if (this->Objtype == eObjectType_EBullet)
	{
		rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_EBullet);
	}
	temp.DrawImage(bulletimg.lock().get(), rect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);


	Gdiplus::Pen P(Gdiplus::Color(255, 0, 0), 1);
	MemG->DrawEllipse(&P, (int)(GetX()), (int)(GetY()), width, height);

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

void Bullet::BulletInit(int px, int py, int clickx, int clicky, EObjectType type)
{
	Objtype = type;
	damage = GameData::GetInstance()->player->ATK;
	SPD = DefaultSPD;
	SetX(px);
	SetY(py);
	SPDSet(px, py, clickx, clicky);	
	center.x = GetX() + r;
	center.y = GetY() + r;
}

void Bullet::BulletReset()
{
	damage = 1;
	SetX(10);
	SetY(10);
	SPDX = 0;
	SPDY = 0;
	SPD = 0;
}


