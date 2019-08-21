#include "pch.h"
#include "Object.h"
#include "Bullet.h"

void Bullet::Update(float Delta)
{
	if (this->Objtype == eObjectType_EBullet)
	{
		if (updown)
		{
			SPD -= 10;
			if (SPD <= 0)
				updown = !updown;
		}
		else
		{
			SPD += 20;
			if (SPD >= 400)
				updown = !updown;
		}
	}
	SetX(GetX() + Delta * SPDX * SPD);
	SetY(GetY() + Delta * SPDY * SPD);
	center.x = GetX() + r;
	center.y = GetY() + r;
}

void Bullet::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, 40, 40);

	//Gdiplus::Bitmap bm(40, 40, PixelFormat32bppARGB);
	//Gdiplus::Graphics temp(&bm);
	if (center.x < 0 ||
		center.x > WIDTH ||
		center.y < 0 ||
		center.y > HEIGHT)
	{
		return;
	}
	if (bulletimg.expired())
	{
		bulletimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));
	}

	
	
	if (this->Objtype == eObjectType_PBullet)
	{
		//rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_PBullet);
		P = new Gdiplus::SolidBrush(Gdiplus::Color(88, 200, 200));
	}		
	else if (this->Objtype == eObjectType_EBullet)
	{
		//rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_EBullet);
		P = new Gdiplus::SolidBrush(Gdiplus::Color(255, 73, 73));
	}

	//temp.DrawImage(bulletimg.lock().get(), rect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);
	
	MemG->FillEllipse(P, (int)(GetX()), (int)(GetY()), width, height);

	//MemG->DrawImage(bulletimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
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

void Bullet::BulletInit(int px, int py, int clickx, int clicky, EObjectType type)
{
	Objtype = type;
	damage = GameData::GetInstance()->player->ATK;
	if (type == eObjectType_EBullet)
		SPD = DefaultSPD;
		//SPD = 200;
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
	damage = 1;
	SetX(10);
	SetY(10);
	SPDX = 0;
	SPDY = 0;
	SPD = 0;
}


