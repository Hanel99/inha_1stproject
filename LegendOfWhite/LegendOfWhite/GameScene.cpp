#include "pch.h"
#include "GameScene.h"
#include "LegendOfWhite.h"

GameScene::GameScene()
{
	Init();
}

#define GRID 60

void GameScene::Init()
{
	player = GameData::GetInstance()->player;

	player->ATK = (player->LV + GameData::GetInstance()->ATKP) * (1 + GameData::GetInstance()->ATKM);
	player->SPD = 500 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM) * 1.5f);
	player->SSPD = 800 + (GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM) * 3.0f);
	player->HP = GameData::GetInstance()->MAXHP;
	player->CRI = GameData::GetInstance()->CRI;

	SetStartPos(100, 100);
	isAllEnemyDead = false;

	for (int gridy = 0; gridy * GRID < HEIGHT; ++gridy)
	{
		for (int gridx = 0; gridx * GRID < WIDTH; ++gridx)
		{
			if (gridx == 0 || gridx == 20 || gridy == 0 || gridy == 11)
			{
				wallVec.emplace_back(new Wall(gridx * GRID, gridy * GRID - 20));
			}
		}
	}
	nextStageBoard = new NextStage(13 * GRID, 4 * GRID);

	enemy = new Enemy(EEnemyType::eEnemyType_Bird, 1, 30, 600, 300);
	enemyVec.emplace_back(enemy);
	enemy = new Enemy(EEnemyType::eEnemyType_Bird, 1, 30, 900, 400);
	enemyVec.emplace_back(enemy);
	bulletVec.reserve(1000);
}

bool xup = false;
bool yup = true;
int x = 2;
int y = 1;
int i = 0;

void GameScene::Update(float Delta)
{
	//스탯창으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
	player->Update(Delta);
	IsPlayerColl(player, Delta);

	if (GetAsyncKeyState(VK_SPACE) & 0x1001)
	{
		if (enemyVec.empty())
		{
			enemy = new Enemy(EEnemyType::eEnemyType_Bird, 1, 30, 600, 300);
			enemyVec.emplace_back(enemy);
		}
	}

	if (enemyVec.empty())
	{
		isAllEnemyDead = true;
	}
	else
	{
		for (auto& it : enemyVec)
		{
			it->Update(Delta);

			if (it->addDelta > 2.0f)
			{
				it->addDelta = 0.0f;
				i++;
				if (i >= 3) i = 0;
			}

			switch (i)
			{
			case 0:
				EnemyPattern1(it);
				break;
			case 1:
				EnemyPattern2(it);
				break;
			case 2:
				EnemyPattern3(it);
				break;
			default:
				break;
			}

			if (it->EnemyType == eEnemyType_Bird)
			{
				EnemyPattern1(it);
			}
			else if (it->EnemyType == eEnemyType_Devil)
			{
				EnemyPattern2(it);
			}

		}
		isAllEnemyDead = false;
	}

	for (auto& it : bulletVec)
	{
		//if (it == nullptr)	break;
		it->Update(Delta);
		BulletCollCheck(it);
	}
}


void GameScene::Render(Gdiplus::Graphics* MemG)
{
	++CLegendOfWhiteApp::CallCount;
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);




	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));
	//uibgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\uibgImg.png")); // ui 배경
	//temp.DrawImage(bgImg.lock().get(), rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 180, 180, 180));
	//MemG->FillRectangle(&WhiteBrush, rect);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);	
	MemG->DrawImage(bgImg.lock().get(), screenPosRect);

	//Gdiplus::Rect screenPosRect2(0, 0, 350, 114); // ui배경
	//MemG->DrawImage(uibgImg.lock().get(), screenPosRect2);

	if (isAllEnemyDead)
		nextStageBoard->Render(MemG);
	static bool bInit = false;
	if (!bInit)
	{
		bInit = true;
		bm = new Gdiplus::Bitmap(WIDTH, HEIGHT, PixelFormat32bppARGB);
		Gdiplus::Graphics temp(bm);
		for (auto& it : wallVec)
		{
			it->Render(&temp);
		}
	}
	else
	{
		MemG->DrawImage(bm, screenPosRect);
	}
	static bool bInit2 = false;
	if (!bInit2)
	{
		bInit2 = true;
		bm2 = new Gdiplus::Bitmap(WIDTH, HEIGHT, PixelFormat32bppARGB);
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


	uibgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\uibgImg.png")); // ui 배경
	Gdiplus::Rect screenPosRect2(0, 0, 340, 90); // ui배경
	MemG->DrawImage(uibgImg.lock().get(), screenPosRect2);

	stagebgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\stagebgImg.png")); // ui 배경
	Gdiplus::Rect screenPosRect3(1085, 0, 234, 68); // ui배경
	MemG->DrawImage(stagebgImg.lock().get(), screenPosRect3);

	UIRender(MemG);
}

