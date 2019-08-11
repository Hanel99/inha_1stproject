#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();

	void Init();
	void Control();
	void Update(float Delta);
	void Render(Gdiplus::Graphics G);
};
