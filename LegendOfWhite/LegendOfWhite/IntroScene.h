#pragma once
#include "Scene.h"

class IntroScene : public Scene
{
	IntroScene();
	~IntroScene();

	void Init();
	void Control();
	void Update(float Delta);
	void Render(Gdiplus::Graphics G);
};

