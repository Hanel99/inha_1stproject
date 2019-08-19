#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "StatusScene.h"
#include "AllClearScene.h"

#include <vector>

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	Scene* GetCurScene();
	void SetCurScene(Scene* scene);
	void SetCurScene(Scene* scene, int chapternum, int stagenum);

	void MoveNextScene();
	void SwapStatusScene();
	void GotoAllClearScene();
	void GotoTitleScene();

private : 
	Scene* introScene;
	Scene* gameScene;
	Scene* statusScene;
	Scene* allClearScene;
	Scene* curScene;

	int scenenum;

	std::vector<Scene*> sceneVec;
};

SceneManager* SceneManager::instance = nullptr;