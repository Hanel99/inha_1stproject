#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "StatusScene.h"
#include "ResultScene.h"

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
	void GotoResultScene();
	void GotoTitleScene();
	void SetGameClear(bool bol);
	bool IsGameClear();

private : 
	Scene* introScene;
	Scene* gameScene;
	Scene* statusScene;
	Scene* allClearScene;
	Scene* curScene;

	int scenenum;
	bool isgameclear;
	std::vector<Scene*> sceneVec;
};

SceneManager* SceneManager::instance = nullptr;