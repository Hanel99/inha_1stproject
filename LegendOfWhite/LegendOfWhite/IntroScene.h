#pragma once
#include "Scene.h"

class IntroScene : public Scene
{
public:
	IntroScene();

	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	std::weak_ptr<Gdiplus::Image> introImg;
};

