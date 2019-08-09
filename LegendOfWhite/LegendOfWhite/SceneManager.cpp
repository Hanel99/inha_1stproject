#include "pch.h"
#include "SceneManager.h"
#include "GameData.h"

#define BOSS_STAGE 10

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	introScene = new IntroScene();

	
	sceneVec.emplace_back(introScene);


	curScene = sceneVec[0];	
}

Scene* SceneManager::GetCurScene()
{
	return curScene;
}

void SceneManager::SetCurScene(Scene* Scene)
{
}

void SceneManager::MoveNextScene()
{


	if (GameData::GetInstance()->GetStagenum == BOSS_STAGE)
	{
		GameData::GetInstance()->SetChapternum(GameData::GetInstance()->GetChapternum() + 1);
		GameData::GetInstance()->SetStagenum(1);
	}
	else {
		GameData::GetInstance()->SetStagenum(GameData::GetInstance()->GetStagenum() + 1);
	}
}

