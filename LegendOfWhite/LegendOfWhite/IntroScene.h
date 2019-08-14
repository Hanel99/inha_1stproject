#pragma once
#include "Scene.h"

#define BTN_WIDTH 270
#define BTN_HEIGHT 88

class IntroScene : public Scene
{
public:
	IntroScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SendLButtonDown(UINT nFlags, CPoint point);
	std::weak_ptr<Gdiplus::Image> introImg;
	std::weak_ptr<Gdiplus::Image> newplayImg;
	std::weak_ptr<Gdiplus::Image> loadplayImg;
	std::weak_ptr<Gdiplus::Image> gameendImg;
};

