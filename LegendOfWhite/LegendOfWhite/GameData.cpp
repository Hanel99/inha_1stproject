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
	//이어하기를 눌렀을경우, DB불러서 데이터 가져오기
	//새로시작의 경우 위 DB불러오는걸 넘기고 초기값 셋팅해준뒤 바로 게임씬으로 이동.

	ATKP = 1;
	ATKM = 0.0f;
	SSPDP = 1;
	SSPDM = 0.0f;
	SPDP = 1;
	SPDM = 0.0f;
	HP = 3;
	healCount = 0;
	CRI = 0.0f;
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
