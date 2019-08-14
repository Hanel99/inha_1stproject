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
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	std::weak_ptr<Gdiplus::Image> wallimg;
};

