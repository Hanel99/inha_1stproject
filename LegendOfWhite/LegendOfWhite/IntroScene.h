#pragma once
#include "Scene.h"
#include "common.h"

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
	void SendRButtonDown(UINT nFlags, CPoint point);
	std::weak_ptr<Gdiplus::Image> introImg;
	std::weak_ptr<Gdiplus::Image> btnImg;
	Gdiplus::Rect* r;

	int eXMLBtnnum;
};

