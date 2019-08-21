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
		width = 60;
		height = 60;
		r = width/2;
		length = 35; //sqrt(powf(width / 2, 2) + powf(height / 2, 2))를 연산하니 42.42정도가 나왔슴. 너무 외적으로하면 벽에 닿지도 않았는데 총알터지는게 있어서 적당한사이즈로 줄임
		center.x = GetX() + r;
		center.y = GetY() + r;
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	CPoint center;
	int length;

	Gdiplus::Rect* rec;
	std::weak_ptr<Gdiplus::Image> wallimg;
};

