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

private:	
	int chapternum;
	int stagenum;
};

GameData* GameData::instance = nullptr;