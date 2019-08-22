#include "pch.h"
#include "Enemy.h"


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
	default:
		enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bird.png"));
		break;
	}

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);
	
	MemG->DrawImage(enemyimg.lock().get(), screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
