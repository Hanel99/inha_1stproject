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
	Release();
}

void SceneManager::Init()
{
	introScene = new IntroScene();
	gameScene = new GameScene();
	statusScene = new StatusScene();
	resultScene = new ResultScene();
	
	sceneVec.emplace_back(introScene);
	sceneVec.emplace_back(gameScene);
	sceneVec.emplace_back(statusScene);	
	sceneVec.emplace_back(resultScene);

	scenenum = eScene_Intro;
	curScene = sceneVec[eScene_Intro];	
}

void SceneManager::Release()
{
	for (auto& it : sceneVec)
	{
		delete it;
	}
}

Scene* SceneManager::GetCurScene()
{
	return curScene;
}
void SceneManager::SetCurScene(Scene* scene)
{
	curScene = scene;
}

void SceneManager::MoveNextScene()
{
	if (scenenum == eScene_Intro)
	{
		//��Ʈ�� -> ����
		scenenum = eScene_Game;
		curScene = sceneVec[scenenum];		
	}
	else if (scenenum == eScene_Game)
	{
		//�������� Ŭ���� �� ���� ���������� �̵�
		if (GameData::GetInstance()->stagenum == BOSS_STAGE)
		{
			GameData::GetInstance()->chapternum++;
			GameData::GetInstance()->stagenum = 1;
		}
		else {
			GameData::GetInstance()->stagenum++;
		}
	}
}

void SceneManager::SwapStatusScene()
{
	if (scenenum == eScene_Game)
	{
		//���� -> �������ͽ� â
		scenenum = eScene_Status;
		curScene = sceneVec[scenenum];
	}
	else if (scenenum == eScene_Status)
	{
		//�������ͽ� â -> ����
		scenenum = eScene_Game;
		curScene = sceneVec[scenenum];
	}
}

void SceneManager::GotoResultScene()
{
	scenenum = eScene_Result;
	curScene = sceneVec[scenenum];
}
void SceneManager::GotoTitleScene()
{
	scenenum = eScene_Intro;
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
