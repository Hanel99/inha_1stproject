#pragma once
#include "pch.h"

class Scene
{
public:
	Scene();

	virtual void Init() = 0;
	virtual void Update(float Delta) = 0;
	virtual void Render(Gdiplus::Graphics* MemG) = 0;
	virtual void SendLButtonDown(UINT nFlags, CPoint point) = 0;
};