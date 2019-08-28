#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
	: Object(EObjectType::eObjectType_Enemy)
	, EnemyType(EEnemyType::eEnemyType_Bird)
	, EnemyNum(1)
	, HP(10)
	, ATK(1)
	, SPD(1)
	, SSPD(1)
	, EXP(1000)
	, addDelta(0.0f)
	, addDelta2(0.0f)
{
	SetX(500);
	SetY(500);
	width = 10;
	height = 10;
	r = width / 2;
	center.x = GetX() + r;
	center.y = GetY() + r;
}

Enemy::Enemy(EEnemyType enemytype, int enemynum, int hp, int x, int y)
	: Object(EObjectType::eObjectType_Enemy)
	, EnemyType(enemytype)
	, EnemyNum(enemynum)
	, HP(hp)
	, ATK(1)
	, SPD(100)
	, SSPD(10)
	, EXP(hp * 3)
	, addDelta(0.0f)
	, addDelta2(0.0f)
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
	r = width / 2;
	center.x = GetX() + r;
	center.y = GetY() + r;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float Delta)
{
	if (this->EnemyType == eEnemyType_Boss)
	{
		this->SetX(GetX());
		this->SetY(GetY());

	}
	addDelta += Delta;
	addDelta2 += Delta;
}

void Enemy::Render(Gdiplus::Graphics* MemG)
{
	if (this->EnemyType == eEnemyType_Boss)
	{
		Gdiplus::Rect rect(0, 0, 256, 256);
	}
	else
	{
		Gdiplus::Rect rect(0, 0, 100, 100);
	}

	switch (this->EnemyType)
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
	default:
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bird.png"));
		break;
	}

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);
	
	MemG->DrawImage(enemyimg.lock().get(), screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
