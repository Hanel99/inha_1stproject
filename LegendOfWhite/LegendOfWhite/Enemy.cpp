#include "pch.h"
#include "Enemy.h"

#define STAGE_X 50
#define STAGE_WIDTH WIDTH-160
#define STAGE_Y 30
#define STAGE_HEIGHT HEIGHT-160

Enemy::Enemy(EEnemyType enemytype, int enemynum, int hp, int x, int y)
	: Object(EObjectType::eObjectType_Enemy)
	, enemyType(enemytype)
	, enemyNum(enemynum)
	, HP(hp)
	, ATK(1)
	, SPD(200)
	, SSPD(10)
	, EXP(hp * 3)
	, addDelta(0.0f)
	, addDelta2(0.0f)
	, lookLeft(true)
	, moveUp(false)
{
	SetX(x);
	SetY(y);
	if (enemytype == eEnemyType_Boss)
	{
		width = 140;
		height = 140;
	}
	else
	{
		width = 80;
		height = 80;
	}

	switch (enemytype)
	{
	case eEnemyType_Bird:
		SPD = 200;
		break;
	case eEnemyType_Digda:
		SPD = 0;
		break;
	case eEnemyType_Digda2:
		SPD = 200;
		break;
	case eEnemyType_Slime:
		SPD = 50;
		break;
	case eEnemyType_Devil:
		SPD = 400;
		break;
	case eEnemyType_Boss:
		SPD = 300;
		break;

	}
	r = width / 2;
	center.x = GetX() + r;
	center.y = GetY() + r;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float Delta)
{
	addDelta += Delta;
	addDelta2 += Delta;

	if (Delta > 0.1f) //처음 튀는거 방지
	{
		addDelta = 0.0;
		addDelta2 = 0.0f;
	}		

	switch (enemyType)
	{
	case eEnemyType_Bird:
		//벽 튕기며 이동
		if (lookLeft)
		{
			SetX(GetX() - Delta * SPD);
		}
		else
		{
			SetX(GetX() + Delta * SPD);
		}

		if (GetX() < STAGE_X || GetX() > STAGE_WIDTH)
		{
			enemyimg.lock().get()->RotateFlip(Gdiplus::Rotate180FlipY);
			lookLeft = !lookLeft;
		}

		if (moveUp)
		{
			SetY(GetY() - Delta * SPD);
		}
		else
		{
			SetY(GetY() + Delta * SPD);
		}

		if (GetY() < STAGE_Y || GetY() > STAGE_HEIGHT)
		{
			moveUp = !moveUp;
		}
		break;

	case eEnemyType_Digda:
		//이동 없음
		break;

	case eEnemyType_Digda2:
		//아주 느리게 플레이어 추격
		if (addDelta > 0.02f)
		{
			addDelta = 0.0f;
			SPDSet(GetX(), GetY(), GameData::GetInstance()->player->GetX(), GameData::GetInstance()->player->GetY());
			SetX(GetX() + Delta * SPDX * SPD);
			SetY(GetY() + Delta * SPDY * SPD);
		}
		break;

	case eEnemyType_Slime:
		//느리게 벽 튕기며 이동
		if (lookLeft)
		{
			SetX(GetX() - Delta * SPD);
		}
		else
		{
			SetX(GetX() + Delta * SPD);
		}

		if (GetX() < STAGE_X || GetX() > STAGE_WIDTH)
		{
			enemyimg.lock().get()->RotateFlip(Gdiplus::Rotate180FlipY);
			lookLeft = !lookLeft;
		}

		if (moveUp)
		{
			SetY(GetY() - Delta * SPD);
		}
		else
		{
			SetY(GetY() + Delta * SPD);
		}

		if (GetY() < STAGE_Y || GetY() > STAGE_HEIGHT)
		{
			moveUp = !moveUp;
		}
		break;

	case eEnemyType_Devil:
		//보통 속도로 플레이어 추격
		if (addDelta > 0.02f)
		{
			addDelta = 0.0f;
			SPDSet(GetX(), GetY(), GameData::GetInstance()->player->GetX(), GameData::GetInstance()->player->GetY());
			SetX(GetX() + Delta * SPDX * SPD);
			SetY(GetY() + Delta * SPDY * SPD);
		}
		break;

	case eEnemyType_Boss:
		//아주 빠르게 벽 튕기며 이동
		if (lookLeft)
		{
			SetX(GetX() - Delta * SPD);
		}
		else
		{
			SetX(GetX() + Delta * SPD);
		}

		if (GetX() < STAGE_X || GetX() > STAGE_WIDTH)
		{
			enemyimg.lock().get()->RotateFlip(Gdiplus::Rotate180FlipY);
			lookLeft = !lookLeft;
		}

		if (moveUp)
		{
			SetY(GetY() - Delta * SPD);
		}
		else
		{
			SetY(GetY() + Delta * SPD);
		}

		if (GetY() < STAGE_Y || GetY() > STAGE_HEIGHT)
		{
			moveUp = !moveUp;
		}
		break;
	}

	center.x = GetX() + width / 2;
	center.y = GetY() + height / 2;
}

void Enemy::Render(Gdiplus::Graphics* MemG)
{
	if (enemyType == eEnemyType_Boss)
	{
		Gdiplus::Rect rect(0, 0, 256, 256);
	}
	else
	{
		Gdiplus::Rect rect(0, 0, 100, 100);
	}

	switch (enemyType)
	{
	case eEnemyType_Boss: //보스
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\boss.png"));
		break;
	case eEnemyType_Bird: //새
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bird.png"));
		break;
	case eEnemyType_Digda: //디그다
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\dig.png"));
		break;
	case eEnemyType_Digda2: //디그다2
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\dig2.png"));
		break;
	case eEnemyType_Slime: //슬라임
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\sli.png"));
		break;
	case eEnemyType_Devil: //악마
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\dev.png"));
		break;
	default:
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bird.png"));
		break;
	}
	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);
	MemG->DrawImage(enemyimg.lock().get(), screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}

void Enemy::SPDSet(int ex, int ey, int px, int py)
{
	if (abs(px - ex) < 0.01f && abs(py - ey) < 0.01f)
	{
		SPDX = 0.0f;
		SPDY = 0.0f;
	}
	else
	{
		float length = sqrtf(pow(abs(px - ex), 2) + pow(abs(py - ey), 2));
		SPDX = abs(px - ex) / length;
		SPDY = abs(py - ey) / length;

		if (px < ex)
			SPDX = -SPDX;
		if (py < ey)
			SPDY = -SPDY;
	}
}
