#pragma once
#include "Scene.h"
#include "common.h"

class ResultScene : public Scene
{
public:
	ResultScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void SendLButtonDown(UINT nFlags, CPoint point);
	virtual void SendRButtonDown(UINT nFlags, CPoint point);
	std::weak_ptr<Gdiplus::Image> Img;
};

