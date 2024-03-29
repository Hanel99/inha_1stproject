#pragma once
#include "Object.h"
#include "common.h"

class NextStage : public Object
{
public:
	NextStage(int getx, int gety);
	~NextStage();

	void Init(int getx, int gety);
	void Release();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	CPoint center;

	std::weak_ptr<Gdiplus::Image> Img;
};

