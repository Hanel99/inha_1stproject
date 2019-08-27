#pragma once
#include "Scene.h"
#include "common.h"

#define BTN_WIDTH 270
#define BTN_HEIGHT 88

class IntroScene : public Scene
{
public:
	IntroScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void SendLButtonDown(UINT nFlags, CPoint point);
	virtual void SendRButtonDown(UINT nFlags, CPoint point);
	std::weak_ptr<Gdiplus::Image> introImg;
	std::weak_ptr<Gdiplus::Image> btnImg;
	Gdiplus::Rect* r;

	void SetStartPos(float x, float y);
	int eXMLBtnnum;
};

