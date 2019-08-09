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

private:
	Player* player;
	//std::vector<Enemy
	int chapternum;
	int stagenum;
};

GameData* GameData::instance = nullptr;