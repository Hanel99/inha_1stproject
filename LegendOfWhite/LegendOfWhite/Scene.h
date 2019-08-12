#pragma once
#include "pch.h"

class Scene
{
public:
	Scene();

	virtual void Init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(float Delta) = 0;
	virtual void Render(Gdiplus::Graphics* MemG) = 0;
};