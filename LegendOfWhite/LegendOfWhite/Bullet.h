#pragma once
#include "Object.h"
#include "GameData.h"

#define DefaultSPD 500

class Bullet : public Object
{
public:
	Bullet();
	Bullet(int px, int py, int clickx, int clicky, EObjectType type, int spd);

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	void SPDSet(int px, int py, int clickx, int clicky);
	void BulletInit(int px, int py, int clickx, int clicky, EObjectType type, int spd);
	void BulletReset();
	CPoint center;

	Gdiplus::Rect* rec;
	Gdiplus::SolidBrush* P;
	int SPD;
	float SPDX;
	float SPDY;
	bool isCritical = false;
};