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
	int ATKP; //���ݷ� ��
	int ATKM; //���ݷ� ��
	int SSPDP; //�����ǵ�(����) ��
	int SSPDM; //�����ǵ�(����) ��
	int SPDP; //���ǵ� ��
	int SPDM; //���ǵ� ��
	int HP; //�ִ�ü��
	int CRI; //ũ��Ƽ�� Ȯ��


private:	
	int chapternum;
	int stagenum;
};

GameData* GameData::instance = nullptr;