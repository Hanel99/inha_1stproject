#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
}

#define GRID 80

void GameScene::Init()
{
	player = GameData::GetInstance()->player;
	SetStartPos(100, 100);

	enemy = new Enemy();
	isAllEnemyDead = false;

	for (int gridy = 0; gridy * GRID < HEIGHT; ++gridy)
	{
		for (int gridx = 0; gridx * GRID < WIDTH; ++gridx)
		{
			if (gridx == 0 || gridx == 15 || gridy == 0 || gridy == 8)
			{
				wallVec.emplace_back(new Wall(gridx * GRID, gridy * GRID));
			}
		}
	}
	wallVec.emplace_back(new Wall(5 * GRID, 2 * GRID));
	wallVec.emplace_back(new Wall(12 * GRID, 4 * GRID));
	wallVec.emplace_back(new Wall(10 * GRID, 5 * GRID));

	nextStageBoard = new NextStage(12 * GRID, 2 * GRID);

	enemyVec.emplace_back(enemy);
}

void GameScene::Update(float Delta)
{
	//스탯창으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
	player->Update(Delta);
	IsPlayerColl(player);

	if (enemyVec.empty())
	{
		isAllEnemyDead = true;
	}
	else
	{
		for (auto& it : enemyVec)
		{
			it->Update(Delta);
		}
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


	nextStageBoard->Render(MemG);
	for (auto& it : wallVec)
	{
		it->Render(MemG);
	}
	for (auto& it : bulletVec)
	{
		it->Render(MemG);
	}
	for (auto& it : enemyVec)
	{
		it->Render(MemG);
	}
	player->Render(MemG);
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
	for (auto& it : wallVec)
	{
		if (pow((it->center.x - b->center.x), 2) + pow((it->center.y - b->center.y), 2) <= pow((it->width / 5 + b->width / 3), 2))
		{
			//벽과 충돌
			AssetManager::GetInstance()->RetrunBullet(b);
			ReturnBulletFromGameScene(b);
		}
	}

	for (auto& it : enemyVec)
	{
		if (pow((it->center.x - b->center.x), 2) + pow((it->center.y - b->center.y), 2) <= pow((it->width / 5 + b->width / 3), 2))
		{
			//몬스터와 충돌
			AssetManager::GetInstance()->RetrunBullet(b);
			ReturnBulletFromGameScene(b);
			printf("%d에서 %d만큼 데미지를 받아", it->HP, player->ATK);
			it->HP = it->HP - player->ATK;
			printf(" %d의 hp가 남음\n",it->HP);
			if (it->HP <= 0)
			{
				std::vector<Enemy*>::iterator itr = std::find(enemyVec.begin(), enemyVec.end(), it);
				enemyVec.erase(itr);
			}
		}
	}
}

void GameScene::IsPlayerColl(Player* p)
{
	for (auto& it : wallVec)
	{
		if (pow((it->center.x - p->center.x), 2) + pow((it->center.y - p->center.y), 2) <= pow((it->r + p->r), 2))
		{
			switch (p->eplayerlook)
			{
			case ePlayerLook_Down:
				p->SetY(p->GetY() - 3);
				break;
			case ePlayerLook_Up:
				p->SetY(p->GetY() + 3);
				break;
			case ePlayerLook_Left:
				p->SetX(p->GetX() + 3);
				break;
			case ePlayerLook_Right:
				p->SetX(p->GetX() - 3);
				break;
			}
		}
	}
	if (pow((nextStageBoard->center.x - p->center.x), 2) + pow((nextStageBoard->center.y - p->center.y), 2) <= pow((nextStageBoard->r + p->r), 2) && isAllEnemyDead)
	{
		printf("다음씬!");
		SetStartPos(100, 100);
		SceneManager::GetInstance()->GotoAllClearScene();
	}
}