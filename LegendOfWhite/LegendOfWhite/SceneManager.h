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

	Scene* GetCurScene();
	void SetCurScene(Scene*);
	void SetStagenum(int stagenum);
	void SetChapternum(int chapnum);
	void Init();

	void AddScene(Scene* Scene);
	
private : 
	int chapternum;
	int stagenum;
	Scene* IntroScene;
	Scene* CurScene;

	std::vector<Scene*> SceneVec;

};

SceneManager* SceneManager::instance = nullptr;