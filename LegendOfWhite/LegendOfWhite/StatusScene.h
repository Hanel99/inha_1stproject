#pragma once
#include "Scene.h"

class StatusScene : public Scene
{
public:
	StatusScene();

	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
};
