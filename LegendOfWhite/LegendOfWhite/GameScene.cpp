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
	//temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//Gdiplus::Image tempImg(TEXT("bgaimage.png"));

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 100, 100, 100));
	MemG->FillRectangle(&WhiteBrush, rect);
	
	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);
	

	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}
}
