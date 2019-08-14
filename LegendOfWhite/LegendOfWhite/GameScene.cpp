#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	Init();
}


void GameScene::Init()
{
	player = GameData::GetInstance()->player;
	SetStartPos(100, 100);

	enemy = new Enemy();

	for (int yy = 0; yy < HEIGHT; yy += 80)
	{
		wallVec.emplace_back(new Wall(0, yy));
		wallVec.emplace_back(new Wall(WIDTH-80, yy));
	}
	for (int xx = 0; xx < WIDTH; xx += 80)
	{
		wallVec.emplace_back(new Wall(xx, 0));
		wallVec.emplace_back(new Wall(xx, HEIGHT-80));
	}
	


	for (auto& it : wallVec)
	{
		objectVec.emplace_back(it);
	}

	objectVec.emplace_back(player);
	objectVec.emplace_back(enemy);
	
}

void GameScene::Update(float Delta)
{
	//����â����
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
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

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);

	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}
}

void GameScene::SetStartPos(float x, float y)
{ 
	player->SetX(x);
	player->SetY(y);
}

void GameScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	Bullet * b = new Bullet(player->GetX() + player->width/2, player->GetY() + player->height/2, point.x, point.y);
	objectVec.emplace_back(b);
}

