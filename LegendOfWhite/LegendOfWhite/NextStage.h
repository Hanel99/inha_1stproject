#pragma once
#include "Object.h"
#include "common.h"

class NextStage : Object
{
public:
	NextStage(int getx, int gety)
		: Object(EObjectType::eObjectType_NextStage)
	{
		SetX(getx);
		SetY(gety);
		width = 64;
		height = 64;
		r = 2;
		center.x = GetX() + 40;
		center.y = GetY() + 40;
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	CPoint center;

	std::weak_ptr<Gdiplus::Image> Img;
};

