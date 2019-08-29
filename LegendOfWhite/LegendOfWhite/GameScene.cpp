#include "pch.h"
#include "GameScene.h"
#include "LegendOfWhite.h"

GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
	Release();
}

#define GRID 60


void GameScene::SceneSetting()
{
	delete nextStageBoard;
	player = GameData::GetInstance()->player;
	player->issafe = false;

	player->ATK = (player->LV + GameData::GetInstance()->ATKP) * (1 + GameData::GetInstance()->ATKM);
	player->SPD = 500 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM) * 1.5f);
	player->SSPD = 800 + (GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM) * 3.0f);
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

	enemyVec.clear();
	enemyVec.empty();

	for (auto& it : GameData::GetInstance()->DBSceneVec)
	{
		if (it->chapter == GameData::GetInstance()->chapternum && it->stage == GameData::GetInstance()->stagenum)
		{
			if (it->enemytype == eEnemyType_Boss)
			{
				enemyVec.emplace_back(new Enemy((EEnemyType)it->enemytype, 1, 200 * it->stage * it->chapter, it->x * GRID, it->y * GRID));
			}
			else
			{
				enemyVec.emplace_back(new Enemy((EEnemyType)it->enemytype, 1, 15 * it->stage * it->chapter, it->x * GRID, it->y * GRID));
			}
		}
	}
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
	bm = new Gdiplus::Bitmap(WIDTH, HEIGHT, PixelFormat32bppARGB);

	B = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255));
	B_Exp = new Gdiplus::SolidBrush(Gdiplus::Color(255, 236, 79)); // EXP 색
	B_Chapter = new Gdiplus::SolidBrush(Gdiplus::Color(76, 101, 228)); // chapter 색

	F_24 = new Gdiplus::Font(L"Arial rounded MT Bold", 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	F_30 = new Gdiplus::Font(L"Arial rounded MT Bold", 30, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
}

void GameScene::Release()
{
	for (auto& it : wallVec)
	{
		delete it;
	}
	for (auto& it : enemyVec)
	{
		delete it;
	}
	delete bm;
	delete F_24;
	delete F_30;
}

void GameScene::Update(float Delta)
{
	if (SceneManager::GetInstance()->isComeGameScene)
	{
		SceneManager::GetInstance()->isComeGameScene = false;
		SceneSetting();
	}
	//탭 키로 스탯창으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
	//esc키로 메인화면으로 
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1001)
	{
		SceneManager::GetInstance()->GotoTitleScene();
	}
	player->Update(Delta);
	IsPlayerColl(player, Delta);

	if (enemyVec.empty())
	{
		isAllEnemyDead = true;
	}
	else
	{
		for (auto& it : enemyVec)
		{
			it->Update(Delta);

			switch (it->enemyType)
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
			case eEnemyType_Devil: //악마
				EnemyPattern5(it);
				break;
			case eEnemyType_Boss: //보스
				EnemyPattern6(it);
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
		//if (it == nullptr)   break;
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

	uibgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\uibgImg.png")); // uibg 배경
	Gdiplus::Rect screenPosRect2(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(uibgImg.lock().get(), screenPosRect2);

	Gdiplus::PointF P;
	std::wstring tempStr;

	Gdiplus::RectF R(-10, 40, 100 ,40);
	Gdiplus::StringFormat SF;
	SF.SetAlignment(Gdiplus::StringAlignmentCenter);
	SF.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	tempStr = L" " + std::to_wstring(player->LV); // LEVEL
	MemG->DrawString(tempStr.c_str(), -1, F_30, R, &SF, B);

	P.X = 160;
	P.Y = 11;
	tempStr = L" " + std::to_wstring(player->HP);  // HP
	MemG->DrawString(tempStr.c_str(), -1, F_24, P, B);

	P.X = 292;
	P.Y = 11;
	tempStr = L"EXP : " + std::to_wstring(player->EXP); // EXP
	MemG->DrawString(tempStr.c_str(), -1, F_24, P, B_Exp);

	P.X = 1030;
	P.Y = 11;
	tempStr = L"CHAPTER : " + std::to_wstring(GameData::GetInstance()->chapternum); // Chapter
	tempStr.append(L"  - " + std::to_wstring(GameData::GetInstance()->stagenum)); //Stage
	MemG->DrawString(tempStr.c_str(), -1, F_24, P, B_Chapter);

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
	// 탭 열기
	if (MouseManager::GetInstance()->GetMousePos().x >= 1220 && MouseManager::GetInstance()->GetMousePos().x <= 1260
		&& MouseManager::GetInstance()->GetMousePos().y >= 180 && MouseManager::GetInstance()->GetMousePos().y <= 510)
	{
		AssetManager::GetInstance()->PlaySound(eSound_BtnClick);
		SceneManager::GetInstance()->SwapStatusScene();
	}
	else
	{
		AssetManager::GetInstance()->PlaySound(eSound_Shot);
		Bullet* b = AssetManager::GetInstance()->CreateBullet();
		if (rand() % 100 < player->CRI * 100)
		{
			b->isCritical = true;
		}
		else
		{
			b->isCritical = false;
		}
		if (b != nullptr)
		{
			b->BulletInit(player->GetX() + (player->r), player->GetY() + (player->r), point.x, point.y, eObjectType_PBullet, 1);
			bulletVec.emplace_back(b);
		}
	}
}

void GameScene::SendRButtonDown(UINT nFlags, CPoint point)
{

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
				it->ishit = true;
				if (b->isCritical)
				{
					it->HP -= player->ATK * 1.5f;
				}
				else
				{
					it->HP -= player->ATK;
				}
				if (it->HP <= 0)
				{
					std::vector<Enemy*>::iterator itr = std::find(enemyVec.begin(), enemyVec.end(), it);
					enemyVec.erase(itr);
					player->EXP += it->EXP;
					AssetManager::GetInstance()->PlaySound(eSound_EnemyDead);
				}
				AssetManager::GetInstance()->RetrunBullet(b);
				ReturnBulletFromGameScene(b);
			}
		}
	}
	if (pow((player->center.x - b->center.x), 2) + pow((player->center.y - b->center.y), 2) <= pow((player->r + b->r), 2))
	{
		if (b->Objtype == eObjectType_EBullet)
		{
			//몬스터의 총알과 플레이어가 충돌
			if (!GameData::GetInstance()->player->issafe)//무적시간이 아니라면
			{
				GameData::GetInstance()->player->issafe = true;
				AssetManager::GetInstance()->RetrunBullet(b);
				ReturnBulletFromGameScene(b);
				player->HP -= 1;
				AssetManager::GetInstance()->PlaySound(eSound_PlayerDamaged);
				if (player->HP <= 0)
				{
					//플레이어 사망
					AssetManager::GetInstance()->PlaySound(eSound_GameOver);
					SceneManager::GetInstance()->SetGameClear(false);
					SceneManager::GetInstance()->GotoResultScene();
				}
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
		//NextStage 발판을 밟았을 경우
		if (GameData::GetInstance()->stagenum == 11)
		{
			//보스 스테이지 클리어의 경우
			AssetManager::GetInstance()->PlaySound(eSound_GameClear);
			SceneManager::GetInstance()->SetGameClear(true);
			GameData::GetInstance()->chapternum++;
			GameData::GetInstance()->stagenum = 1;
			GameData::GetInstance()->SavePlayerData();
			SceneManager::GetInstance()->GotoResultScene();
		}
		else
		{
			//일반 스테이지 클리어의 경우
			AssetManager::GetInstance()->PlaySound(eSound_NextStage);
			GameData::GetInstance()->stagenum++;
			SceneSetting();
		}
	}
}

//8방향 발사. 
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

//회오리 발사 
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

//플레이어 유도 
void GameScene::EnemyPattern3(Enemy* it)
{
	if (it->addDelta2 > 0.3f)
	{
		it->addDelta2 = 0.0f;
		for (int i = -1; i < 2; i++)
		{
			Bullet* b = AssetManager::GetInstance()->CreateBullet();
			if (b != nullptr)
			{
				b->BulletInit(it->center.x, it->center.y, player->center.x + i * 30, player->center.y + i * 30, eObjectType_EBullet, 500);
				bulletVec.emplace_back(b);
			}
		}
	}
}

//쌍 레이저 발사
void GameScene::EnemyPattern4(Enemy* it)
{
	int MAX = 31;
	if (it->addDelta2 > 0.05f)
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

//플레이어 저격하는 속도다른 16개 탄
void GameScene::EnemyPattern5(Enemy* it)
{
	if (it->addDelta2 > 0.5f)
	{
		it->addDelta2 = 0.0f;
		for (int i = 0; i < 16; i++)
		{
			Bullet* b = AssetManager::GetInstance()->CreateBullet();
			if (b != nullptr)
			{
				b->BulletInit(it->center.x, it->center.y, player->center.x, player->center.y, eObjectType_EBullet, 200 + (i * 50));
				bulletVec.emplace_back(b);
			}
		}
	}
}

//1패턴 강화 Boss
void GameScene::EnemyPattern6(Enemy* it)
{
	if (it->addDelta2 > 0.2f)
	{
		//8방향
		it->addDelta2 = 1.0f;
		EnemyPattern1(it);
	}
}
