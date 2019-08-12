#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::Init()
{
}

void GameScene::ProcessInput()
{
	for (auto& it : objectVec)
	{
		it->ProcessInput();
	}
}

void GameScene::Update(float Delta)
{
	for (auto& it : objectVec)
	{
		it->Update(Delta);
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}
}
