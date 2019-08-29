#pragma once
#include "Scene.h"
#include "common.h"

class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	virtual void Init()override;
	virtual void Update(float Delta)override;
	virtual void Release()override;
	virtual void Render(Gdiplus::Graphics* MemG)override;
	virtual void SendLButtonDown(UINT nFlags, CPoint point)override;
	virtual void SendRButtonDown(UINT nFlags, CPoint point)override;
	std::weak_ptr<Gdiplus::Image> Img;
};

