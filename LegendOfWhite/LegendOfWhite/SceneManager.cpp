#include "pch.h"
#include "SceneManager.h"
#include "GameData.h"

#define BOSS_STAGE 10

SceneManager::SceneManager()
{
	Init();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	introScene = new IntroScene();
	//게임씬을 양산해서 사용할것. 여기선 임시로 하나만
	gameScene = new GameScene();
	statusScene = new StatusScene();
	allClearScene = new ResultScene();
	
	sceneVec.emplace_back(introScene);
	sceneVec.emplace_back(statusScene);
	sceneVec.emplace_back(gameScene);
	sceneVec.emplace_back(allClearScene);

	scenenum = 0;
	curScene = introScene;	
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
		//새로시작의 경우 2로, 저장되있는 경우 저장한 수의 씬으로 이동
		curScene = sceneVec[2];
		scenenum = 2;
	}
	else if (scenenum > 2)
	{
		//스테이지 클리어 후 다음 스테이지로 이동
		if (GameData::GetInstance()->GetStagenum() == BOSS_STAGE)
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

void SceneManager::GotoResultScene()
{
	scenenum = 3;
	curScene = sceneVec[scenenum];
}


void SceneManager::GotoTitleScene()
{
	scenenum = 0;
	curScene = sceneVec[scenenum];
}

void SceneManager::SetGameClear(bool bol)
{
	isgameclear = bol;
}

bool SceneManager::IsGameClear()
{	
	return isgameclear;
}