void GameScene::UIRender(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(1210, 120, 50, 450);
	tabImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\tab.png"));

	Gdiplus::PointF P;
	std::wstring tempStr;
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));
	Gdiplus::SolidBrush B4(Gdiplus::Color(255, 236, 79)); // EXP 색
	Gdiplus::SolidBrush B5(Gdiplus::Color(76, 101, 228)); // chapter 색
	Gdiplus::SolidBrush B6(Gdiplus::Color(133, 51, 255)); // stage 색
	Gdiplus::Font F3(L"Berlin Sans FB", 28, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::Font F4(L"Berlin Sans FB", 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	P.X = 12;
	P.Y = 8;
	tempStr = L"Lv. " + std::to_wstring(player->LV);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 150;
	P.Y = 8;
	tempStr = L"HP : " + std::to_wstring(player->HP);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 12;
	P.Y = 42;
	tempStr = L"EXP : " + std::to_wstring(player->EXP);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B4);

	P.X = 1100;
	P.Y = 8;
	tempStr = L"CHAPTER : " + std::to_wstring(GameData::GetInstance()->chapternum); // chapter값 받아야됨
	MemG->DrawString(tempStr.c_str(), -1, &F4, P, &B5);

	P.X = 1128;
	P.Y = 33;
	tempStr = L"STAGE : " + std::to_wstring(GameData::GetInstance()->stagenum); // stage값 받아야됨
	MemG->DrawString(tempStr.c_str(), -1, &F4, P, &B6);

	//P.X = 200;
	//P.Y = 56;
	//tempStr = L"X : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().x);
	//tempStr.append(L" / Y : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().y));
	//MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	//Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	//MemG->DrawImage(tabImg.lock().get(), rect, 0, 0, 32, 512, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
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
		b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x, point.y, eObjectType_PBullet);
		bulletVec.emplace_back(b);
	}
}

void GameScene::SendRButtonDown(UINT nFlags, CPoint point)
{
	for (int i = -10; i < 10; ++i)
	{
		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x + i * 10, point.y + i * 10, eObjectType_PBullet);
			bulletVec.emplace_back(b);
		}
	}
}

void GameScene::ReturnBulletFromGameScene(Bullet* b)
{
	CCriticalSection cs;
	cs.Lock();
	std::vector<Bullet*>::iterator it = std::find(bulletVec.begin(), bulletVec.end(), b);
	if (it < bulletVec.end())
		bulletVec.erase(it);
	cs.Unlock();
}

