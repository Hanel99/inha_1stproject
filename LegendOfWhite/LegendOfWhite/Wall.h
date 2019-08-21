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
		length = 35; //sqrt(powf(width / 2, 2) + powf(height / 2, 2))�� �����ϴ� 42.42������ ���Խ�. �ʹ� ���������ϸ� ���� ������ �ʾҴµ� �Ѿ������°� �־ �����ѻ������ ����
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

