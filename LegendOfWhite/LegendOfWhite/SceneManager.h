#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "IntroScene.h"

#include <vector>

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	Scene* GetCurScene();
	void SetCurScene(Scene* Scene);

	void MoveNextScene();
	
	
private : 
	Scene* introScene;
	std::vector<Scene*> gameScenes;
	Scene* curScene;

	std::vector<Scene*> sceneVec;
};

SceneManager* SceneManager::instance = nullptr;