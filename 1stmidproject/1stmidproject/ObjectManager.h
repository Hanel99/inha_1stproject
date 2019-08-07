#pragma once


class Object
{
public:
	Object()
		: Objtype(eObjectType_None)
	{

	}

	Object(EObjectType InType)
		: Objtype(InType)
	{

	}

	virtual void Begin() {}
	virtual void Update(float Delta)
	{

	}
	virtual void End() {}

public:
	//Gdiplus::Image* ParentImg;
	//Gdiplus::Bitmap Img;

	//CRect rc;
	EObjectType Objtype;
};

class Btn : public Object
{
public:
	Btn()
		: Object(EObjectType::eObjectType_Btn)
	{

	}
	void SendLButtonDown();
	int ID;
};






class PBullet : public Object
{
public:
	PBullet()
		: Object(EObjectType::eObjectType_PBullet)
	{

	}

	/*
	PBullet(CImage& _img, int _startX, int _startY, float _velocityX, float _velocityY)
		: Object(EObjectType::eObjectType_PlayerB)
		, velocityX(_velocityX)
		, velocityY(_velocityY)
		, Dmg(50)
	{
		Img = _img;

		rc.left = _startX;
		rc.top = _startY;
		rc.right = _startX + 25;
		rc.bottom = _startY + 25;
	}
	*/

	virtual void Update(float Delta)
	{
		//rc.MoveToXY(rc.left + Delta * velocityX, rc.top + Delta * velocityY);
	}

	//obj로 바꿔야하지 않을까?
	//bool IsCullMon(std::vector<Enemy*> vec)
	//{
		//CRect Rect;
		//for (auto& it : vec)
		//{
			/*
			if (Rect.IntersectRect(rc, it->rc))
			{
				it->Hp -= Dmg;
				if (it->Hp <= 0)
				{
					it->Enable = false;
					//it->Img.Detach();
					//it->Img.Destroy();

					//delete it;
					//it = nullptr;
				}
				return true;
			}
			*/
		//}
	//}

	float velocityX;
	float velocityY;
	int Dmg;
};

//pbullet 완성후 ebullet 완성할것






class Enemy : public Object
{
public:
	Enemy()
		: Object(EObjectType::eObjectType_Enemy)
		, MonsterType(EMonsterType::eMonsterType_Bird)
		, MonsterNum(0)
		, HP(1)
		, ATK(1)
		, SPD(1)
		, SSPD(1)
	{

	}
	Enemy(EMonsterType montype, int monnum, int hp)
		: Object(EObjectType::eObjectType_Enemy)
		, MonsterType(montype)
		, MonsterNum(monnum)
		, HP(hp)
		, ATK(1)
		, SPD(100)
		, SSPD(100)
	{

	}

	virtual void Update(float Delta)
	{
		//rc.MoveToXY(rc.left, rc.top + 100 * Delta);
	}

	EMonsterType MonsterType;
	int MonsterNum;
	int HP;
	int ATK;
	int SPD;
	int SSPD;
};


class Player : public Object
{
public:
	Player()
		: Object(EObjectType::eObjectType_Player)
		, HP(3)
		, ATK(1)
		, SPD(100)
		, SSPD(100)
		, CRI(0)
	{

	}

	virtual void Update(float Delta) {}

	int HP;
	int ATK;
	int SPD;
	int SSPD;
	float CRI;
};

class StaticObject : public Object
{
public:
	StaticObject()
		: Object(EObjectType::eObjectType_Static)
	{

	}
};
