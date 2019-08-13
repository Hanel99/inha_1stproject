#pragma once
#include "Object.h"
#include "GameData.h"

class Bullet : public Object
{
public:
	Bullet()
		: Object(EObjectType::eObjectType_EBullet)
		, ATK(GameData::GetInstance()->player->ATK)
		, SSPD(GameData::GetInstance()->player->SSPD)
	{
		width = 40;
		height = 40;
		Init();
	}

	void Init();
	void ProcessInput();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

private:
	int ATK;
	int SSPD;

	std::weak_ptr<Gdiplus::Image> bulletimg;
};

