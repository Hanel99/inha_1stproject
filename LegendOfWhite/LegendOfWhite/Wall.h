#pragma once
#include "Object.h"
#include "common.h"

class Wall : public Object
{
public:
	Wall(int getx, int gety);
	~Wall();

	void Init(int getx, int gety);
	void Release();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	CPoint center;
	int length;

	Gdiplus::Rect* rec;
	std::weak_ptr<Gdiplus::Image> wallimg;
};

