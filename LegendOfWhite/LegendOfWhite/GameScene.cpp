#include "pch.h"
#include "GameScene.h"
#include "LegendOfWhite.h"

GameScene::GameScene()
{
	Init();
}

#define GRID 60


void GameScene::SceneSetting()
{
	player = GameData::GetInstance()->player;

	player->ATK = (player->LV + GameData::GetInstance()->ATKP) * (1 + GameData::GetInstance()->ATKM);
	player->SPD = 500 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM) * 1.5f);
	player->SSPD = 800 + (GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM) * 3.0f);
	player->HP = GameData::GetInstance()->MAXHP;
	player->CRI = GameData::GetInstance()->CRI;

	SetStartPos(100, 100);
	isAllEnemyDead = false;
	int x = rand() % 16 + 2;
	int y = rand() % 7 + 2;

	nextStageBoard = new NextStage(x * GRID, y * GRID);

	for (auto& it : bulletVec)
	{
		AssetManager::GetInstance()->RetrunBullet(it);
		ReturnBulletFromGameScene(it);
	}
	bulletVec.clear();
	bulletVec.empty();

	enemy = new Enemy(EEnemyType::eEnemyType_Bird, 1, 30, 600, 300);
	enemyVec.emplace_back(enemy);
}

void GameScene::Init()
{
	SceneSetting();	
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
	bulletVec.reserve(1000);
}

void GameScene::Update(float Delta)
{
	if (SceneManager::GetInstance()->isComeGameScene)
	{
		SceneManager::GetInstance()->isComeGameScene = false;
		SceneSetting();
	}
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
			int a = rand() % 5;
			enemy = new Enemy((EEnemyType)a, 1, 30, 600, 300);
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

			switch (it->EnemyType)
			{
			case eEnemyType_Bird: //새
				EnemyPattern1(it);
				break;
			case eEnemyType_Digda: //디그다
				EnemyPattern2(it);
				break;
			case eEnemyType_Digda2: //디그다2
				EnemyPattern3(it);
				break;
			case eEnemyType_Slime: //슬라임
				EnemyPattern4(it);
				break;
			case eEnemyType_Boss: //보스
				if (it->addDelta > 3.0f)
				{
					it->addDelta = 0.0f;
					pattern++;
					if (pattern >= 4) pattern = 0;
				}

				switch (pattern)
				{
				case 0:
					EnemyPattern1(it);
					EnemyPattern2(it);
					break;
				case 1:
					EnemyPattern2(it);
					EnemyPattern3(it);
					break;
				case 2:
					EnemyPattern3(it);
					EnemyPattern4(it);
					break;
				case 3:
					EnemyPattern4(it);
					EnemyPattern1(it);
					EnemyPattern5(it);
					break;
				default:
					EnemyPattern5(it);
					EnemyPattern1(it);
					break;
				}
				break;
			default:
				EnemyPattern1(it);
				break;
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

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(bgImg.lock().get(), screenPosRect);

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
	UIRender(MemG);
}

void GameScene::UIRender(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(1220, 180, 40, 330);
	tabImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\tab.png"));

	uibgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\uibgImg.png")); // ui 배경
	Gdiplus::Rect screenPosRect2(0, 0, 340, 90); // ui배경
	MemG->DrawImage(uibgImg.lock().get(), screenPosRect2);

	stagebgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\stagebgImg.png")); // ui 배경
	Gdiplus::Rect screenPosRect3(1085, 0, 234, 68); // ui배경
	MemG->DrawImage(stagebgImg.lock().get(), screenPosRect3);

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
	tempStr = L"CHAPTER : " + std::to_wstring(GameData::GetInstance()->chapternum);
	MemG->DrawString(tempStr.c_str(), -1, &F4, P, &B5);

	P.X = 1128;
	P.Y = 33;
	tempStr = L"STAGE : " + std::to_wstring(GameData::GetInstance()->stagenum);
	MemG->DrawString(tempStr.c_str(), -1, &F4, P, &B6);

	//P.X = 200;
	//P.Y = 56;
	//tempStr = L"X : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().x);
	//tempStr.append(L" / Y : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().y));
	//MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(tabImg.lock().get(), rect, 0, 0, 32, 512, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
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
		b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x, point.y, eObjectType_PBullet, 1);
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
			b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x + i * 10, point.y + i * 10, eObjectType_PBullet, 1);
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

//8방향 발사. Bird
void GameScene::EnemyPattern1(Enemy* it) 
{
	Bullet* b;
	if (it->addDelta2 > 0.5f)
	{
		it->addDelta2 = 0.0f;
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x, it->center.y + 30, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x, it->center.y - 30, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + 30, it->center.y, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x - 30, it->center.y, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}


		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x - 20, it->center.y + 10, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x - 20, it->center.y - 10, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x - 10, it->center.y + 20, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x - 10, it->center.y - 20, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}

		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + 20, it->center.y + 10, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + 20, it->center.y - 10, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + 10, it->center.y + 20, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + 10, it->center.y - 20, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);
		}
	}
}

//회오리 발사 Digda
void GameScene::EnemyPattern2(Enemy* it) 
{
	int MAX = 7;
	if (it->addDelta2 > 0.02f)
	{
		it->addDelta2 = 0.0f;
		if (p2y > MAX || p2y < -MAX)
			p2yup = !p2yup;
		if (p2x > MAX || p2x < -MAX)
			p2xup = !p2xup;
		if (p2xup)
			p2x++;
		else
			p2x--;
		if (p2yup)
			p2y++;
		else
			p2y--;

		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + p2x, it->center.y + p2y, eObjectType_EBullet, 600);
			bulletVec.emplace_back(b);
		}
	}
}

//플레이어 유도 Digda2
void GameScene::EnemyPattern3(Enemy* it) 
{
	if (it->addDelta2 > 0.3f)
	{
		it->addDelta2 = 0.0f;
		for (int i = -2; i < 3; i++)
		{
			Bullet* b = AssetManager::GetInstance()->CreateBullet();
			if (b != nullptr)
			{
				b->BulletInit(it->center.x, it->center.y, player->GetX() + (player->r), player->GetY() + i * 10 + (player->r)+ i * 10, eObjectType_EBullet, 600);
				bulletVec.emplace_back(b);
			}
		}		
	}
}

//쌍 레이저 발사 Slime
void GameScene::EnemyPattern4(Enemy* it) 
{
	int MAX = 31;
	if (it->addDelta2 > 0.02f)
	{
		it->addDelta2 = 0.0f;
		if (p4y > MAX || p4y < -MAX)
			p4yup = !p4yup;
		if (p4x > MAX || p4x < -MAX)
			p4xup = !p4xup;
		if (p4xup)
			p4x++;
		else
			p4x--;
		if (p4yup)
			p4y++;
		else
			p4y--;

		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x + p4x, it->center.y + p4y, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);

		}
		b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, it->center.x - p4x, it->center.y - p4y, eObjectType_EBullet, 400);
			bulletVec.emplace_back(b);

		}
	}
}

//빠른 플레이어 유도 Boss
void GameScene::EnemyPattern5(Enemy* it)
{
	if (it->addDelta2 > 0.3f)
	{
		it->addDelta2 = 0.0f;
		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (b != nullptr)
		{
			b->BulletInit(it->center.x, it->center.y, player->GetX() + (player->r), player->GetY() + (player->r), eObjectType_EBullet, 1200);
			bulletVec.emplace_back(b);
		}
	}
}
