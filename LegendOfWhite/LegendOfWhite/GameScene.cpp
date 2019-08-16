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

	for (int gridy = 0; gridy * 80 < HEIGHT; ++gridy)
	{
		for (int gridx = 0; gridx * 80 < WIDTH; ++gridx)
		{
			if (gridx == 0 || gridx == 15 || gridy == 0 || gridy == 8)
			{
				wallVec.emplace_back(new Wall(gridx * 80, gridy * 80));
			}

			if (gridx == 5 && gridy == 2)
				wallVec.emplace_back(new Wall(gridx * 80, gridy * 80));
			else if (gridx == 12 && gridy == 4)
				wallVec.emplace_back(new Wall(gridx * 80, gridy * 80));
			else if (gridx == 10 && gridy == 5)
				wallVec.emplace_back(new Wall(gridx * 80, gridy * 80));
		}
	}

	objectVec.emplace_back(player);
	objectVec.emplace_back(enemy);
}

void GameScene::Update(float Delta)
{
	//스탯창으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
	for (auto& it : objectVec)
	{
		it->Update(Delta);
	}
	for (auto& it : bulletVec)
	{
		if (it == nullptr) break;
		it->Update(Delta);
		BulletCollCheck(it);
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));

	temp.DrawImage(bgImg.lock().get(), rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);

	for (auto& it : wallVec)
	{
		it->Render(MemG);
	}
	for (auto& it : bulletVec)
	{
		it->Render(MemG);
	}
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
	Bullet* b = AssetManager::GetInstance()->CreateBullet();
	if (b != nullptr)
	{
		b->BulletInit(player->GetX() + (player->width / 2), player->GetY() + (player->height / 2), point.x, point.y);
		bulletVec.emplace_back(b);
	}
}

void GameScene::SendRButtonDown(UINT nFlags, CPoint point)
{
	for (int i = 0; i < 20; ++i)
	{
		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(player->GetX() + (player->width / 2), player->GetY() + (player->height / 2), point.x + i * 40, point.y + i * 40);
			bulletVec.emplace_back(b);
		}
	}
}

void GameScene::ReturnBulletFromGameScene(Bullet* b)
{
	std::vector<Bullet*>::iterator it = std::find(bulletVec.begin(), bulletVec.end(), b);
	if (it < bulletVec.end())
		bulletVec.erase(it);
}

void GameScene::BulletCollCheck(Bullet* b)
{
	if (b->GetX() > WIDTH || b->GetX() < 0 || b->GetY() > HEIGHT || b->GetY() < 0)
	{
		AssetManager::GetInstance()->RetrunBullet(b);
		ReturnBulletFromGameScene(b);
	}
	else
	{
		for (auto& it : wallVec)
		{
			if (pow((it->center.x - b->center.x), 2) + pow((it->center.y - b->center.y), 2) <= pow((it->width / 3 + b->width / 3), 2))
			{
				//벽과 충돌
				AssetManager::GetInstance()->RetrunBullet(b);
				ReturnBulletFromGameScene(b);
			}
		}
	}
}
//
//void GameScene::IsPlayerColl(Player* p)
//{
//	p->canmove = true;
//	for (auto& it : wallVec)
//	{
//		if (pow((it->center.x - p->center.x), 2) + pow((it->center.y - p->center.y), 2) <= pow((it->width/3 + p->width/3), 2))
//		{
//			printf("충돌!");
//			p->canmove = false;
//			break;
//		}
//	}
//}