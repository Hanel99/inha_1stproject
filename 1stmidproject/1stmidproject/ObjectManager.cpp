#include "pch.h"
#include "ObjectManager.h"


void Enemy::Update(float Delta)
{
	//rc.MoveToXY(rc.left, rc.top + 100 * Delta);
}

void Player::Update(float Delta)
{
	/*
	
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		rc.MoveToXY(rc.left, rc.top - Delta * Vel);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		rc.MoveToXY(rc.left, rc.top + Delta * Vel);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		rc.MoveToXY(rc.left - Delta * Vel, rc.top);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		rc.MoveToXY(rc.left + Delta * Vel, rc.top);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		AddDelta += Delta;
		if (AddDelta > Rate)
		{
			AddDelta = 0;
			SceneManager::GetInstance().GetCurScene()->info.emplace_back(
				new Bullet(temp.Img, rc.CenterPoint().x - 25, rc.CenterPoint().y - rc.Height() * 0.5f, 300, -500));
			SceneManager::GetInstance().GetCurScene()->info.emplace_back(
				new Bullet(temp.Img, rc.CenterPoint().x, rc.CenterPoint().y - rc.Height() * 0.5f, 0, -500));
			SceneManager::GetInstance().GetCurScene()->info.emplace_back(
				new Bullet(temp.Img, rc.CenterPoint().x + 25, rc.CenterPoint().y - rc.Height() * 0.5f, -300, -500));
		}
	}
	*/
}
