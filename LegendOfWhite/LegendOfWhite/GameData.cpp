#include "pch.h"
#include "GameData.h"

GameData::GameData()
	: stagenum(1)
	, chapternum(1)
{
	Init();
}

GameData::~GameData()
{
}

void GameData::Init()
{
	player = new Player;
}

int GameData::GetStagenum()
{
	return stagenum;
}

void GameData::SetStagenum(int stage)
{
	stagenum = stage;
}

int GameData::GetChapternum()
{
	return chapternum;
}

void GameData::SetChapternum(int chapter)
{
	chapternum = chapter;
}
