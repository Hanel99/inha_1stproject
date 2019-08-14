#pragma once
#include "Object.h"
#include "GameData.h"

#define DefaultSPD 500

class Bullet : public Object
{
public:
	Bullet()
		: Object(EObjectType::eObjectType_EBullet)
		, SPD(DefaultSPD)
		, damage(1)
		, SPDY(1)
		, SPDX(1)
	{
		width = 40;
		height = 40;
	}
	Bullet(int px, int py, int clickx, int clicky)
		: Object(EObjectType::eObjectType_EBullet)
		, damage(GameData::GetInstance()->player->ATK)
		, SPD(DefaultSPD)
	{
		width = 40;
		height = 40;
		SPDSet(px, py, clickx, clicky);
		SetX(px);
		SetY(py);
	}

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SPDSet(int px, int py, int clickx, int clicky);
	void BulletInit(int px, int py, int clickx, int clicky);
	void BulletReset();

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
			//rc�� bullet�� rc
			if (Rect.IntersectRect(rc, it->rc))
			{
				it->Hp -= Dmg;
				if (it->Hp <= 0)
				{
					//Object�� Enable ���� ���ؼ� ������� �����ִ� �κ�
					//enemy�� Enable�� false��
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
