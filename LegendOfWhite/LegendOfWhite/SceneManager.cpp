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
	gameScene = new GameScene();
	statusScene = new StatusScene();
	
	sceneVec.emplace_back(introScene);
	sceneVec.emplace_back(gameScene);
	sceneVec.emplace_back(statusScene);

	scenenum = 0;
	curScene = sceneVec[scenenum];	
}

Scene* SceneManager::GetCurScene()
{
	return curScene;
}

void SceneManager::SetCurScene(Scene* scene)
{
	curScene = scene;
}

//나중에 게임씬 양산하고 넣어줄때는 이렇게 넣을 것
void SceneManager::SetCurScene(Scene* scene, int chapternum, int stagenum)
{
	curScene = scene;
}

void SceneManager::MoveNextScene()
{
	if (scenenum == 0)
	{
		//인트로 -> 게임
		curScene = sceneVec[++scenenum];
	}
	else if (scenenum == 1)
	{
		//스테이지 클리어 후 다음 스테이지로 이동
		if (GameData::GetInstance()->GetStagenum == BOSS_STAGE)
		{
			GameData::GetInstance()->SetChapternum(GameData::GetInstance()->GetChapternum() + 1);
			GameData::GetInstance()->SetStagenum(1);
		}
		else {
			GameData::GetInstance()->SetStagenum(GameData::GetInstance()->GetStagenum() + 1);
		}
	}
}

void SceneManager::SwapStatusScene()
{
	if (scenenum == 1)
	{
		//게임 -> 스테이터스 창
		curScene = sceneVec[++scenenum];
	}
	else if (scenenum == 2)
	{
		//스테이터스 창 -> 게임
		curScene = sceneVec[--scenenum];
	}
}

