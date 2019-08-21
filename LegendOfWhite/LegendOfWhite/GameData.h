#pragma once
#include "Singleton.h"
#include "pch.h"

static class DBSceneData
{
public:
	int datanum;
	int chapter;
	int stage;
	EObjectType objtype;
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
	int HP;
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

	int GetStagenum();
	void SetStagenum(int stage);
	int GetChapternum();
	void SetChapternum(int chapter);

public:
	Player* player;
	int winWIDTH;
	int winHEIGHT;
	int ATKP; //���ݷ� ��
	float ATKM; //���ݷ� ��
	int SSPDP; //�����ǵ�(����) ��
	float SSPDM; //�����ǵ�(����) ��
	int SPDP; //���ǵ� ��
	float SPDM; //���ǵ� ��
	int HP; //�ִ�ü��
	int healCount;//ȸ���� Ƚ��
	float CRI; //ũ��Ƽ�� Ȯ��

	void SavePlayerData();
	void LoadSceneData();
	void LoadPlayerData();
	DBSceneData* GetSceneData(int chapter, int stage);

	std::vector<int> AssetObjImgVec;
	std::vector<DBSceneData*> DBSceneVec;
	DBPlayerData dbPlayerData;
	DBSceneData* dbSceneData;

	bool isPlayerData = false;

private:	
	int chapternum;
	int stagenum;
};

GameData* GameData::instance = nullptr;