#pragma once
#include "framework.h"


class Object
{
public:
	Object()
		: Objtype(eObjectType_None)
		, Enable(true)
	{

	}

	Object(EObjectType InType)
		: Objtype(InType)
		, Enable(true)
	{

	}

	virtual void Begin() {}
	virtual void Update(float Delta)
	{
	}




	virtual void End() {}

	CImage* ParentImg;
	CImage Img;

	CRect rc;
	EObjectType Objtype;
	bool Enable;
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

class Enemy : public Object
{
public:
	Enemy()
		: Object(EObjectType::eObjectType_Enemy)
		, Hp(1500)
	{

	}

	virtual void Update(float Delta)
	{
		rc.MoveToXY(rc.left, rc.top + 100 * Delta);
	}

	int Hp;
};

class Bullet : public Object
{
public:
	Bullet()
		: Object(EObjectType::eObjectType_Bullet)
	{

	}

	Bullet(CImage& _img, int _startX, int _startY, float _velocityX, float _velocityY)
		: Object(EObjectType::eObjectType_Bullet)
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

	virtual void Update(float Delta)
	{
		rc.MoveToXY(rc.left + Delta * velocityX, rc.top + Delta * velocityY);
	}

	bool IsCullBull(std::vector<Enemy*> vec)
	{
		CRect Rect;
		for (auto& it : vec)
		{
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
		}
	}

	float velocityX;
	float velocityY;
	int Dmg;
};

class Player : public Object
{
public:
	Player()
		: Object(EObjectType::eObjectType_Player)
		, AddDelta(0)
		, Rate(0.1f)
	{
		Vel = 500;
	}

	virtual void Update(float Delta);


	float Rate;
	float AddDelta;
	float Vel;
	Bullet temp;
};

class StaticObject : public Object
{
public:
	StaticObject()
		: Object(EObjectType::eObjectType_Static)
	{

	}
};

class Scene
{
public:
	void Start();
	void Loop(float Delta);
	void End();
	bool bLoop;
	CString Name;
	std::vector<Object*> info;
};

class SceneManager
{
public:
	SceneManager();
	void LoadScene(CString& pName);
	void RenderScene(CDC* pDC);
	Scene* GetCurScene();
	static SceneManager& GetInstance();
	void SendLButtonDown(UINT nFlags, CPoint point);
	void Update(float Delta);

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
};

