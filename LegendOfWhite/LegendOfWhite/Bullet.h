#pragma once
#include "Object.h"
#include "GameData.h"

class Bullet : public Object
{
public:
	Bullet()
		: Object(EObjectType::eObjectType_EBullet)
		, damage(GameData::GetInstance()->player->ATK)
		, SPD(300)
		, SPDX(1)
		, SPDY(1)
	{
		width = 40;
		height = 40;
	}
	Bullet(int px, int py, int clickx, int clicky)
		: Object(EObjectType::eObjectType_EBullet)
		, damage(GameData::GetInstance()->player->ATK)
		, SPD(300)
	{
		width = 40;
		height = 40;
		SPDSet(px, py, clickx, clicky);
		SetX(px);
		SetY(py);
	}

	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SPDSet(int px, int py, int clickx, int clicky);

private:
	int damage;
	int SPD;
	float SPDX;
	float SPDY;

	std::weak_ptr<Gdiplus::Image> bulletimg;
};


/*
	bool IsCullBull(std::vector<Enemy*> vec)
	{
		CRect Rect;
		for (auto& it : vec)
		{
			//rc는 bullet의 rc
			if (Rect.IntersectRect(rc, it->rc))
			{
				it->Hp -= Dmg;
				if (it->Hp <= 0)
				{
					//Object에 Enable 값을 정해서 출력할지 정해주는 부분
					//enemy의 Enable을 false로
					it->Enable = false;

					//it->Img.Detach();
					//it->Img.Destroy();

					//delete it;
					//it = nullptr;
				}
				return true;
			}
		}
	}

	float velocityX;
	float velocityY;
	int Dmg;
};

*/
