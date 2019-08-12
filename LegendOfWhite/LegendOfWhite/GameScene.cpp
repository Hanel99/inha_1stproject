#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
}

void GameScene::Init()
{
	player = new Player();
	enemy = new Enemy();

	objectVec.emplace_back(player);
	objectVec.emplace_back(enemy);
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
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));

	temp.DrawImage(bgImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);

	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}
}