void GameScene::BulletCollCheck(Bullet* b)
{
	for (auto& it : wallVec)
	{
		if (pow((it->center.x - b->center.x), 2) + pow((it->center.y - b->center.y), 2) <= pow((it->length + b->r), 2))
		{
			//벽과 충돌
			AssetManager::GetInstance()->RetrunBullet(b);
			ReturnBulletFromGameScene(b);
		}
	}

	for (auto& it : enemyVec)
	{
		if (pow((it->center.x - b->center.x), 2) + pow((it->center.y - b->center.y), 2) <= pow((it->r + b->r), 2))
		{
			if (b->Objtype == eObjectType_PBullet)
			{
				//플레이어의 총알과 몬스터가 충돌
				AssetManager::GetInstance()->RetrunBullet(b);
				ReturnBulletFromGameScene(b);
				it->HP -= player->ATK;
				if (it->HP <= 0)
				{
					std::vector<Enemy*>::iterator itr = std::find(enemyVec.begin(), enemyVec.end(), it);
					enemyVec.erase(itr);
					player->EXP += it->EXP;
				}
			}
		}
	}
	if (pow((player->center.x - b->center.x), 2) + pow((player->center.y - b->center.y), 2) <= pow((player->r + b->r), 2))
	{
		if (b->Objtype == eObjectType_EBullet)
		{
			//몬스터의 총알과 플레이어가 충돌
			AssetManager::GetInstance()->RetrunBullet(b);
			ReturnBulletFromGameScene(b);
			player->HP -= enemy->ATK;
			if (player->HP <= 0)
			{
				//플레이어 사망
				SceneManager::GetInstance()->SetGameClear(false);
				SceneManager::GetInstance()->GotoResultScene();
			}
		}
	}
}

void GameScene::IsPlayerColl(Player* p, float Delta)
{
	for (auto& it : wallVec)
	{
		if (pow((it->center.x - p->center.x), 2) + pow((it->center.y - p->center.y), 2) <= pow((it->r + p->r), 2))
		{
			switch (p->eplayerlook)
			{
			case ePlayerLook_Down:
				p->SetY(p->GetY() - (Delta * p->SPD));
				break;
			case ePlayerLook_Up:
				p->SetY(p->GetY() + (Delta * p->SPD));
				break;
			case ePlayerLook_Left:
				p->SetX(p->GetX() + (Delta * p->SPD));
				break;
			case ePlayerLook_Right:
				p->SetX(p->GetX() - (Delta * p->SPD));
				break;
			}
		}
	}
	if (pow((nextStageBoard->center.x - p->center.x), 2) + pow((nextStageBoard->center.y - p->center.y), 2) <= pow((nextStageBoard->r + p->r), 2) && isAllEnemyDead)
	{
		SceneManager::GetInstance()->SetGameClear(true);
		GameData::GetInstance()->SavePlayerData();
		SceneManager::GetInstance()->GotoResultScene();
	}
}


void GameScene::EnemyPattern1(Enemy* it) //8방향 발사
{
	Bullet* b;
	if (it->addDelta2 > 0.5f)
	{
		it->addDelta2 = 0.0f;
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r, it->GetY() + it->r + 30, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r, it->GetY() + it->r - 30, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r + 30, it->GetY() + it->r, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r - 30, it->GetY() + it->r, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}


		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r - 20, it->GetY() + it->r + 10, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r - 20, it->GetY() + it->r - 10, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r - 10, it->GetY() + it->r + 20, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r - 10, it->GetY() + it->r - 20, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}

		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r + 20, it->GetY() + it->r + 10, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r + 20, it->GetY() + it->r - 10, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r + 10, it->GetY() + it->r + 20, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r + 10, it->GetY() + it->r - 20, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
	}
}

void GameScene::EnemyPattern2(Enemy* it) //회오리 발사
{
	if (it->addDelta2 > 0.1f)
	{
		it->addDelta2 = 0.0f;
		if (y >= 3 || y <= -3)
			yup = !yup;
		if (x >= 3 || x <= -3)
			xup = !xup;
		if (xup)
			x++;
		else
			x--;
		if (yup)
			y++;
		else
			y--;

		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, it->GetX() + it->r + x, it->GetY() + it->r + y, eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
	}
}

void GameScene::EnemyPattern3(Enemy* it) //플레이어 유도
{
	if (it->addDelta2 > 0.1f)
	{
		it->addDelta2 = 0.0f;
		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, player->GetX() + (player->r), player->GetY() + (player->r), eObjectType_EBullet);
			bulletVec.emplace_back(b);
		}
	}
}
