#include "pch.h"
#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
}

void GameData::Init()
{
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
