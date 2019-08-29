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
	Init(enemytype, enemynum, hp, x, y);
}

Enemy::~Enemy()
{
	Release();
}

void Enemy::Init(EEnemyType enemytype, int enemynum, int hp, int x, int y)
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
		SPD = 100;
		break;
	case eEnemyType_Slime:
		SPD = 100;
		break;
	case eEnemyType_Devil:
		SPD = 200;
		break;
	case eEnemyType_Boss:
		SPD = 300;
		break;
	}
	r = width / 2;
	center.x = GetX() + r;
	center.y = GetY() + r;
	ishit = false;
}

void Enemy::Release()
{
}

void Enemy::Update(float Delta)
{
	addDelta += Delta;
	addDelta2 += Delta;

	if (Delta > 0.1f) //ó�� Ƣ�°� ����
	{
		addDelta = 0.0;
		addDelta2 = 0.0f;
	}

	if (ishit)
	{
		addDelta += Delta;
		if (addDelta > 0.1f)
		{
			ishit = false;
		}
	}
	else
	{
		addDelta = 0;
	}

	switch (enemyType)
	{
	case eEnemyType_Bird:
		//�� ƨ��� �̵�
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
		//�̵� ����
		break;

	case eEnemyType_Digda2:
		//���� ������ �÷��̾� �߰�		
		SPDSet(GetX(), GetY(), GameData::GetInstance()->player->GetX(), GameData::GetInstance()->player->GetY());
		SetX(GetX() + Delta * SPDX * SPD);
		SetY(GetY() + Delta * SPDY * SPD);
		break;

	case eEnemyType_Slime:
		//������ �� ƨ��� �̵�
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
		//���� �ӵ��� �÷��̾� �߰�
		SPDSet(GetX(), GetY(), GameData::GetInstance()->player->GetX(), GameData::GetInstance()->player->GetY());
		SetX(GetX() + Delta * SPDX * SPD);
		SetY(GetY() + Delta * SPDY * SPD);
		break;

	case eEnemyType_Boss:
		//���� ������ �� ƨ��� �̵�
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

	if (ishit)
	{
		float R = 255.0f;
		float alpha = 0.8f;
		//�ǰݻ������� ǥ���� ������ ���� ���� �̹��� ó��
		Gdiplus::ColorMatrix colorMatrix = { R, 0.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
											0.0f, 0.0f, 0.0f, alpha, 0.0f,
											0.0f, 0.0f, 0.0f, 0.0f, 0.5f };

		Gdiplus::ImageAttributes imageAtt;
		imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		MemG->DrawImage(enemyimg.lock().get(), screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, &imageAtt, 0, nullptr);
	}
	else
	{
		MemG->DrawImage(enemyimg.lock().get(), screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}
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
