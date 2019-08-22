#pragma once
#include "Singleton.h"
#include "pch.h"

static class DBSceneData
{
public:
	int datanum;
	int chapter;
	int stage;
	EEnemyType enemytype;
	int x;
	int y;
};

static class DBPlayerData
{
public:
	int datanum;
	int LV;
	int EXP;
	int skillPoint;
	int chapter;
	int stage;
	int MAXHP;
	int playerHP;
	int ATKP;
	float ATKM;
	int SPDP;
	float SPDM;
	int SSPDP;
	float SSPDM;
	float CRI;
	int healCount;
};

class GameData : public Singleton<GameData>
{
public:
	GameData();
	~GameData();

	void Init();
	
public:
	Player* player;
	int ATKP; //���ݷ� ��
	float ATKM; //���ݷ� ��
	int SSPDP; //�����ǵ�(����) ��
	float SSPDM; //�����ǵ�(����) ��
	int SPDP; //���ǵ� ��
	float SPDM; //���ǵ� ��
	int MAXHP; //�ִ�ü��
	int healCount;//ȸ���� Ƚ��
	float CRI; //ũ��Ƽ�� Ȯ��

	void SavePlayerData();
	void SaveFirstPlayerData();
	int LoadSceneData(CString where);
	int LoadPlayerData();
	void SetPlayerDBData();

	std::vector<int> AssetObjImgVec;
	std::vector<DBSceneData*> DBSceneVec;
	DBPlayerData dbPlayerData;
	DBSceneData* dbSceneData;	
	int chapternum;
	int stagenum;
};

GameData* GameData::instance = nullptr;