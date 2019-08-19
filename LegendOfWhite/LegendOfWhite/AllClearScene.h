#pragma once
#include "Scene.h"
#include "common.h"

class AllClearScene : public Scene
{
public:
	AllClearScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SendLButtonDown(UINT nFlags, CPoint point);
	void SendRButtonDown(UINT nFlags, CPoint point);
	std::weak_ptr<Gdiplus::Image> allClearImg;
};

