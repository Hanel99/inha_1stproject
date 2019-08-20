#pragma once
#include "Object.h"
#include "common.h"

class Wall : public Object
{
public:
	Wall(int getx, int gety)
		: Object(EObjectType::eObjectType_Wall)
	{
		SetX(getx);
		SetY(gety);
		width = 128;
		height = 128;
		r = 30;
		center.x = GetX() + 20;
		center.y = GetY() + 20;
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	CPoint center;

	std::weak_ptr<Gdiplus::Image> wallimg;
};

