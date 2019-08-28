#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
	: Object(EObjectType::eObjectType_Enemy)
	, enemyType(EEnemyType::eEnemyType_Bird)
	, enemyNum(1)
	, HP(10)
	, ATK(1)
	, SPD(1)
	, SSPD(1)
	, EXP(1000)
	, addDelta(0.0f)
	, addDelta2(0.0f)
	, lookLeft(true)
	, moveUp(false)
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
	, enemyType(enemytype)
	, enemyNum(enemynum)
	, HP(hp)
	, ATK(1)
	, SPD(100)
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

	if (Delta < 0.1f) //ó�� Ƣ�°� ����
	{
		switch (enemyType)
		{
		case eEnemyType_Bird:
			if (lookLeft)
			{
				SetX(GetX() - Delta * 300);
			}
			else
			{
				SetX(GetX() + Delta * 300);
			}
			if (GetX() < 60 || GetX() > WIDTH-60)
			{
				enemyimg.lock().get()->RotateFlip(Gdiplus::Rotate180FlipY);
				lookLeft = !lookLeft;
			}

			if (moveUp)
			{
				SetY(GetX() - Delta * 300);
			}
			else
			{
				SetY(GetX() + Delta * 300);
			}
			if (GetY() < 60 || GetY() > 500)
			{
				moveUp = !moveUp;
			}
			break;

		case eEnemyType_Digda:
			SetX(GetX());
			SetY(GetY());
			break;

		case eEnemyType_Digda2:
			SetX(GetX());
			SetY(GetY());
			break;

		case eEnemyType_Slime:
			SetX(GetX());
			SetY(GetY());
			break;

		case eEnemyType_Devil:
			SetX(GetX());
			SetY(GetY());
			break;

		case eEnemyType_Boss:
			SetX(GetX());
			SetY(GetY());
			break;
		}
	}

	center.x = GetX() + width / 2;
	center.y = GetY() + height / 2;
}

void Enemy::Render(Gdiplus::Graphics* MemG)
{
	if (this->enemyType == eEnemyType_Boss)
	{
		Gdiplus::Rect rect(0, 0, 256, 256);
	}
	else
	{
		Gdiplus::Rect rect(0, 0, 100, 100);
	}

	switch (this->enemyType)
	{
	case eEnemyType_Boss: //����
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\boss.png"));
		break;
	case eEnemyType_Bird: //��
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bird.png"));
		break;
	case eEnemyType_Digda: //��״�
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\dig.png"));
		break;
	case eEnemyType_Digda2: //��״�2
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\dig2.png"));
		break;
	case eEnemyType_Slime: //������
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\sli.png"));
		break;
	case eEnemyType_Devil: //�Ǹ�
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\dev.png"));
		break;
	default:
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bird.png"));
		break;
	}
	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);
	MemG->DrawImage(enemyimg.lock().get(), screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
