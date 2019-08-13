#pragma once
#include "Scene.h"

class IntroScene : public Scene
{
public:
	IntroScene();

	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SendLButtonDown(UINT nFlags, CPoint point);
	std::weak_ptr<Gdiplus::Image> introImg;
};

