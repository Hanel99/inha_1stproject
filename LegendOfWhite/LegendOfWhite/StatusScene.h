#pragma once
#include "Scene.h"

class StatusScene : public Scene
{
public:
	StatusScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SendLButtonDown(UINT nFlags, CPoint point);

public:
	std::weak_ptr<Gdiplus::Image> statImg;

};
