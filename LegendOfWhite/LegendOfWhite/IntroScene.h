#pragma once
#include "Scene.h"
#include "common.h"

#define BTN_WIDTH 270
#define BTN_HEIGHT 88

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	virtual void Init()override;
	virtual void Update(float Delta)override;
	virtual void Release()override;
	virtual void Render(Gdiplus::Graphics* MemG)override;
	virtual void SendLButtonDown(UINT nFlags, CPoint point)override;
	virtual void SendRButtonDown(UINT nFlags, CPoint point)override;
	std::weak_ptr<Gdiplus::Image> introImg;
	std::weak_ptr<Gdiplus::Image> btnImg;
	Gdiplus::Rect* r;

	int eXMLBtnnum;
};

