#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	Init();
}


void GameScene::Init()
{
	player = GameData::GetInstance()->player;
	enemy = new Enemy();
	bul = new Bullet();

	objectVec.emplace_back(player);
	objectVec.emplace_back(enemy);
	objectVec.emplace_back(bul);
	SetStartPos(300, 300);
}

void GameScene::ProcessInput()
{
	//스탯창으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}

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

void GameScene::SetStartPos(int x, int y)
{ 
	player->SetX(x);
	player->SetY(y);
}

void GameScene::SetStartPos(CPoint cp)
{
	player->SetXY(cp.x, cp.y);
}

