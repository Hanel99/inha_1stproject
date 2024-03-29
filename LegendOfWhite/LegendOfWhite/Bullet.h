#pragma once
#include "Object.h"
#include "GameData.h"

#define DefaultSPD 500

class Bullet : public Object
{
public:
	Bullet();
	~Bullet();

	void Init();
	void Release();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	void SPDSet(int px, int py, int clickx, int clicky);
	void BulletInit(int px, int py, int clickx, int clicky, EObjectType type, int spd);
	void BulletReset();
	CPoint center;

	Gdiplus::Rect* rec;
	Gdiplus::SolidBrush* brush;

	Gdiplus::SolidBrush* criB;
	Gdiplus::SolidBrush* pbulletB;
	Gdiplus::SolidBrush* ebulletB;

	int SPD;
	float SPDX;
	float SPDY;
	bool isCritical = false;
};