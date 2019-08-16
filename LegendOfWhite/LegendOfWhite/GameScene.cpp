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
		}
	}
	wallVec.emplace_back(new Wall(5 * 80, 2 * 80));
	wallVec.emplace_back(new Wall(12 * 80, 4 * 80));
	wallVec.emplace_back(new Wall(10 * 80, 5 * 80));

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
		IsPlayerColl(player);
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
		b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x, point.y);
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
			b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x + i * 100, point.y + i * 100);
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
			if (pow((it->center.x - b->center.x), 2) + pow((it->center.y - b->center.y), 2) <= pow((it->width/5 + b->width/3), 2))
			{
				//벽과 충돌
				AssetManager::GetInstance()->RetrunBullet(b);
				ReturnBulletFromGameScene(b);
			}
		}
	}
}

void GameScene::IsPlayerColl(Player* p)
{
	for (auto& it : wallVec)
	{
		//if (p->GetX() + p->width > it->GetX()) //플레이어가 오른쪽으로 이동해 벽과 충돌
		//	p->SetX(p->GetX() - 100);
		//else if (p->GetX() < it->GetX() + it->width) //플레이어가 왼쪽으로 이동해 벽과 충돌
		//	p->SetX(p->GetX() + 100);
		//else if (p->GetY() + p->height > it->GetY()) //플레이어가 아래로 이동해 벽과 충돌
		//	p->SetY(p->GetY() + 100);
		//else if (p->GetY() + p->height > it->GetY()) //플레이어가 위로 이동해 벽과 충돌
		//	p->SetY(p->GetY() - 100);

		if (pow((it->center.x - p->center.x), 2) + pow((it->center.y - p->center.y), 2) <= pow((it->r + p->r), 2))
		{
			switch (p->eplayerlook)
			{
			case ePlayerLook_Down:
				p->SetY(p->GetY() - 10);
				break;
			case ePlayerLook_Up:
				p->SetY(p->GetY() + 10);
				break;
			case ePlayerLook_Left:
				p->SetX(p->GetX() + 10);
				break;
			case ePlayerLook_Right:
				p->SetX(p->GetX() - 10);
				break;
			}
			printf("충돌!\n");
		}
	}
}