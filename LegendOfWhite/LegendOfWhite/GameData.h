#pragma once
#include "Singleton.h"
#include "pch.h"

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


private:	
	int chapternum;
	int stagenum;
};

GameData* GameData::instance = nullptr;