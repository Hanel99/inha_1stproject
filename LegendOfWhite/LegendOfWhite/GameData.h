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
	int ATKP; //공격력 합
	float ATKM; //공격력 곱
	int SSPDP; //샷스피드(공속) 합
	float SSPDM; //샷스피드(공속) 곱
	int SPDP; //스피드 합
	float SPDM; //스피드 곱
	int HP; //최대체력
	int healCount;//회복한 횟수
	float CRI; //크리티컬 확률

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