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
	//�̾��ϱ⸦ ���������, DB�ҷ��� ������ ��������
	//���ν����� ��� �� DB�ҷ����°� �ѱ�� �ʱⰪ �������ص� �ٷ� ���Ӿ����� �̵�.

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
