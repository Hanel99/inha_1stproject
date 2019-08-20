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
	//���Ӿ��� ����ؼ� ����Ұ�. ���⼱ �ӽ÷� �ϳ���
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

//���߿� ���Ӿ� ����ϰ� �־��ٶ��� �̷��� ���� ��
void SceneManager::SetCurScene(Scene* scene, int chapternum, int stagenum)
{
	curScene = scene;
}

void SceneManager::MoveNextScene()
{
	if (scenenum == 0)
	{
		//��Ʈ�� -> ����
		//���ν����� ��� 2��, ������ִ� ��� ������ ���� ������ �̵�
		curScene = sceneVec[2];
		scenenum = 2;
	}
	else if (scenenum > 2)
	{
		//�������� Ŭ���� �� ���� ���������� �̵�
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
		//���� -> �������ͽ� â
		curScene = sceneVec[++scenenum];
	}
	else if (scenenum == 2)
	{
		//�������ͽ� â -> ����
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
