#pragma once
#include "Object.h"
#include "common.h"

class Enemy : public Object
{
public:
	Enemy(EEnemyType enemytype, int enemynum, int hp, int x, int y);
	~Enemy();

	void Init(EEnemyType enemytype, int enemynum, int hp, int x, int y);
	void Release();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);

	EEnemyType enemyType;
	int enemyNum;
	int HP;
	int ATK;
	int SPD;
	
	//�̰� �÷��̾� �߰ݿ��� ����ϴ� ����. �Ϲ������� SPD�� ���
	void SPDSet(int ex, int ey, int px, int py);
	float SPDX;
	float SPDY;

	int SSPD;
	int EXP;
	CPoint center;
	float addDelta;
	float addDelta2;
	bool lookLeft;
	bool moveUp;

	bool ishit;

	std::weak_ptr<Gdiplus::Image> enemyimg;
};

