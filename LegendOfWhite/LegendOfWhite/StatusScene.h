#pragma once
#include "Scene.h"

class StatusScene : public Scene
{
public:
	StatusScene();

	void Init();
	void Control();
	void Update(float Delta);
	void Render(Gdiplus::Graphics G);
};
