#pragma once
#include "Scene.h"
#include "Object.h"

class GameScene : public Scene
{
public:
	GameScene();

	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

private:
	Object* player;
	std::vector<Object*> objectVec;
};
