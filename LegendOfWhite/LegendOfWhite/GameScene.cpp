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
	player->SPD = 300 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM) * 1.5f);
	player->SSPD = 500 + (GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM) * 3.0f);
	player->HP = GameData::GetInstance()->HP;
	player->CRI = GameData::GetInstance()->CRI;

	SetStartPos(100, 100);
	addDelta2 = 0.0f;
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
	//wallVec.emplace_back(new Wall(3 * GRID, 2 * GRID - 20));
	//wallVec.emplace_back(new Wall(5 * GRID, 4 * GRID - 20));
	//wallVec.emplace_back(new Wall(7 * GRID, 6 * GRID - 20));

	//wallVec.emplace_back(new Wall(12 * GRID, 1 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 2 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 3 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 4 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 5 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 6 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 7 * GRID - 20));
	//wallVec.emplace_back(new Wall(12 * GRID, 8 * GRID - 20));

	nextStageBoard = new NextStage(13 * GRID, 4 * GRID);

	enemy = new Enemy(EEnemyType::eEnemyType_Bird, 1, 30, 600, 300);
	enemyVec.emplace_back(enemy);
	bulletVec.reserve(1000);
}

bool xup = false;
bool yup = true;
int x = 2;
int y = 1;

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
	addDelta2 += Delta;

	if (enemyVec.empty())
	{
		isAllEnemyDead = true;
	}
	else
	{
		for (auto& it : enemyVec)
		{
			it->Update(Delta);

			//패턴1 - 플레이어 유도
			/*if (addDelta2 > 0.1f)
			{
				addDelta2 = 0.0f;
				Bullet* b = AssetManager::GetInstance()->CreateBullet();
				if (b != nullptr)
				{
					b->BulletInit(it->GetX() + it->r, it->GetY() + it->r, player->GetX() + (player->r), player->GetY() + (player->r), eObjectType_EBullet);
					bulletVec.emplace_back(b);
				}
			}*/

			//패턴2 - 8방향 변속
			EnemyPattern1(it);

			
			/*if (addDelta2 > 0.1f)
			{
				addDelta2 = 0.0f;
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
			}*/
		}
		isAllEnemyDead = false;
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
	++CLegendOfWhiteApp::CallCount;
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	
	
	
	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));
	//temp.DrawImage(bgImg.lock().get(), rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 180, 180, 180));
	//MemG->FillRectangle(&WhiteBrush, rect);

	//그려줄 screen좌표의 rect
	//int bg = GetTickCount();
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(bgImg.lock().get(), screenPosRect);
	//bg = GetTickCount() - bg;
	//printf("bgRender : %d \n", bg);

	if (isAllEnemyDead)
		nextStageBoard->Render(MemG);
	//int wallDraw = GetTickCount();
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
	//wallDraw = GetTickCount() - wallDraw;
	//printf("wallDraw : %d \n", wallDraw);
	static bool bInit2 = false;
	if (!bInit2)
	{
		bInit2 = true;
		bm2 = new Gdiplus::Bitmap(WIDTH, HEIGHT, PixelFormat32bppARGB);
	}

	//if (CLegendOfWhiteApp::CallCount % 3)
	//{
	//	Gdiplus::Graphics temp(bm2);
	//	Gdiplus::SolidBrush emptybrush(Gdiplus::Color(0, 0, 0, 0));
	//	temp.SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceCopy);
	//	temp.FillRectangle(&emptybrush, rect);
	//	temp.SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceOver);
		for (auto& it : bulletVec)
		{
			it->Render(MemG);
		}
	//	MemG->DrawImage(bm2, screenPosRect);
	//}
	//else
//	{
//		MemG->DrawImage(bm2, screenPosRect);
//	}

	//int BulletRender = GetTickCount();
	//for (auto& it : bulletVec)
	//{
	//	it->Render(MemG);
	//}

	//BulletRender = GetTickCount() - BulletRender;
	//printf("BulletRender : %d \n", BulletRender);

	//int enemyRender = GetTickCount();
	for (auto& it : enemyVec)
	{
		it->Render(MemG);
	}
	//enemyRender = GetTickCount() - enemyRender;
	//printf("enemyRender : %d \n", enemyRender);

	//int OtherRender = GetTickCount();
	player->Render(MemG);
	UIRender(MemG);
	//OtherRender = GetTickCount() - OtherRender;
	//printf("OtherRender : %d \n", OtherRender);

}

void GameScene::UIRender(Gdiplus::Graphics* MemG)
{
	//Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	//Gdiplus::Graphics temp(&bm);

	Gdiplus::Rect rect(1210, 100, 50, 720);

	tabImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\tab.png"));
	//temp.DrawImage(tabImg.lock().get(), rect, 0, 0, 32, 512, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	Gdiplus::PointF P;
	std::wstring tempStr;
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));
	Gdiplus::Font F3(L"맑은고딕", 30, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	P.X = 10;
	P.Y = 10;
	tempStr = L"LV : " + std::to_wstring(player->LV);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 180;
	P.Y = 10;
	tempStr = L"HP : " + std::to_wstring(player->HP);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 10;
	P.Y = 40;
	tempStr = L"EXP : " + std::to_wstring(player->EXP);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	/*P.X = 100;
	P.Y = 40;
	tempStr = L"X : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().x);
	tempStr.append(L" / Y : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().y));
	temp.DrawString(tempStr.c_str(), -1, &F3, P, &B);*/

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
		b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x, point.y, eObjectType_PBullet);
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
				SetStartPos(100, 100);
				GameData::GetInstance()->HP = 6;
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
		SetStartPos(100, 100);
		GameData::GetInstance()->HP = 6;
		SceneManager::GetInstance()->SetGameClear(true);
		SceneManager::GetInstance()->GotoResultScene();
	}
}

void GameScene::EnemyPattern1(Enemy* it)
{
	Bullet* b;
	if (addDelta2 > 0.5f)
	{
		addDelta2 = 0.0f;
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
